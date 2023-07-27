#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
/**
 * @file DIO_interface.h
 * @brief This file contains the interface for the DIO driver.
 *
 * This driver is responsible for controlling the digital input/output pins of the AVR microcontroller.
 * It provides functions to initialize the pins' direction and value, set and get the value of a single pin or a whole port,
 * toggle the value of a single pin or a whole port, and set the direction of a single pin.
 */

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

// ARGUMENTS
#define DIO_u8INPUT  0
#define DIO_u8OUTPUT 1

#define DIO_u8LOW  0
#define DIO_u8HIGH 1
#define DIO_u8FLOAT 0
#define DIO_u8PULL_UP 1

#define DIO_u8PORTA 3
#define DIO_u8PORTB 2
#define DIO_u8PORTC 1
#define DIO_u8PORTD 0

#define DIO_u8DDRA 3
#define DIO_u8DDRB 2
#define DIO_u8DDRC 1
#define DIO_u8DDRD 0

#define DIO_u8PINA 3
#define DIO_u8PINB 2
#define DIO_u8PINC 1
#define DIO_u8PIND 0

#define DIO_u8PIN0 0
#define DIO_u8PIN1 1
#define DIO_u8PIN2 2
#define DIO_u8PIN3 3
#define DIO_u8PIN4 4
#define DIO_u8PIN5 5
#define DIO_u8PIN6 6
#define DIO_u8PIN7 7


/**
 * @brief Initializes the direction and value of all the digital pins according to the configuration in DIO_CONFIG.h file.
 */
void DIO_voidInit(void);

/**
 * @brief Sets the direction of a whole port.
 * 
 * @param Copy_u8PortID The ID of the port to set its direction.
 * @param Copy_u8Direction The direction to set for the port.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If setting the direction is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8Direction is out of range.
 */
ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Direction);

/**
 * @brief Sets the value of a whole port.
 * 
 * @param Copy_u8PortID The ID of the port to set its value.
 * @param Copy_u8Value The value to set for the port.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If setting the value is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8Direction is out of range.
 */
ES_t DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Value);

/**
 * @brief Gets the value of a whole port.
 * 
 * @param Copy_u8PortID The ID of the port to get its value.
 * @param Copy_pu8Value Pointer to a variable to store the value of the port.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If getting the value is successful.
 *         - ES_NULL_POINTER: If Copy_pu8Value is a null pointer.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID is out of range.
 */
ES_t DIO_enuGetPortValue(u8 Copy_u8PortID, u8 *Copy_pu8Value);

/**
 * @brief Toggles the value of a whole port.
 * 
 * @param Copy_u8PortID The ID of the port to toggle its value.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If toggling the value is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID is out of range.
 */
ES_t DIO_enuTogglePortValue(u8 Copy_u8PortID);

/**
 * @brief Sets the direction of a single pin.
 * 
 * @param Copy_u8PortID The ID of the port the pin belongs to.
 * @param Copy_u8PinID The ID of the pin to set its direction.
 * @param Copy_u8Value The direction to set for the pin.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If setting the direction is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8PinID is out of range, or if Copy_u8Value is not a valid direction.
 */
ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID,u8 Copy_u8Value);

/**
 * @brief Sets the value of a single pin.
 * 
 * @param Copy_u8PortID The ID of the port the pin belongs to.
 * @param Copy_u8PinID The ID of the pin to set its value.
 * @param Copy_u8Value The value to set for the pin.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If setting the value is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8PinID is out of range, or if Copy_u8Value is not a valid value.
 */
ES_t DIO_enuSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value);

/**
 * @brief Gets the value of a single pin.
 * 
 * @param Copy_u8PortID The ID of the port the pin belongs to.
 * @param Copy_u8PinID The ID of the pin to get its value.
 * @param Copy_pu8Value Pointer to a variable to store the value of the pin.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If getting the value is successful.
 *         - ES_NULL_POINTER: If Copy_pu8Value is a null pointer.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8PinID is out of range.
 */
ES_t DIO_enuGetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 *Copy_pu8Value);

/**
 * @brief Toggles the value of a single pin.
 * 
 * @param Copy_u8PortID The ID of the port the pin belongs to.
 * @param Copy_u8PinID The ID of the pin to toggle its value.
 * 
 * @return ES_t Error status.
 *         - ES_OK: If toggling the value is successful.
 *         - ES_OUT_OF_RANGE: If Copy_u8PortID or Copy_u8PinID is out of range.
 */
ES_t DIO_enuTogglePinValue(u8 Copy_u8PortID, u8 Copy_u8PinID);

#endif /* DIO_INTERFACE_H_ */
