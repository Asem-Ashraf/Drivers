#include "../LIB/STD_TYPE.h"
#include "../LIB/ERR_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CPU_FREQ.h"

#define F_CPU CPU_u32Freq
#include <util/delay.h>


#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/ADC/ADC_INTERFACE.h"
#include "../MCAL/GIE/GIE_INTERFACE.h"
#include "../MCAL/EXTI/EXTI_INTERFACE.h"
#include "../MCAL/I2C/I2C_INTERFACE.h"


#include "../HAL/LCD/LCD_INTERFACE.h"
#include "../HAL/EEPROM/EEPROM_INTERFACE.h"

#include "../SERVICE/Type_Conv.h"

#include "block/block.h"
#include "transaction/transaction.h"
#include "generate/generate.h"

#define Delay _delay_ms(100)

#define EEPROM_LAST_HASH_ADDRESS 0xFF

#define HASH_FOUND_INPUT_PIN DIO_u8PORTC, DIO_u8PIN3


Block Global_block;

char Global_String[20];

u8 Global_StatusCode = 0;

volatile u8 SignalFromManager = 0;

void func(void){
    SignalFromManager = 1;
}

extern LCD_t LCD_AstructDisplays[];
extern EEPROM_t EEPROM_AstructChips[];

u8 u8BroadcastBlock(){
    I2C_enuStartCondition_Master(&Global_StatusCode);
    if (Global_StatusCode != I2C_MASTER_START_SENT) {
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error start");
        return 1;
    }
    I2C_enuSendSLA_R_W_Master(0, I2C_WRITE_OPERATION, &Global_StatusCode);
    if (Global_StatusCode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error SLA");
        LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
        floatToString(Global_StatusCode, Global_String, 0);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
        return 1;
    }
    for (u8 blocksize = 0; blocksize<sizeof(Block); blocksize++) {
        I2C_enuSendDataByte_Master(((u8*)&Global_block)[blocksize], &Global_StatusCode);
        if (Global_StatusCode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error data");
            LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
            floatToString(Global_StatusCode, Global_String, 0);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
            return 1;
        }
        // a delay to give the slave a chance to process what was sent
        _delay_us(10);
    }
    I2C_enuStopCondition_Master();
    return 0;
}
void voidReceiveNonce(){
    I2C_enuInit_Slave(0b00000010, I2C_GENERAL_CALL_ACCEPT);
    I2C_enuCheckStatus_Slave(&Global_StatusCode);
    if(Global_StatusCode != I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error gen");
    }
    for (u8 i = 0; i<sizeof(u32); i++) {
        I2C_enuReceiveDataByte_Slave(&((u8*)&Global_block.nonce)[i], I2C_SEND_ACK);
        I2C_enuCheckStatus_Slave(&Global_StatusCode);
        if(Global_StatusCode != I2C_SLAVE_DATA_RECEIVED_ACK_SENT){
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error data");
        }
    }
    I2C_enuResetAndCheckStatus_Slave(&Global_StatusCode);
    if(Global_StatusCode != I2C_SLAVE_STOP_RECEIVED){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error stop");
    }
}

















int main(void){

    // initialize interrupt
    GIE_Enable();
    EXTI_enuInitInterrupt(EXTI_u8INT2,func);
    EXTI_enuSetSenseControl(EXTI_u8INT2, EXTI_u8RISING_EDGE);
    EXTI_enuEnableInterrupt(EXTI_u8INT2);

    // initialize LCD
    ES_t error = LCD_enuInit();
    if (error != ES_OK)  { 
        DIO_enuSetPortValue(DIO_u8PORTB, error);
    }

    // initialize I2C
    error = I2C_enuInit_Master(400);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C init failed");
        return 0;
    }

    // initialize ADC
    error = ADC_enuInit(ADC_u8PRESCALER_2, ADC_u8LEFT_ADJ, ADC_u8AVCC);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ADC init failed");
        return 0;
    }


    // set up ADC Channel direction as input
    DIO_enuSetPinDirection(DIO_u8PORTA, DIO_u8PIN1, DIO_u8INPUT);
    ADC_enuSetChannel(ADC_u8CH1);

    DIO_enuSetPinDirection(HASH_FOUND_INPUT_PIN, DIO_u8OUTPUT);

    // generate block
    Global_block.target = 0x00100000;

    u8 address;
    EEPROM_enuReadByte(&EEPROM_AstructChips[0], EEPROM_LAST_HASH_ADDRESS, &address);
    if (( address >= EEPROM_LAST_HASH_ADDRESS-4 )|| address%4!=0) {
        EEPROM_enuWriteByte(&EEPROM_AstructChips[0], EEPROM_LAST_HASH_ADDRESS, 0);
        address = 0;
    }

    EEPROM_enuReadPage(&EEPROM_AstructChips[0], address, (u8*)&Global_block.prevHash, sizeof(Global_block.prevHash));

    while (1) {
        // generate transaction
        for (u8 i = 0; i < NUM_OF_TRANSACTIONS_IN_BLOCK ; i++) {
            generateRandomTransaction(&Global_block.transactions[i]);
        }


        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block generated");
        Delay;
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Waiting signal");
        // wait for signal from manager on int2
        while(!SignalFromManager);
        SignalFromManager = 0;
        DIO_enuSetPinValue(HASH_FOUND_INPUT_PIN, DIO_u8LOW);

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"signal received");
        Delay;

        // broadcast block on i2c
        if(u8BroadcastBlock()==1){
            return 0;
        }

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block sent");

    ReceiveNonce:

        LCD_enuGotoPosition(&LCD_AstructDisplays[0],1 ,0);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Wating nonce");

        voidReceiveNonce();

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce received");

        Delay;

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Hashing block");

        Delay;
        // hash block
        u32 hash = hashBlock(&Global_block);

        // check hash
        if (hash < Global_block.target) {

            DIO_enuSetPinValue(HASH_FOUND_INPUT_PIN, DIO_u8HIGH);

            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block accepted");
            Delay;
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Adding to");
            LCD_enuGotoPosition(&LCD_AstructDisplays[0],1 ,0);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"BlockChain");
            Delay;

            u8 address;
            EEPROM_enuReadByte(&EEPROM_AstructChips[0], EEPROM_LAST_HASH_ADDRESS,&address);
            error = EEPROM_enuWritePage(&EEPROM_AstructChips[0], address, (u8*)&hash, sizeof(hash));
            if (error != ES_OK) {
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"EEPROM error");
                return 0;
            }
            address += sizeof(hash);
            // check if address is at the end of the EEPROM memory
            // if so, start from the beginning
            // else, continue writing
            // this is to avoid overwriting the address of the last hash
            // which is stored at the end of the EEPROM memory
            // This will lead to a block chain made using a circular linked list
            if (address >= EEPROM_LAST_HASH_ADDRESS-sizeof(hash)) {
                address = 0;
            }
            _delay_ms(1);
            error = EEPROM_enuWriteByte(&EEPROM_AstructChips[0], EEPROM_LAST_HASH_ADDRESS, address);
            if (error != ES_OK) {
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"EEPROM error");
                return 0;
            }

            // update prev hash
            Global_block.prevHash = hash;
            // update target
            Global_block.target = 0x00100000;
            // update nonce
            Global_block.nonce = 0x00000000;
            continue;

        } else {
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block rejected");
            // wait again for another nonce from miners
            Delay;
            goto ReceiveNonce;
        }
    }
}
