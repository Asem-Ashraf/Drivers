#ifndef SW_INIT_H
#define SW_INIT_H
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

typedef struct{
    u8 SW_u8Mode;   // DIO_u8pull_up or DIO_u8FLOAT
    u8 SW_u8PORTID; // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 SW_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}SW_t;


/**
 * @brief Initialize all switches defined in SW_AstuSwitches array.
 * 
 * @param[in] Copy_AstructSwitchs Pointer to an array of SW_t structures containing the switch configurations.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Initialization successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer passed as argument.
 */
ES_t SW_enuInit(SW_t* Copy_AstructSwitchs);

/**
 * @brief Get the current state of a switch.
 * 
 * @param[in] Copy_pstructSwitch Pointer to a SW_t structure containing the switch configuration.
 * @param[out] pu8State Pointer to a variable that will hold the switch state (0 or 1).
 * 
 * @return ES_t Error status.
 *         - ES_OK: Get state operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer passed as argument.
 */
ES_t SW_enuGetState(SW_t* Copy_pstructSwitch, u8 *pu8State);

/**
 * @brief Set the mode of a switch (pull-up or floating).
 * 
 * @param[in] Copy_pstructSwitch Pointer to a SW_t structure containing the switch configuration.
 * @param[in] Copy_u8Mode Mode to set the switch to (DIO_u8pull_up or DIO_u8FLOAT).
 * 
 * @return ES_t Error status.
 *         - ES_OK: Set mode operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer passed as argument.
 */
ES_t SW_enuSetMode(SW_t* Copy_pstructSwitch, u8 Copy_u8Mode);

#endif // SW_INIT_H
