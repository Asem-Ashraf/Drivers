#include "../LIB/STD_TYPE.h"
#include "../LIB/ERR_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CPU_FREQ.h"

#define F_CPU CPU_u32Freq
#include <util/delay.h>

#include "../SERVICE/Type_Conv.h"

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/SPI/SPI_INTERFACE.h"


#include "../HAL/LCD/LCD_INTERFACE.h"

#include "block/block.h"
#include "transaction/transaction.h"


#define MAX_MINER_COUNT 8


#define MINER_SELECTOR_OUTPUT_PORT        DIO_u8PORTA
#define MINER_SELECTOR_ENABLE_OUTPUT_PIN  DIO_u8PORTB,DIO_u8PIN0

#define BROADCAST_ENABLE_OUTPUT_PIN       DIO_u8PORTC,DIO_u8PIN0

#define MINER_REQUEST_INPUT_PIN           DIO_u8PORTB, DIO_u8PIN3

#define MINER_STOP_INTPUT_PIN             DIO_u8PORTC, DIO_u8PIN4
#define MINERS_READY_INPUT_PIN            DIO_u8PORTC, DIO_u8PIN3

#define Delay _delay_ms(100)


extern LCD_t LCD_AstructDisplays[];



ES_t Global_error = ES_NOK;

char Global_String[20];

u8 Global_minerCount= 0;



int main() {

    // not checking error because I know I have input the correct arguments
    // and I don't want to waste time checking for errors
    // broadcast pin defaults to output low
    DIO_enuSetPinDirection(BROADCAST_ENABLE_OUTPUT_PIN     , DIO_u8OUTPUT);
    DIO_enuSetPinDirection(MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinValue    (MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8HIGH);
    DIO_enuSetPortDirection(MINER_SELECTOR_OUTPUT_PORT, 0xff);



    Global_error = LCD_enuInit();
    if (Global_error != ES_OK)  { DIO_enuSetPortValue(DIO_u8PORTB, Global_error); }


    Global_error = SPI_enuMasterInit(SPI_u8LSB_FIRST,  SPI_u8CLK_1X,SPI_u8CLK_16, 
                                     SPI_u8RISING_LEADING, SPI_u8SAMPLE_TRAILING, 
                                     SPI_u8MASTER_INPUT_OUTPUT);
    if (Global_error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"SPI init failed");
        return 0;
    }

    Delay;

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Detecting miners");


    // as long as the any miner is holding the pin to low, keep counting
    u8 i=0;
    u8 pinval;


    DIO_enuGetPinValue(MINER_REQUEST_INPUT_PIN, &pinval);

    _delay_ms(50);

    while(pinval == DIO_u8LOW) {
        DIO_enuSetPortValue(MINER_SELECTOR_OUTPUT_PORT,i);
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8LOW);
        _delay_ms(10);
        SPI_voidSendByte(i);
        _delay_ms(10);
        if (i==SPI_enuSendReceiveByte(i)) {
            i++;
        }else{
            continue;
        }

        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8HIGH);
        _delay_ms(10);
        DIO_enuGetPinValue(MINER_REQUEST_INPUT_PIN, &pinval);
    }
    Global_minerCount=i;

    

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ACK sent to");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    integerToString(Global_minerCount,Global_String);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)Global_String);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)" miners");
    Delay;
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Sending ranges");

    Delay;

    // for each miner send 2 bytes that represent the bounds of the range of the miner
    u8 bound = 255/Global_minerCount;
    for(u8 j = 0; j<Global_minerCount;) {
        DIO_enuSetPortValue(MINER_SELECTOR_OUTPUT_PORT,j );
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8LOW);
        // send lower bound
        SPI_voidSendByte(j*bound);
        j++;
        // send higher bound
        SPI_voidSendByte(j*bound);
        DIO_enuSetPinValue(MINER_SELECTOR_ENABLE_OUTPUT_PIN, DIO_u8HIGH);
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Ranges sent");

    Delay;

    _delay_ms(10);

    while (1) {
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"broadcasting...");

        // signal for generator to start broadcasting blocks
        // the generator receives this through INT2 so it does not need to be 
        // too long
        DIO_enuSetPinValue(BROADCAST_ENABLE_OUTPUT_PIN, DIO_u8HIGH);
        DIO_enuSetPinValue(BROADCAST_ENABLE_OUTPUT_PIN, DIO_u8LOW);

        Delay;

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Sleeping");

        Delay;
        u8 MinersReady= DIO_u8LOW;
        u8 StopMining = DIO_u8LOW;
        while(!( MinersReady == DIO_u8HIGH && StopMining == DIO_u8HIGH)){
            DIO_enuGetPinValue(MINERS_READY_INPUT_PIN, &MinersReady);
            DIO_enuGetPinValue(MINER_STOP_INTPUT_PIN, &StopMining);
        }
    }
}
