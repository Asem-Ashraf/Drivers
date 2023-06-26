/**
 * @file GIE_interface.h
 * @brief This file contains the interface for the General Interrupt Enable 
 * (GIE) driver.
 *        The GIE driver provides functions for enabling and disabling 
 *        interrupts on the AVR microcontroller.
 */

#ifndef GIE_INTERFACE_H
#define GIE_INTERFACE_H

/**
 * @brief Enables global interrupts on the AVR microcontroller.
 *        This function enables global interrupts on the AVR microcontroller by
 *        setting the Global Interrupt Enable (GIE) bit in the Status Register 
 *        (SREG).
 * @param None.
 * @return None.
 */
#define GIE_Enable() asm("SEI")

/**
 * @brief Disables global interrupts on the AVR microcontroller.
 *        This function disables global interrupts on the AVR microcontroller by
 *        clearing the Global Interrupt Enable (GIE) bit in the Status Register
 *        (SREG).
 * @param None.
 * @return None.
 */
#define GIE_Disable() asm("CLI")

#endif // !GIE_INTERFACE_H
