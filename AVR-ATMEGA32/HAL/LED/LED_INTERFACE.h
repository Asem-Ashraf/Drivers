#ifndef LED_INT_H_
#define LED_INT_H_
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

typedef struct {
    u8 LED_u8PORTID;        // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 LED_u8PINID;         // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
    u8 LED_u8Connection;    // LED_u8SINK, LED_u8SOURCE
    u8 LED_u8InitState;     // LED_u8ON, LED_u8OFF
}LED_t;


// LED_AstructLed  : pointer to the LED Array
ES_t LED_enuInit      (LED_t* LED_AstructLed);


// LED_AstructLed  : pointer to a LED struct
ES_t LED_enuTurnOn    (LED_t* LED_pstructLed);


// LED_AstructLed  : pointer to a LED struct
ES_t LED_enuTurnOff   (LED_t* LED_pstructLed);


// LED_AstructLed  : pointer to a LED struct
ES_t LED_enuToggle    (LED_t* LED_pstructLed);


#endif
