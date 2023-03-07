#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#include "../../LIB/stdTypes.h"

#define LED_u8NUM_OF_LEDS  1

typedef struct {
    u8 LED_u8PORTID; // PORTA, PORTB, PORTC, PORTD
    u8 LED_u8PINID;  // PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7
}LED_t;

#endif
