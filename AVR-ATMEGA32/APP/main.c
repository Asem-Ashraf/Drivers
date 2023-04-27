#include <util/delay.h>
#include "../LIB/Bit_Math.h"
#include "../LIB/stdTypes.h"
#include "../LIB/ErrorStates.h"

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/GIE/GIE_INTERFACE.h"
#include "../MCAL/ADC/ADC_INTERFACE.h"
#include "../MCAL/EXTI/EXTI_INTERFACE.h"

#include "../HAL/LCD/LCD_INTERFACE.h"
#include "../HAL/LED/LED_INTERFACE.h"
#include "../HAL/SWITCH/SW_INTERFACE.h"
#include "../HAL/7_SEG/SEVEN_SEG_INTERFACE.h"

extern LED_t LED_AstructLed[];
ES_t gerror=ES_OK;

u16 ADC_u16Result = 0;  
u8 ADC_u8Result = 0;  

void callback(void) {
    gerror = ADC_enuGetHighValue(&ADC_u8Result);
    if (gerror != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);
    gerror = DIO_enuSetPortValue(DIO_u8PORTC,ADC_u8Result);
    if (gerror != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);
}
int main() {
    ES_t error = ES_NOK;
    error = DIO_enuInit();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = LED_enuInit(LED_AstructLed);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuInit(ADC_u8PRESCALER_128, ADC_u8LEFT_ADJ,ADC_u8AVCC);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuSetChannel(ADC_u8CH0);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = DIO_enuSetPortDirection(DIO_u8PORTC,DIO_u8OUTPUT);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuSetTrigger(ADC_u8FREE_RUNNING);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuStartOneConversion();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuSetCallBack(&callback);
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = ADC_enuEnableInterrupt();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    error = GIE_enuEnable();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }

    _delay_ms(5000);
    error = ADC_enuDisableTrigger();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    _delay_ms(5000);
    error = ADC_enuStartOneConversion();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    _delay_ms(5000);
    error = ADC_enuDisableInterrupt();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = ADC_enuStartOneConversion();
    if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = DIO_enuSetPortValue(DIO_u8PORTC,0);
    if (error != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);
    _delay_ms(5000);
    error = ADC_enuGetHighValue(&ADC_u8Result);
    if (error != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);
    error = DIO_enuSetPortValue(DIO_u8PORTC,ADC_u8Result);
    if (error != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);

    while (1) {
    error = ADC_enuGetHighValue(&ADC_u8Result);
    if (error != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);
    error = DIO_enuSetPortValue(DIO_u8PORTC,ADC_u8Result);
    if (error != ES_OK) LED_enuTurnOn(&LED_AstructLed[0]);

    }
}
