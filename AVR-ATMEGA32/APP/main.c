#include <util/delay.h>
#include "../LIB/Bit_Math.h"
#include "../LIB/stdTypes.h"
#include "../LIB/ErrorStates.h"

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/ADC/ADC_INTERFACE.h"

#include "../HAL/LED/LED_INTERFACE.h"
#include "../HAL/LCD/LCD_INTERFACE.h"
#include "../HAL/Thermistor/TH_INTERFACE.h"

extern LED_t LED_AstructLed[];
extern TH_t TH_AstuThemistors[];
extern LCD_t LCD_AstructDisplays[];

void floatToString(float num, char* str, int precision) {
    int integerPart = (int)num;
    float decimalPart = num - (float)integerPart;
    int i = 0;

    // Convert integer part to string
    if (integerPart == 0) {
        str[i++] = '0';
    }
    else {
        int temp = integerPart;
        while (temp != 0) {
            int digit = temp % 10;
            str[i++] = digit + '0';
            temp /= 10;
        }
        int len = i;
        for (int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
    }

    // Add decimal point and convert decimal part to string
    if (precision != 0) {
        str[i++] = '.';
        for (int j = 0; j < precision; j++) {
            decimalPart *= 10;
            int digit = (int)decimalPart;
            str[i++] = digit + '0';
            decimalPart -= (float)digit;
        }
    }

    // Add null terminator
    str[i] = '\0';
}

int main() {
    ES_t error = ES_NOK;
    error = LED_enuInit(LED_AstructLed);
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    error = DIO_enuInit();
        if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
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
        for (int i =0; i<6; i++) {
            error = LCD_enuWriteChar(&LCD_AstructDisplays[0], str[i]);
                if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
        }
        _delay_ms(3000);
        error = LCD_enuClear(&LCD_AstructDisplays[0]);
            if (error != ES_OK)  { LED_enuTurnOn(&LED_AstructLed[0]); return 0; }
    }
}
