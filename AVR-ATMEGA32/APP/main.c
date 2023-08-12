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

extern LED_t LED_AstructLed[];
extern TH_t TH_AstuThemistors[];
extern LCD_t LCD_AstructDisplays[];

int main() {
    ES_t error = ES_NOK;
    error = LED_enuInit(LED_AstructLed);
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    DIO_voidInit();
    error = ADC_enuInit(ADC_u8PRESCALER_128, ADC_u8RIGHT_ADJ,ADC_u8AVCC); 
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = TH_enuInit(TH_AstuThemistors);
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = ADC_enuSetChannel(TH_AstuThemistors[0].TH_u8PINID);
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = LCD_enuInit();
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    f32 f32temp;
    char str[20];
    while (1) {
        error = TH_enuGetTemp(&TH_AstuThemistors[0], &f32temp);
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
        floatToString(f32temp, str,8);
        error = LCD_enuGotoPosition(&LCD_AstructDisplays[0], 1, 0);
        LCD_enuWriteString(&LCD_AstructDisplays[0], (u8*)str);
        _delay_ms(3000);
        error = LCD_enuClear(&LCD_AstructDisplays[0]);
            if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    }
}
