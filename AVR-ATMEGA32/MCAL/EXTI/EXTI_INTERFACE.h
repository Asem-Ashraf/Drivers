#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
/**
 * @file EXTI_Interface.h
 *
 * @brief This file contains the interface for configuring and controlling external interrupts (EXTI) in a microcontroller.
 */


#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

// Interrupt IDs
/**< External interrupt 0 */
#define EXTI_u8INT0    0
/**< External interrupt 1 */
#define EXTI_u8INT1    1
/**< External interrupt 2 */
#define EXTI_u8INT2    2

// Sense Control
/**< Low level sense control */
#define EXTI_u8LEVEL_LOW      0b00000000
/**< Sense control on any logical change */
#define EXTI_u8LEVEL_CHANGE   0b00000001
/**< Falling edge sense control */
#define EXTI_u8FALLING_EDGE   0b00000010
/**< Rising edge sense control */
#define EXTI_u8RISING_EDGE    0b00000011


/**
 * @brief Initializes an external interrupt.
 *
 * This function initializes the specified external interrupt with the provided callback function.
 *
 * @param EXTI_u8InterruptID - The ID number of the external interrupt to be initialized.
 * @param EXTI_FptrCallback - A pointer to the function to be called when the interrupt occurs.
 *
 * @return ES_t - Error status.
 *         ES_OK if the interrupt is initialized successfully, otherwise if unsuccessful.
 */
ES_t EXTI_enuInitInterrupt(u8 EXTI_u8InterruptID, void (*EXTI_FptrCallback)(void));


/**
 * @brief Sets the sense control for an external interrupt.
 *
 * This function sets the sense control for the specified external interrupt.
 *
 * @param EXTI_u8InterruptID - The ID number of the external interrupt to set the sense control for.
 *        EXTI_u8SenseControl - The sense control to be set for the external interrupt (LEVEL_LOW, LEVEL_CHANGE, FALLING_EDGE, or RISING_EDGE).
 *
 * @return ES_t - Error status.
 *         ES_OK if the sense control is set successfully, ES_NOK otherwise.
 */
ES_t EXTI_enuSetSenseControl(u8 EXTI_u8InterruptID, u8 EXTI_u8SenseControl);


/**
 * @brief Enables an external interrupt.
 *
 * This function enables the specified external interrupt.
 *
 * @param EXTI_u8InterruptID - The ID number of the external interrupt to be enabled.
 *
 * @return ES_t - Error status.
 *         ES_OK if the interrupt is enabled successfully, ES_NOK otherwise.
 */
ES_t EXTI_enuEnableInterrupt(u8 EXTI_u8InterruptID);


/**
 * @brief Disables an external interrupt.
 *
 * This function disables the specified external interrupt.
 *
 * @param EXTI_u8InterruptID - The ID number of the external interrupt to be disabled.
 *
 * @return ES_t - Error status.
 *         ES_OK if the interrupt is disabled successfully, ES_NOK otherwise.
 */
ES_t EXTI_enuDisableInterrupt(u8 EXTI_u8InterruptID);

#endif // !EXTI_INTERFACE_H
