#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#define LCD_u8MODE_8BIT 0x01
#define LCD_u8MODE_4BIT 0x00

#define LCD_u8CURSOR_ON 0x01
#define LCD_u8CURSOR_OFF 0x00

#define LCD_u8CURSOR_BLINK_ON 0x01
#define LCD_u8CURSOR_BLINK_OFF 0x00

#define LCD_u8LINES_1 0x00
#define LCD_u8LINES_2 0x01

#define LCD_u8BLOCK_SIZE_5x10 0x01
#define LCD_u8BLOCK_SIZE_5x7 0x00

#define LCD_u8NOT_USED 0xFF

typedef struct {
    // MODE
    u8 LCD_u8Mode;          // LCD_u8MODE_8BIT,         LCD_u8MODE_4BIT


    // CURSOR
    u8 LCD_u8Cursor;        // LCD_u8CURSOR_ON,         LCD_u8CURSOR_OFF
    u8 LCD_u8CursorBlink;   // LCD_u8CURSOR_BLINK_ON,   LCD_u8CURSOR_BLINK_OFF


    // LINES
    u8 LCD_u8LinesNum;      // LCD_u8LINES_2,           LCD_u8LINES_1


    // BLOCK
    u8 LCD_u8BlockSize;     // LCD_u8BLOCK_SIZE_5x10,   LCD_u8BLOCK_SIZE_5x7


    // CONTROL
    u8 LCD_u8RSPort;
    u8 LCD_u8RSPin;

    u8 LCD_u8RWPort;
    u8 LCD_u8RWPin;

    u8 LCD_u8EPort;
    u8 LCD_u8EPin;


    // DATA
    u8 LCD_u8DB0Port;
    u8 LCD_u8DB0Pin;

    u8 LCD_u8DB1Port;
    u8 LCD_u8DB1Pin;

    u8 LCD_u8DB2Port;
    u8 LCD_u8DB2Pin;

    u8 LCD_u8DB3Port;
    u8 LCD_u8DB3Pin;

    u8 LCD_u8DB4Port;
    u8 LCD_u8DB4Pin;

    u8 LCD_u8DB5Port;
    u8 LCD_u8DB5Pin;

    u8 LCD_u8DB6Port;
    u8 LCD_u8DB6Pin;

    u8 LCD_u8DB7Port;
    u8 LCD_u8DB7Pin;
} LCD_t;

#define LCD_u8DISPLAY_NUM 1

u8 LCD_u8DisplayNum = LCD_u8DISPLAY_NUM;
LCD_t LCD_AstructDisplays[LCD_u8DISPLAY_NUM] = {
        {
        LCD_u8MODE_8BIT,
        LCD_u8CURSOR_OFF,LCD_u8CURSOR_BLINK_OFF,
        LCD_u8LINES_2,
        LCD_u8BLOCK_SIZE_5x7,
        DIO_u8PORTC,DIO_u8PIN5,
        DIO_u8PORTC,DIO_u8PIN6,
        DIO_u8PORTC,DIO_u8PIN7,

        DIO_u8PORTD,DIO_u8PIN0,
        DIO_u8PORTD,DIO_u8PIN1,
        DIO_u8PORTD,DIO_u8PIN2,
        DIO_u8PORTD,DIO_u8PIN3,
        DIO_u8PORTD,DIO_u8PIN4,
        DIO_u8PORTD,DIO_u8PIN5,
        DIO_u8PORTD,DIO_u8PIN6,
        DIO_u8PORTD,DIO_u8PIN7,
    }
};
