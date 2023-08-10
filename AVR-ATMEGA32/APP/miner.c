
#include "../LIB/STD_TYPE.h"
#include "../LIB/ERR_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CPU_FREQ.h"

#define F_CPU CPU_u32Freq

#include <util/delay.h>

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/ADC/ADC_INTERFACE.h"
#include "../MCAL/TIMER0/TMR0_INTERFACE.h"
#include "../MCAL/GIE/GIE_INTERFACE.h"
#include "../MCAL/EXTI/EXTI_INTERFACE.h"
#include "../MCAL/UART/UART_INTERFACE.h"
#include "../MCAL/SPI/SPI_INTERFACE.h"
#include "../MCAL/I2C/I2C_INTERFACE.h"


#include "../HAL/LED/LED_INTERFACE.h"
#include "../HAL/LCD/LCD_INTERFACE.h"
#include "../HAL/Thermistor/TH_INTERFACE.h"
#include "../HAL/EEPROM/EEPROM_INTERFACE.h"

#define TWCR	*((volatile u8 *) 0x56)
#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWWC	3
#define TWEN	2
#define TWIE	0

#include "../SERVICE/Type_Conv.h"

#include "block/block.h"
#include "transaction/transaction.h"

#define MINER_REQUEST_PIN DIO_u8PORTB, DIO_u8PIN3

#define Delay _delay_ms(0)

extern LED_t LED_AstructLed[];
extern LCD_t LCD_AstructDisplays[];


int main() {
    ES_t error = ES_NOK;
    char str[20];

    error = LCD_enuInit();
    if (error != ES_OK)  { 
        DIO_enuSetPortValue(DIO_u8PORTB, error);
    }

    error = LED_enuInit(LED_AstructLed);
    if (error != ES_OK)  { 
        DIO_enuSetPortValue(DIO_u8PORTB, error);
    }

    error = I2C_enuInit_Slave(0b0000001,I2C_GENERAL_CALL_ACCEPT);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C init failed");
        return 0;
    }
    // LCD_enuClear(&LCD_AstructDisplays[0]);
    // LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C initiated");
    // LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    // LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"successfully");
    //
    // Delay;

    // not checking error because I know I have input the correct arguments
    DIO_enuSetPinDirection(MINER_REQUEST_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinValue    (MINER_REQUEST_PIN, DIO_u8HIGH);


    error = SPI_enuSlaveInit(SPI_u8LSB_FIRST, SPI_u8RISING_LEADING, 
                             SPI_u8SAMPLE_TRAILING,SPI_u8SLAVE_INPUT_ONLY);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"SPI init failed");
        return 0;
    }

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Waiting for ACK");


    u8 val;
    u8 tries = 3;
StartAck:
    // receive the first byte
     val = SPI_enuReceiveByte();
    // receive the second byte and take the difference. The difference being 
    // zero means that this miner has been successfully detected to be part of 
    // the network and should wait for its range of nonce in the next 2 bytes
    if(val - SPI_enuReceiveByte() == 0) {
        // not checking error because I know I have input the correct arguments
        // SPI_voidSendByte(val);
        DIO_enuSetPinValue(MINER_REQUEST_PIN, DIO_u8LOW);
    }
    else{
        // tries--;
        // if(tries)goto StartAck;
        // else {
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error in ACK");
            return 0;
        // }
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ACK received");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ID: ");
    integerToString(val, str);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);

    // Delay;


    // receive lower bound
    u32 nonceMin = ((u32)(SPI_enuReceiveByte()));
    // receive higher bound
    u32 nonceMax = ((u32)(SPI_enuReceiveByte()));

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Range received");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    integerToString(nonceMin, str);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)" : ");
    integerToString(nonceMax, str);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);

    Delay;
    nonceMin <<= 24;
    // receive higher bound
    nonceMax <<= 24;
    // u32 progressbarvar = nonceMax-nonceMin;
    // u32 progressbar = progressbarvar/16;

    Block block;
    u8 statusCode;
    I2C_enuCheckSLA_R_W_Slave(&statusCode);
    if(statusCode != I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error gen");
        return 0;
    }

    for (u8 i = 0; i<sizeof(Block); i++) {
        I2C_enuReceiveDataByte_Slave(&(((u8*)&block)[i]),I2C_SEND_ACK);
        I2C_enuCheckSLA_R_W_Slave(&statusCode);
        if(statusCode != I2C_SLAVE_GEN_CALL_DATA_RECEIVED_ACK_SENT){
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error data");
            return 0;
        }
    }
    TWCR = (1<<TWINT)|(1<<TWEN);
    I2C_enuCheckSLA_R_W_Slave(&statusCode);
    if(statusCode != I2C_SLAVE_STOP_RECEIVED){
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C Error stop");
        return 0;
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block received");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"successfully");
    Delay;

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Mining...");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);

    for (block.nonce = nonceMin ; block.nonce <nonceMax; block.nonce ++) {
        u32 hashresult = hashBlock(&block);
        LED_enuToggle(&LED_AstructLed[0]);
        if(hashresult<block.target) {
            integerToString(block.nonce, str);
            LCD_enuClear(&LCD_AstructDisplays[0]);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Nonce found");
            LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
            LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
            break;
        }
        // if(block.nonce%progressbar == 0){
        //     LCD_enuWriteChar(&LCD_AstructDisplays[0], '-');
        // }
    }

    while (1) {
    }
}
