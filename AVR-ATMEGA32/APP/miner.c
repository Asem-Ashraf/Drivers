
#include "../LIB/STD_TYPE.h"
#include "../LIB/ERR_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CPU_FREQ.h"

#define F_CPU CPU_u32Freq

#include <util/delay.h>

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/SPI/SPI_INTERFACE.h"
#include "../MCAL/I2C/I2C_INTERFACE.h"


#include "../HAL/LCD/LCD_INTERFACE.h"


#include "../SERVICE/Type_Conv.h"

#include "block/block.h"
#include "transaction/transaction.h"

#define MINER_REQUEST_OUTPUT_PIN DIO_u8PORTB, DIO_u8PIN3
#define MINER_STOP_OUTPUT_PIN DIO_u8PORTB, DIO_u8PIN2

#define Delay _delay_ms(100)

extern LCD_t LCD_AstructDisplays[];

#define NONCE_FOUND 1

#define NONCE_NOT_FOUND 0

#define GENERATOR_ADDRESS 0b00000010

#define ACK_SUCCESS 0
#define BAD_ACK 1

#define GOOD_BOUNDS 0
#define BAD_BOUNDS 1

ES_t Global_error = ES_NOK;

char Global_String[20];

u8 Global_ID;

Block Global_block;

u8 Global_StatusCode;

u8 Global_PinVal;


u8 u8SendNonce(u32 nonce){
StartSendingNonce:
    I2C_enuStartCondition_Master(&Global_StatusCode);
    if(Global_StatusCode != I2C_MASTER_START_SENT){ 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error start");
        return Global_StatusCode;
    }

    I2C_enuSendSLA_R_W_Master(GENERATOR_ADDRESS, I2C_WRITE_OPERATION, &Global_StatusCode);
    if(Global_StatusCode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED){
        // if the generator did not send ACK, maybe because he is already processing a nonce.
        // or because a nonce is already found.

        // if the nonce is found then send a stop condition and return the code 
        // for nonce found and wait for the next block in the main while loop
        DIO_enuGetPinValue(DIO_u8PORTC,DIO_u8PIN3,&Global_PinVal);
        if( Global_PinVal== DIO_u8HIGH){
            // nonce already found
            I2C_enuStopCondition_Master();
            return 1;
        }
        // there could also be that the error is I2C_MASTER_ARB_LOST but that 
        // would mean that the generator is sending an accepted block to the 
        // EEPROM, which means that the nonce found signal is already up


        // if the generator is already processing a nonce, Then attempt to send 
        // nonce again because the nonce that is being processed right now could 
        // be wrong
        if(Global_StatusCode == I2C_MASTER_SLA_W_SENT_NACK_RECEIVED) {
            I2C_enuStopCondition_Master();
            goto StartSendingNonce;
        }

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error sla");
        return Global_StatusCode;
    }
    DIO_enuGetPinValue(DIO_u8PORTC,DIO_u8PIN3,&Global_PinVal);
    if( Global_PinVal== DIO_u8HIGH){
        // nonce already found
        return 1;
    }

    for (u8 i = 0; i<sizeof(u32); i++) {
        I2C_enuSendDataByte_Master(((u8*)&nonce)[i], &Global_StatusCode);
        DIO_enuGetPinValue(DIO_u8PORTC,DIO_u8PIN3,&Global_PinVal);
        if( Global_PinVal== DIO_u8HIGH){
            // nonce already found
            I2C_enuStopCondition_Master();
            return 1;
        }

        // This could happen if w miners find nonce at the exact same time and send it to the generator
        // one miner will lose arbitration and will have to send the nonce again
        // just if the nonce sent before was wrong
        if(Global_StatusCode == I2C_MASTER_ARB_LOST){
            goto StartSendingNonce;
        }


        // this case is not possible because the generator will always send ACK if we reach this stage
        if(Global_StatusCode != I2C_MASTER_DATA_SENT_ACK_RECEIVED){
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error data");
            return Global_StatusCode; 
        }
        _delay_ms(1);
    }
    I2C_enuStopCondition_Master();
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce sent");
    return 0;
}

u8 mine(Block* pBlock, u32 nonceMin, u32 nonceMax){
    u8 Code;
    for (pBlock->nonce = nonceMin ; pBlock->nonce <nonceMax; pBlock->nonce ++) {
        u32 hashresult = hashBlock(pBlock);
        DIO_enuGetPinValue(DIO_u8PORTC,DIO_u8PIN3,&Code);
        if( Code== DIO_u8HIGH){
            return 2;
        }
        if(hashresult<pBlock->target) {
            return NONCE_FOUND;
        }

    }
    return NONCE_NOT_FOUND;
}

ES_t enuReceiveBlock(Block* pBlock){
    u8 statusCode;
    I2C_enuInit_Slave(0b00000001, I2C_GENERAL_CALL_ACCEPT);
    I2C_enuCheckStatus_Slave(&statusCode);
    if(statusCode != I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error gen");
        return ES_NOK;
    }

    for (u8 i = 0; i<sizeof(Block); i++) {
        I2C_enuReceiveDataByte_Slave(&(((u8*)pBlock)[i]),I2C_SEND_ACK);
        I2C_enuCheckStatus_Slave(&statusCode);
        if(statusCode != I2C_SLAVE_GEN_CALL_DATA_RECEIVED_ACK_SENT){
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error data");
        return ES_NOK;
        }
    }
    I2C_enuResetAndCheckStatus_Slave(&statusCode);
    if(statusCode != I2C_SLAVE_STOP_RECEIVED){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error stop");
        return ES_NOK;
    }
    return ES_OK;
}


u8 u8ReceiveBounds(u32* nonceMin, u32* nonceMax){
    // receive the first byte
    *nonceMin = (u32)SPI_enuReceiveByte();

    // receive the first byte
    *nonceMax = (u32)SPI_enuReceiveByte();

    if (*nonceMax<=*nonceMin) {
        return BAD_BOUNDS;
    }
    return GOOD_BOUNDS;
    
}

u8 u8ReceiveRecognition(){
    // The function receives the ID of the miner twice.
    Global_ID = SPI_enuReceiveByte();
    if(Global_ID - SPI_enuSendReceiveByte(Global_ID) == 0) {
        // not checking error because I know I have input the correct arguments
        return ACK_SUCCESS;
    }
    return BAD_ACK;
}














int main() {

    Global_error = LCD_enuInit(); 
    if (Global_error != ES_OK)  { 
        DIO_enuSetPortValue(DIO_u8PORTB, Global_error); 
    }

    Global_error = I2C_enuInit_Master_And_Slave(0b0000001,400, I2C_GENERAL_CALL_ACCEPT);
    if (Global_error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C init failed");
        return 0;
    }

    // not checking error because I know I have input the correct arguments
    DIO_enuSetPinDirection(MINER_REQUEST_OUTPUT_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinValue    (MINER_REQUEST_OUTPUT_PIN, DIO_u8HIGH);

    DIO_enuSetPinDirection(MINER_STOP_OUTPUT_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinValue    (MINER_STOP_OUTPUT_PIN, DIO_u8HIGH);


    Global_error = SPI_enuSlaveInit(SPI_u8LSB_FIRST, SPI_u8RISING_LEADING, 
                             SPI_u8SAMPLE_TRAILING,SPI_u8SLAVE_INPUT_OUTPUT);
    if (Global_error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"SPI init failed");
        return 0;
    }

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Waiting for");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1,0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"recognition");

retry:
    switch(u8ReceiveRecognition()){
        case ACK_SUCCESS:
            DIO_enuSetPinValue(MINER_REQUEST_OUTPUT_PIN, DIO_u8LOW);
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"recognized");
            LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ID: ");
            integerToString(Global_ID, Global_String);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
            break;
        case BAD_ACK:
            goto retry;
    }

    Delay;


    u32 nonceMin,nonceMax;
GetBounds:
    switch(u8ReceiveBounds(&nonceMin, &nonceMax)){
        case BAD_BOUNDS:
            goto GetBounds;
        case GOOD_BOUNDS:
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Range received");
            break;
    }


    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1,0);
    integerToString(nonceMin, Global_String);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)" : ");
    integerToString(nonceMax, Global_String);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);

    Delay;

    nonceMin <<= 24;
    nonceMax <<= 24;



    while (1) {
        DIO_enuSetPinValue(MINER_STOP_OUTPUT_PIN, DIO_u8LOW);
        Global_error = enuReceiveBlock(&Global_block);
        if (Global_error != ES_OK) {
            return 0;
        }
        DIO_enuSetPinValue(MINER_STOP_OUTPUT_PIN, DIO_u8HIGH);

        Delay;
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"block received");
        // Delay;
        LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1,0);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"mining...");


        switch (mine(&Global_block, nonceMin, nonceMax)) {
        case NONCE_NOT_FOUND:
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce not found");
            continue;
        case 2: 
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"OMFN");
            break;
        case NONCE_FOUND:
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce found");
            LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
            integerToString(Global_block.nonce, Global_String);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
            break;

        }
        Delay;

        u8 Code;
        DIO_enuGetPinValue(DIO_u8PORTC,DIO_u8PIN3,&Code);
        if( Code== DIO_u8HIGH){
            // nonce already found
            continue;
        }
        switch(u8SendNonce(Global_block.nonce)){
            case 0:
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce sent");
                break;
            case 1:
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"OMFN");
                break;
            default:
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error sending");
                break;
        }
    }
}
