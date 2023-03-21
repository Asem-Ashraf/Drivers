#include "../../LIB/stdTypes.h"
#include "../../LIB/Bit_Math.h"
#include "../../LIB/ErrorStates.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LCD_CONFIG.h"

#define LCD_u8DISPLAY_NUM 2

#define LCD_PIN_u8NOT_USED 0xFF

u8 LCD_u8DisplayNum = LCD_u8DISPLAY_NUM;
LCD_t LCD_AstructDisplays[LCD_u8DISPLAY_NUM] = {
    {
        LCD_u8MODE_8BIT,
        LCD_u8CURSOR_ON,LCD_u8CURSOR_BLINK_ON,
        LCD_u8LINES_2,
        LCD_u8BLOCK_SIZE_5x7,
        DIO_u8PORTB,DIO_u8PIN0,
        DIO_u8PORTB,DIO_u8PIN1,
        DIO_u8PORTB,DIO_u8PIN2,

        DIO_u8PORTA,DIO_u8PIN0,
        DIO_u8PORTA,DIO_u8PIN1,
        DIO_u8PORTA,DIO_u8PIN2,
        DIO_u8PORTA,DIO_u8PIN3,
        DIO_u8PORTA,DIO_u8PIN4,
        DIO_u8PORTA,DIO_u8PIN5,
        DIO_u8PORTA,DIO_u8PIN6,
        DIO_u8PORTA,DIO_u8PIN7,
    },
    {
        LCD_u8MODE_4BIT,
        LCD_u8CURSOR_OFF,LCD_u8CURSOR_BLINK_OFF,
        LCD_u8LINES_1,
        LCD_u8BLOCK_SIZE_5x7,
        DIO_u8PORTC,DIO_u8PIN0,
        DIO_u8PORTC,DIO_u8PIN1,
        DIO_u8PORTC,DIO_u8PIN2,

        LCD_u8NOT_USED,LCD_u8NOT_USED,
        LCD_u8NOT_USED,LCD_u8NOT_USED,
        LCD_u8NOT_USED,LCD_u8NOT_USED,
        LCD_u8NOT_USED,LCD_u8NOT_USED,
        DIO_u8PORTD,DIO_u8PIN4,
        DIO_u8PORTD,DIO_u8PIN5,
        DIO_u8PORTD,DIO_u8PIN6,
        DIO_u8PORTD,DIO_u8PIN7,
    }
};
