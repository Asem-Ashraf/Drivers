#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

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


/* LCD Commands */
ES_t LCD_enuInit(void);

ES_t LCD_enuGotoPosition(LCD_t* LCD_pstructDisplay,u8 x,u8 y);

ES_t LCD_enuWriteChar(LCD_t* LCD_pstructDisplay,u8 Data);

ES_t LCD_enuClear(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOn(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOff(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuSendWriteCommand(LCD_t* LCD_pstructDisplay,u8 Command);


#endif /* LCD_INTERFACE_H_ */
