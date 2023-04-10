#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"

// ARGUMENTS

// Interrupt IDs
#define EXTI_u8INT0    0
#define EXTI_u8INT1    1
#define EXTI_u8INT2    2
// Sense Control
#define LEVEL_LOW      0b11111100
#define LEVEL_CHANGE   0b11111101
#define FALLING_EDGE   0b11111110
#define RISING_EDGE    0b11111111


// EXTI_u8InterruptID : EXTI_u8INT0, EXTI_u8INT1, EXTI_u8INT2
// EXTI_FptrCallback  : pointer to function to be called when interrupt occurs
ES_t EXTI_enuInitInterrupt(u8 EXTI_u8InterruptID, void (*EXTI_FptrCallback)(void));

// EXTI_u8InterruptID : EXTI_u8INT0, EXTI_u8INT1, EXTI_u8INT2
// Sense Control      : LEVEL_LOW, LEVEL_CHANGE, FALLING_EDGE, RISING_EDGE
ES_t EXTI_enuSetSenseControl(u8 EXTI_u8InterruptID, u8 EXTI_u8SenseControl);

// EXTI_u8InterruptID : EXTI_u8INT0, EXTI_u8INT1, EXTI_u8INT2
//// This function does NOT enable the Global Interrupt ////
ES_t EXTI_enuEnableInterrupt(u8 EXTI_u8InterruptID); 

// EXTI_u8InterruptID : EXTI_u8INT0, EXTI_u8INT1, EXTI_u8INT2
ES_t EXTI_enuDisableInterrupt(u8 EXTI_u8InterruptID);

#endif // !EXTI_INTERFACE_H
