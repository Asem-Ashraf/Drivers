#include "../LIB/STD_TYPE.h"
#include "../LIB/ERR_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CPU_FREQ.h"

#define F_CPU CPU_u32Freq
#include <util/delay.h>

#include "../SERVICE/Type_Conv.h"

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

#include "block/block.h"
#include "transaction/transaction.h"


#define MAX_MINER_COUNT 8


#define MINER_SELECTOR_PORT DIO_u8PORTA
#define MINER_SELECTOR_ENABLE_PIN DIO_u8PORTB,DIO_u8PIN0

#define BROADCAST_ENABLE_PIN DIO_u8PORTC,DIO_u8PIN0

#define MINER_REQUEST_PIN DIO_u8PORTB, DIO_u8PIN3

#define Delay _delay_ms(300)

extern LED_t LED_AstructLed[];
extern LCD_t LCD_AstructDisplays[];

int main() {
    ES_t error = ES_NOK;
    char str[20];
    u8 minerCount= 0;

    error = LCD_enuInit();
    if (error != ES_OK)  { DIO_enuSetPortValue(DIO_u8PORTB, error); }

    // not checking error because I know I have input the correct arguments
    // and I don't want to waste time checking for errors
    // broadcast pin defaults to output low
    DIO_enuSetPinDirection(BROADCAST_ENABLE_PIN     , DIO_u8OUTPUT);
    DIO_enuSetPinDirection(MINER_SELECTOR_ENABLE_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinValue    (MINER_SELECTOR_ENABLE_PIN, DIO_u8HIGH);
    DIO_enuSetPortDirection(MINER_SELECTOR_PORT, 0xff);

    error = SPI_enuMasterInit(SPI_u8LSB_FIRST,  SPI_u8CLK_1X,SPI_u8CLK_4, 
                              SPI_u8RISING_LEADING, SPI_u8SAMPLE_TRAILING, 
                              SPI_u8MASTER_INPUT_OUTPUT);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"SPI init failed");
        return 0;
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"SPI initiated");

    Delay;

DetectingMiners:

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Detecting miners");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"detected: 0");


    // as long as the any miner is holding the pin to low, keep counting
    for (u16 i = 0;i<MAX_MINER_COUNT; i++) {
        u8 pinval;
        DIO_enuGetPinValue(MINER_REQUEST_PIN, &pinval);
        if (pinval == DIO_u8HIGH) {
            // already incremented from loop condition
            minerCount = i;
            break;
        }

        u8 tries = 3;
    SendACK:
        // Delay;
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_PIN, DIO_u8HIGH);
        DIO_enuSetPortValue(MINER_SELECTOR_PORT,i );
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_PIN, DIO_u8LOW);
        SPI_voidSendByte(i);
        SPI_voidSendByte(i);
        // Delay;
        // if(SPI_enuReceiveByte()!=i) {
        //     LCD_enuClear(&LCD_AstructDisplays[0]);
        //     LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"miner failed");
        //     LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
        //     LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"id: ");
        //     integerToString((float)i, str, 0);
        //     LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
        //     Delay;
        //     tries--;
        //     if(tries)goto SendACK;
        //     else tries = 3;
        // }
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_PIN, DIO_u8HIGH);
        integerToString(i+1, str);
        LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 11);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
        Delay;
    }
    if (minerCount == 0) {
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"No miners found");
        LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"trying again");
        Delay;
        goto DetectingMiners;
    }
    

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ACK sent");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"successfully");

    Delay;

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Sending ranges");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"to miners");

    Delay;

    // for each miner send 2 bytes that represent the bounds of the range of the miner
    u8 bound = 255/minerCount;
    for(u8 j = 0; j<minerCount;) {
        DIO_enuSetPortValue(MINER_SELECTOR_PORT,j );
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_PIN, DIO_u8LOW);
        SPI_voidSendByte(j*bound);
        j++;
        SPI_voidSendByte(j*bound);
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_PIN, DIO_u8HIGH);
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Ranges to miners");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"sent successfully");

    Delay;

    // signal for generator to start broadcasting blocks
    DIO_enuSetPinValue(BROADCAST_ENABLE_PIN, DIO_u8HIGH);
    // signal for generator to start broadcasting blocks
    DIO_enuSetPinValue(BROADCAST_ENABLE_PIN, DIO_u8LOW);

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"broadcasting...");

    Delay;

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Going to sleep");
    while (1) {
        u8 pinvalue;
        DIO_enuGetPinValue(MINER_REQUEST_PIN, &pinvalue);
        if (pinvalue == DIO_u8LOW) {
            goto DetectingMiners;
        }
    }
}
