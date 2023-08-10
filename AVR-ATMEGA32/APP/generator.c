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

#include "../SERVICE/Type_Conv.h"

#include "block/block.h"
#include "transaction/transaction.h"
#include "generate/generate.h"

#define Delay _delay_ms(1)

volatile u8 SignalFromManager = 0;
void func(void){
    SignalFromManager = 1;
}

extern LCD_t LCD_AstructDisplays[];

int main(void){
    // initialize block
    Block block;
    char str[20];

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

    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"LCD initiated");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"successfully");

    Delay;
    // initialize I2C
    error = I2C_enuInit_Master(100);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C init failed");
        return 0;
    }
    LCD_enuClear(&LCD_AstructDisplays[0]);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"I2C initiated");
    LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
    LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"successfully");

    Delay;
    // initialize ADC
    error = ADC_enuInit(ADC_u8PRESCALER_2, ADC_u8RIGHT_ADJ, ADC_u8AVCC);
    if (error != ES_OK)  { 
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"ADC init failed");
        return 0;
    }
    ADC_enuSetChannel(ADC_u8CH1);
    DIO_enuSetPinDirection(DIO_u8PORTA, DIO_u8PIN1, DIO_u8INPUT);


    while (1) {
        // generate transaction
        for (u8 i = 0; i < NUM_OF_TRANSACTIONS_IN_BLOCK ; i++) {
            generateRandomTransaction(&block.transactions[i]);
        }

        // generate block
        block.target = 0x00100000;
        block.height = 0x00000000;
        block.prevHash = 0x00000000;

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block generated");
        Delay;
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Waiting signal");
        // wait for signal from manager on int2
        while(!SignalFromManager);
        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"signal received");
        Delay;

        // broadcast block on i2c
        u8 Copy_u8StatusCode = 0;
        I2C_enuStartCondition_Master(&Copy_u8StatusCode);
        if (Copy_u8StatusCode != I2C_MASTER_START_SENT) {
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error");
                LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"start not sent");
                return 0;
        }
        I2C_enuSendSLA_R_W_Master(0, I2C_WRITE_OPERATION, &Copy_u8StatusCode);
        if (Copy_u8StatusCode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error SLA");
                LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
                floatToString(Copy_u8StatusCode, str, 0);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
                return 0;
        }
        for (u8 blocksize = 0; blocksize<sizeof(Block); blocksize++) {
            I2C_enuSendDataByte_Master(((u8*)&block)[blocksize], &Copy_u8StatusCode);
            if (Copy_u8StatusCode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
                LCD_enuClear(&LCD_AstructDisplays[0]);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Error data");
                LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
                floatToString(Copy_u8StatusCode, str, 0);
                LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
                return 0;
            }
        }
        I2C_enuStopCondition_Master();

        LCD_enuClear(&LCD_AstructDisplays[0]);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)"Block sent");
        SignalFromManager = 0;
        Delay;
    }
}
