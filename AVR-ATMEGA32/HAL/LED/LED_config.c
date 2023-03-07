#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "LED_config.h"

u8 LED_u8NUM_OF_LEDS=1; // This number has to be equal to the number of elements in the array
LED_t LED_AstructLed[] = {
    {DIO_u8PORTB, DIO_u8PIN0,LED_u8SINK, LED_u8OFF}
};
