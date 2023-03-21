#include <util/delay.h>
#include "../../LIB/stdTypes.h"
#include "../../LIB/Bit_Math.h"
#include "../../LIB/ErrorStates.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LCD_PRIVATE.h"

extern LCD_t LCD_AstructDisplays[];
extern u8 LCD_u8DisplayNum;

static inline ES_t LCD_enuReadBits(LCD_t *LCD_pstructDisplay,u8* command){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    u8 local_u8Data = 0;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB7Port, LCD_pstructDisplay->LCD_u8DB7Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 7;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB6Port, LCD_pstructDisplay->LCD_u8DB6Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 6;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB5Port, LCD_pstructDisplay->LCD_u8DB5Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 5;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB4Port, LCD_pstructDisplay->LCD_u8DB4Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 4;
    if (LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB3Port, LCD_pstructDisplay->LCD_u8DB3Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 3;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB2Port, LCD_pstructDisplay->LCD_u8DB2Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 2;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB1Port, LCD_pstructDisplay->LCD_u8DB1Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 1;
    Local_ESErrorState = DIO_enuGetPinValue(LCD_pstructDisplay->LCD_u8DB0Port, LCD_pstructDisplay->LCD_u8DB0Pin, &local_u8Data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    *command |= local_u8Data << 0;
    return Local_ESErrorState;
}
static inline ES_t LCD_enuWriteBits(LCD_t *LCD_pstructDisplay,u8 command){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB7Port, LCD_pstructDisplay->LCD_u8DB7Pin, GetBit(command,7));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB6Port, LCD_pstructDisplay->LCD_u8DB6Pin, GetBit(command,6));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB5Port, LCD_pstructDisplay->LCD_u8DB5Pin, GetBit(command,5));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB4Port, LCD_pstructDisplay->LCD_u8DB4Pin, GetBit(command,4));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    if (LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB3Port, LCD_pstructDisplay->LCD_u8DB3Pin, GetBit(command,3));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB2Port, LCD_pstructDisplay->LCD_u8DB2Pin, GetBit(command,2));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB1Port, LCD_pstructDisplay->LCD_u8DB1Pin, GetBit(command,1));
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8DB0Port, LCD_pstructDisplay->LCD_u8DB0Pin, GetBit(command,0));
    return Local_ESErrorState;
}




static inline ES_t LCD_enuWriteData(LCD_t *LCD_pstructDisplay,u8 data){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RSPort, LCD_pstructDisplay->LCD_u8RSPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RWPort, LCD_pstructDisplay->LCD_u8RWPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = LCD_enuWriteBits(LCD_pstructDisplay,data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT){
        Local_ESErrorState = LCD_enuWriteBits(LCD_pstructDisplay,data<<4);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    }
    return Local_ESErrorState;
}
static inline ES_t LCD_enuReadData(LCD_t *LCD_pstructDisplay,u8* data){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RSPort, LCD_pstructDisplay->LCD_u8RSPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RWPort, LCD_pstructDisplay->LCD_u8RWPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = LCD_enuReadBits(LCD_pstructDisplay,data);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT){
        u8 Local_u8Temp = 0;
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = LCD_enuReadBits(LCD_pstructDisplay,&Local_u8Temp);
        *data|= Local_u8Temp>>4;
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    }
    return Local_ESErrorState;
}
static inline ES_t LCD_enuWriteCommand(LCD_t *LCD_pstructDisplay,u8 command){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RSPort, LCD_pstructDisplay->LCD_u8RSPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RWPort, LCD_pstructDisplay->LCD_u8RWPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = LCD_enuWriteBits(LCD_pstructDisplay,command);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT){
        Local_ESErrorState = LCD_enuWriteBits(LCD_pstructDisplay,command<<4);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    }
    return Local_ESErrorState;
}

static inline ES_t LCD_enuReadCommand(LCD_t *LCD_pstructDisplay,u8* command){
    ES_t Local_ESErrorState = ES_OUT_OF_RANGE;
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RSPort, LCD_pstructDisplay->LCD_u8RSPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RWPort, LCD_pstructDisplay->LCD_u8RWPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = LCD_enuReadBits(LCD_pstructDisplay,command);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(LCD_pstructDisplay->LCD_u8Mode == LCD_u8MODE_4BIT){
        u8 Local_u8Temp = 0;
        _delay_ms(1);
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        _delay_ms(1);
        Local_ESErrorState = LCD_enuReadBits(LCD_pstructDisplay,&Local_u8Temp);
        *command |= Local_u8Temp>>4;
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    }
    return Local_ESErrorState;
}







static inline ES_t LCD_DisplayClear(LCD_t* LCD_pstructDisplay) {
    u8 command = 0b00000001;
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_ReturnHome(LCD_t* LCD_pstructDisplay) {
    u8 command = 0b00000010;
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_EntryModeSet(LCD_t* LCD_pstructDisplay,u8 I_D, u8 SH) {
    if(I_D > 1 || SH > 1) { return ES_OUT_OF_RANGE; }
    u8 command = 0b00000100|I_D<<1|SH;
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_DisplayOnOff(LCD_t* LCD_pstructDisplay,u8 D, u8 C, u8 B) {
    if(D > 1 || C > 1 || B > 1) { return ES_OUT_OF_RANGE; }
    u8 command = 0b00001000|D<<2|C<<1|B;
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_enuFunctionSet(LCD_t* LCD_pstructDisplay,u8 DL, u8 N, u8 F) {
    if(DL > 1 || N > 1 || F > 1) { return ES_OUT_OF_RANGE; }
    u8 command = 0b00100000|DL<<4|N<<3|F<<2;
    u8 Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RSPort, LCD_pstructDisplay->LCD_u8RSPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8RWPort, LCD_pstructDisplay->LCD_u8RWPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = LCD_enuWriteBits(LCD_pstructDisplay,command);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8HIGH);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _delay_ms(1);
    Local_ESErrorState = DIO_enuSetPinValue(LCD_pstructDisplay->LCD_u8EPort, LCD_pstructDisplay->LCD_u8EPin, DIO_u8LOW);
    if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_SetCGRAMAddress(LCD_t* LCD_pstructDisplay,u8 Address) {
    if(Address > 0x3F) { return ES_OUT_OF_RANGE; }
    u8 command = 0b01000000|Address;
    return LCD_enuWriteCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_SetDDRAMAddress(LCD_t* LCD_pstructDisplay,u8 Address) {
    if(Address > 0x27) { return ES_OUT_OF_RANGE; }
    u8 command = 0b10000000|Address;
    return LCD_enuWriteCommand(LCD_pstructDisplay,0b10000000|Address);
}
static inline ES_t LCD_ReadBusyFlagAndAddress(LCD_t* LCD_pstructDisplay,u8* command) {
    u8 Local_u8Data = 0;
    return LCD_enuReadCommand(LCD_pstructDisplay,command);
}
static inline ES_t LCD_WriteDataToCGRAMOrDDRAM(LCD_t* LCD_pstructDisplay,u8 Data) {
    return LCD_enuWriteData(LCD_pstructDisplay,Data);
}
static inline ES_t LCD_ReadDataFromCGRAMOrDDRAM(LCD_t* LCD_pstructDisplay, u8* Data) {
    u8 Local_u8Data = 0;
    return LCD_enuReadData(LCD_pstructDisplay,Data);
}








ES_t LCD_enuInit(void){
    ES_t Local_ESErrorState = ES_NOK;
    _delay_ms(30);
    for(u8 Local_u8Counter = 0; Local_u8Counter < LCD_u8DisplayNum; Local_u8Counter++){
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8RSPort, LCD_AstructDisplays[Local_u8Counter].LCD_u8RSPin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8RWPort, LCD_AstructDisplays[Local_u8Counter].LCD_u8RWPin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8EPort, LCD_AstructDisplays[Local_u8Counter].LCD_u8EPin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB4Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB4Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB5Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB5Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB6Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB6Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB7Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB7Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        if(LCD_AstructDisplays[Local_u8Counter].LCD_u8Mode == LCD_u8MODE_4BIT) goto _4bitmode;
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB0Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB0Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB1Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB1Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB2Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB2Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        Local_ESErrorState = DIO_enuSetPinDirection(LCD_AstructDisplays[Local_u8Counter].LCD_u8DB3Port, LCD_AstructDisplays[Local_u8Counter].LCD_u8DB3Pin, DIO_u8OUTPUT);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    _4bitmode: 
        // set function
        Local_ESErrorState = LCD_enuFunctionSet(&LCD_AstructDisplays[Local_u8Counter],LCD_AstructDisplays[Local_u8Counter].LCD_u8Mode,LCD_AstructDisplays[Local_u8Counter].LCD_u8LinesNum,LCD_AstructDisplays[Local_u8Counter].LCD_u8BlockSize);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        // delay 1ms
        _delay_ms(1);
        // display on/off control
        Local_ESErrorState = LCD_DisplayOnOff(&LCD_AstructDisplays[Local_u8Counter],1,LCD_AstructDisplays[Local_u8Counter].LCD_u8Cursor,LCD_AstructDisplays[Local_u8Counter].LCD_u8CursorBlink);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        // delay 1ms
        _delay_ms(1);
        // clear display
        Local_ESErrorState = LCD_DisplayClear(&LCD_AstructDisplays[Local_u8Counter]);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
        // delay 2ms
        _delay_ms(2);
        // entry mode set
        Local_ESErrorState = LCD_EntryModeSet(&LCD_AstructDisplays[Local_u8Counter],1,0);
        if(Local_ESErrorState != ES_OK) { return Local_ESErrorState; }
    }
    return Local_ESErrorState;
}
ES_t LCD_enuGotoPosition(LCD_t* LCD_pstructDisplay,u8 x,u8 y){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    if(x > LCD_pstructDisplay->LCD_u8LinesNum || y > 15) { return ES_OUT_OF_RANGE; }
    return LCD_SetDDRAMAddress(LCD_pstructDisplay,0b10000000|((x-1)*0x40)+y);
}
ES_t LCD_enuWriteChar(LCD_t* LCD_pstructDisplay,u8 Data){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    return LCD_WriteDataToCGRAMOrDDRAM(LCD_pstructDisplay,Data);
}
ES_t LCD_enuClear(LCD_t* LCD_pstructDisplay){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    return LCD_DisplayClear(LCD_pstructDisplay);
}
ES_t LCD_enuDisplayOn(LCD_t* LCD_pstructDisplay){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    return LCD_DisplayOnOff(LCD_pstructDisplay,1,LCD_pstructDisplay->LCD_u8Cursor,LCD_pstructDisplay->LCD_u8CursorBlink);
}
ES_t LCD_enuDisplayOff(LCD_t* LCD_pstructDisplay){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    return LCD_DisplayOnOff(LCD_pstructDisplay,0,0,0);
}
ES_t LCD_enuSendWriteCommand(LCD_t* LCD_pstructDisplay,u8 Command){
    if (LCD_pstructDisplay == NULL) { return ES_NULL_POINTER;}
    if (LCD_pstructDisplay<LCD_AstructDisplays || LCD_pstructDisplay>(LCD_AstructDisplays+sizeof(LCD_t)*LCD_u8DisplayNum)) { return ES_OUT_OF_RANGE; }
    if(Command > 0b11111111) { return ES_OUT_OF_RANGE; }
    return LCD_enuWriteCommand(LCD_pstructDisplay,Command);
}

