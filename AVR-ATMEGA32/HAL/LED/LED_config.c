#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "LED_config.h"

#define LED_u8NUMOFLEDS 1

u8 LED_u8NUM_OF_LEDS=LED_u8NUMOFLEDS;
LED_t LED_AstructLed[LED_u8NUMOFLEDS] = {
    {DIO_u8PORTA, DIO_u8PIN1,LED_u8SINK, LED_u8OFF}
};
