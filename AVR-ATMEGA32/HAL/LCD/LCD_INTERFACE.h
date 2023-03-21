#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/Bit_Math.h"
#include "../../LIB/ErrorStates.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LCD_CONFIG.h"

/* LCD Commands */
ES_t LCD_enuInit(void);

ES_t LCD_enuGotoPosition(LCD_t* LCD_pstructDisplay,u8 x,u8 y);

ES_t LCD_enuWriteChar(LCD_t* LCD_pstructDisplay,u8 Data);

ES_t LCD_enuClear(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOn(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOff(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuSendCommand(LCD_t* LCD_pstructDisplay,u8 Command);


#endif /* LCD_INTERFACE_H_ */
