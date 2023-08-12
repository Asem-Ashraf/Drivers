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


/**
 * @brief Initialize all LEDs defined in LED_AstructLed array.
 * 
 * @param[in] Copy_AstructLed Pointer to an array of LED_t structures containing 
 *            the LED configurations.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Initialization successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer or LED configuration passed as argument.
 */
ES_t LED_enuInit();

/**
 * @brief Turn on an LED.
 * 
 * @param[in] Copy_pstructLed Pointer to a LED_t structure containing the LED 
 *            configuration.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Turn on operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer or LED configuration passed as argument.
 */
ES_t LED_enuTurnOn(LED_t* Copy_pstructLed);

/**
 * @brief Turn off an LED.
 * 
 * @param[in] Copy_pstructLed Pointer to a LED_t structure containing the LED configuration.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Turn off operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer or LED configuration passed as argument.
 */
ES_t LED_enuTurnOff(LED_t* Copy_pstructLed);

/**
 * @brief Toggle an LED.
 * 
 * @param[in] Copy_pstructLed Pointer to a LED_t structure containing the LED configuration.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Toggle operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer or LED configuration passed as argument.
 */
ES_t LED_enuToggle(LED_t* Copy_pstructLed);

#endif
