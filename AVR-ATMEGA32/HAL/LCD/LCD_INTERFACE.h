#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* LCD Commands */
ES_t LCD_enuInit(void);

ES_t LCD_enuGotoPosition(LCD_t* LCD_pstructDisplay,u8 x,u8 y);

ES_t LCD_enuWriteChar(LCD_t* LCD_pstructDisplay,u8 Data);

ES_t LCD_enuClear(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOn(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuDisplayOff(LCD_t* LCD_pstructDisplay);

ES_t LCD_enuSendWriteCommand(LCD_t* LCD_pstructDisplay,u8 Command);


#endif /* LCD_INTERFACE_H_ */
