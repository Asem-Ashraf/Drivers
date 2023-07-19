/* Author: Asem Ashraf
 * Purpose: UART Driver Interface
 * This file contains all the interfacing information of UART Driver along with
 * doxygen documentation.
 */
#ifndef UART_INTERFACE_H__
#define UART_INTERFACE_H__

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

#define UART_5BIT_DATA          0
#define UART_6BIT_DATA          1
#define UART_7BIT_DATA          2
#define UART_8BIT_DATA          3
#define UART_9BIT_DATA          4

#define UART_PARITY_DISABLED    0
#define UART_PARITY_EVEN        1
#define UART_PARITY_ODD         2

#define UART_1STOP_BIT          0
#define UART_2STOP_BIT          1

#define UART_DOUBLE_SPEED_OFF   0
#define UART_DOUBLE_SPEED_ON    1

/**
 * @brief  UART Initialization. 
 *
 * @param  Copy_u32BaudRate: Baud Rate of the UART.
 *
 * @param  Copy_u8DataBits: Data Bits of the UART.
 * @values UART_5BIT_DATA
 *         UART_6BIT_DATA
 *         UART_7BIT_DATA
 *         UART_8BIT_DATA
 *         UART_9BIT_DATA
 *
 * @param  Copy_u8Parity: Parity of the UART.
 * @values UART_PARITY_DISABLED
 *         UART_PARITY_EVEN
 *         UART_PARITY_ODD
 *
 * @param  Copy_u8StopBits: Stop Bits of the UART.
 * @values UART_1STOP_BIT
 *         UART_2STOP_BIT
 *
 * @param  Copy_u8DoubleSpeed: Double Speed of the UART.
 * @values UART_DOUBLE_SPEED_ON
 *         UART_DOUBLE_SPEED
 *
 * @return ES_OUT_OF_RANGE: If any of the parameters are out of range.
 *         ES_NOT_OK: If the UART is not initialized.
 *         ES_OK: If the UART is initialized successfully.
 */
ES_t UART_enuInit(u32 Copy_u32BaudRate, u8 Copy_u8DataBits, u8 Copy_u8Parity,
                  u8 Copy_u8StopBits, u8 Copy_u8DoubleSpeed);


/**
 * @brief  UART Transmit Unit Enable.
 */
void UART_voidEnableTransmitUnit(void);


/**
 * @brief  UART Transmit Data.
 *         This function is used to transmit 8-bit data.
 *         This function is used only if the UART is initialized with 8-bit data.
 *         This function is blocking.
 *
 * @param  Copy_u8Data: Data to be transmitted.
 *
 */
void UART_voidTransmit(u8 Copy_u8Data);


/**
 * @brief  UART Transmit 9-bit Data.
 *         This function is used to transmit 9-bit data.
 *         This function is used only if the UART is initialized with 9-bit data.
 *         This function is blocking.
 *         If the value is more than 9 bits, the function will take the LSBs.
 *
 * @param  Copy_u16Data: 9-bit Data to be transmitted.
 *
 */
void UART_voidTransmit9bit(u16 Copy_u16Data);


/**
 * @brief  UART Transmit Complete Interrupt Enable.
 */
void UART_voidEnableTransmitCompleteInterrupt(void);


/**
 * @brief  UART Transmit Complete Interrupt Set Call Back.
 *
 * @param  Copy_pvCallBack: Pointer to function to be called when the interrupt
 *                          is fired.
 *
 * @return ES_NULL_POINTER: If the pointer is NULL.
 *         ES_OK: If the pointer is not NULL.
 */
ES_t UART_enuSetTransmitCompleteCallBack(void (*Copy_pvCallBack)(void));


/**
 * @brief  UART Transmit Complete Interrupt Disable.
 */
void UART_voidDisableTransmitCompleteInterrupt(void);


/**
 * @brief  UART Transmit Register Empty Interrupt Enable.
 */
void UART_voidEnableTransmitRegisterEmptyInterrupt(void);


/**
 * @brief  UART Transmit Register Empty Interrupt Set Call Back.
 *
 * @param  Copy_pvCallBack: Pointer to function to be called when the interrupt
 *                          is fired.
 *
 * @return ES_NULL_POINTER: If the pointer is NULL.
 *         ES_OK: If the pointer is not NULL.
 */
ES_t UART_enuSetTransmitRegisterEmptyCallBack(void (*Copy_pvCallBack)(void));


/**
 * @brief  UART Transmit Register Empty Interrupt Disable.
 */
void UART_voidDisableTransmitRegisterEmptyInterrupt(void);


/**
 * @brief  UART Transmit Unit Disable.
 */
void UART_voidDisableTransmitUnit(void);



/**
 * @brief  UART Receive Unit Enable.
 */
void UART_voidEnableReceiveUnit(void);


/**
 * @brief  UART Receive Data.
 *        This function is used to receive 8-bit data.
 *        This function is used only if the UART is initialized with 8-bit data.
 *        This function is blocking.
 *
 * @return 8-bit Data received.
 */
u8 UART_enuReceive();


/**
 * @brief  UART Receive 9-bit Data.
 *         This function is used to receive 9-bit data.
 *         This function is used only if the UART is initialized with 9-bit data.
 *         This function is blocking.
 *
 * @return 9-bit Data received in a 16-bit variable.
 */
u16 UART_enuReceive9bit();


/**
 * @brief  UART Receive Complete Interrupt Enable.
 */
void UART_voidEnableReceiveCompleteInterrupt(void);


/**
 * @brief  UART Receive Complete Interrupt Set Call Back.
 *
 * @param  Copy_pvCallBack: Pointer to function to be called when the interrupt
 *                          is fired.
 *
 * @return ES_NULL_POINTER: If the pointer is NULL.
 *         ES_OK: If the pointer is not NULL.
 */
ES_t UART_enuSetReceiveCompleteCallBack(void (*Copy_pvCallBack)(void));


/**
 * @brief  UART Receive Complete Interrupt Disable.
 */
void UART_voidDisableReceiveCompleteInterrupt(void);


/**
 * @brief  UART Receive Register Empty Interrupt Enable.
 */
void UART_voidDisableReceiveUnit(void);



/**
 * @brief  Sends a string through the UART.
 *         This function is blocking.
 *         This function is used only if the UART is initialized with 8-bit data.
 *
 * @param  Copy_pu8Data: Pointer to the string to be transmitted.
 *                      The string must be terminated with '\0'.
 *
 * @return ES_NULL_POINTER: If the pointer is NULL.
 *         ES_OK: If the pointer is not NULL.
 */
ES_t UART_enuTransmitString(u8 * Copy_pu8Data);

#endif
