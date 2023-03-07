#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "LED_config.h"

LED_t LED_AstructLed[LED_u8NUM_OF_LEDS] = {
    {DIO_u8PORTB, DIO_u8PIN0}
};
