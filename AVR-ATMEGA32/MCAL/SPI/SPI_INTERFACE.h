#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

#define SPI_u8MSB_FIRST       0b00000000
#define SPI_u8LSB_FIRST       0b00100000

#define SPI_u8RISING_LEADING  0b00000000
#define SPI_u8RISING_TRAILING 0b00001000

#define SPI_u8SAMPLE_LEADING  0b00000000
#define SPI_u8SAMPLE_TRAILING 0b00000100

#define SPI_u8CLK_4           0b00000000
#define SPI_u8CLK_16          0b00000001
#define SPI_u8CLK_64          0b00000010
#define SPI_u8CLK_128         0b00000011

#define SPI_u8CLK_1X          0b00000000
#define SPI_u8CLK_2X          0b00000001

#define SPI_u8MASTER_INPUT_ONLY   0
#define SPI_u8MASTER_INPUT_OUTPUT 1

#define SPI_u8SLAVE_INPUT_ONLY    0
#define SPI_u8SLAVE_INPUT_OUTPUT  1


/**
* @brief: This function initializes the SPI as a master
*
*           The Function does not control the slave select. Selecting the slave
*           must be managed by the user.
*           The functions of the SS, MISO, and SCK pins are overridden by the
*           SPI peripheral.
*         
* @param Copy_u8SBFirst: Selects whether the data is sent MSB first or LSB first
* @value SPI_u8MSB_FIRST,
*        SPI_u8LSB_FIRST
*
* @param Copy_u8DoubleSpeed: Selects the clock divider
* @value SPI_u8CLK_1X,
*        SPI_u8CLK_2X
*
* @param Copy_u8ClkRate: Selects the clock rate
* @value SPI_u8CLK_4,
*        SPI_u8CLK_16,
*        SPI_u8CLK_64,
*        SPI_u8CLK_128
*
* @param Copy_u8ClkPol: Selects the clock polarity
* @value SPI_u8RISING_LEADING,
*        SPI_u8RISING_TRAILING
*
* @param Copy_u8ClkPh: Selects the clock phase
* @value SPI_u8SAMPLE_LEADING,
*        SPI_u8SAMPLE_TRAILING
*
* @param Copy_u8Duplex: Selects the duplex mode
* @value SPI_u8MASTER_INPUT_ONLY,
*        SPI_u8MASTER_INPUT_OUTPUT
*
* return: Error state
*      ES_OK: No error,
*      ES_OUT_OF_RANGE: Out of range error
*/
ES_t SPI_enuMasterInit(u8 Copy_u8SBFirst, u8 Copy_u8DoubleSpeed, 
                       u8 Copy_u8ClkRate, u8 Copy_u8ClkPol, u8 Copy_u8ClkPh, 
                       u8 Copy_u8Duplex);

/**
* @brief: This function initializes the SPI as a slave
*
*           The functions of the SS, MOSI, and SCK pins are 
*           overridden by the SPI peripheral.
*
* @param Copy_u8SBFirst: Selects whether the data is sent MSB first or LSB first
* @value SPI_u8MSB_FIRST,
*        SPI_u8LSB_FIRST
*
* @param Copy_u8ClkPol: Selects the clock polarity
* @value SPI_u8RISING_LEADING,
*        SPI_u8RISING_TRAILING
*
* @param Copy_u8ClkPh: Selects the clock phase
* @value SPI_u8SAMPLE_LEADING,
*        SPI_u8SAMPLE_TRAILING
*
* @param Copy_u8Duplex: Selects the duplex mode
* @value SPI_u8SLAVE_INPUT_ONLY,
*        SPI_u8SLAVE_INPUT_OUTPUT
*
* return: Error state
*    ES_OK: No error,
*    ES_OUT_OF_RANGE: Out of range error
*/
ES_t SPI_enuSlaveInit(u8 Copy_u8SBFirst, u8 Copy_u8ClkPol, u8 Copy_u8ClkPh, 
                      u8 Copy_u8Duplex);

/**
* @brief: This function starts the SPI based on the settings used in the init 
*         fucntion.
*/
void SPI_voidStart(void);

/**
* @brief: This function stops the SPI without changing its settings.
*/
void SPI_voidStop(void);


/**
 * @brief: This function sets the callback function for the SPI interrupt
 *
 * @param Copy_pvCallBack: Pointer to the callback function
 *
 * return: Error state
 *     ES_OK: No error
 *     ES_NULL_POINTER: Null pointer error
 */
ES_t SPI_enuSetTransferCompleteCallback(void (*Copy_pvCallBack)(void));

/**
* @brief: This function enables the SPI interrupt.
*
* The callback function must be called before this function with a valid 
* function to run when the interrupt occurs.
*/
void SPI_voidEnableTransferCompleteInterrupt();

/**
* @brief: This function disables the SPI interrupt without changing the callback 
* function.
*/
void SPI_voidDisableTransferCompleteInterrupt();

/**
* @brief: This function sends a byte of data
*
* Can only be used when the SPI is configured to send.
*
* @param Copy_u8Data: The data to be sent
*/
void SPI_voidSendByte(u8 Copy_u8Data);

/**
* @brief: This function sends a byte of data
*
* The SPI is always configured as receive in the ATmega32.
*
* return: Received data
*/
u8 SPI_enuReceiveByte();

/**
* @brief: This function sends a byte of data and receives a byte of data
*         
* Can only be used when the SPI is configured to send and receives.
*
* @param Copy_u8SendData: The data to be sent
*
* return: Received data
*/
u8 SPI_enuSendReceiveByte(u8 Copy_u8SendData);

#endif
