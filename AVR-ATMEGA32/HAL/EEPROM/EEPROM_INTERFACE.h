#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

typedef struct {
    u8 EEPROM_u8SlaveAddress;
    u8 EEPROM_u8PageSize;
    u8 EEPROM_u8PageCount;
}EEPROM_t;



/**
 * @brief: This function initializes the EEPROM module and checks for false 
 *         EEPROM configurations
 * @return: Error state
 * @note: The I2C protocol must be initialized before using this function
 */
ES_t EEPROM_enuInit();

/**
 * @brief: This function Write a byte in the EEPROM according to the address
 *
 *
 * @param: Copy_pstructEEPROMChip: A pointer to the EEPROM struct that contains 
 *                                 the slave address and the page size
 * @param: Copy_u8Address: The address of the byte to be written
 * @param: Copy_u8Data: The data to be written
 * @return: Error state
 *      - ES_OK: The function is executed successfully
 *      - ES_NUL_POITNTER: A null pointer is passed to the function
 *      - ES_EEPROM_I2C_FAILED: I2C communication did not run as expected
 *
 * @note: The I2C protocol must be initialized before using this function
 *        This function does not neet a delay function to run after it as it
 *        uses ack polling to check if the write operation is done or not.
 */
ES_t EEPROM_enuWriteByte(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8Address, u8 Copy_u8Data);

/**
 * @brief: This function Write a page in the EEPROM according to the address
 *
 * This function writes on EEPROM starting from Copy_u8StartAddress. See EEPROM
 * datasheet for more details about the internal address increment mechanism.
 *
 * @param: Copy_pstructEEPROMChip: A pointer to the EEPROM struct that contains the
 *                                 slave address and the page size
 * @param: Copy_u8StartAddress: The address of the page to be written
 * @param: Copy_Au8Data: The pointer to the array of data to be written
 * @param: Copy_u8Size: The size of the page
 * @return: Error state
 * @note: The I2C protocol must be initialized before using this function
 */
ES_t EEPROM_enuWritePage(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8StartAddress, u8 *Copy_Au8Data, u8 Copy_u8Size);


/**
 * @brief: This function Read a byte from the EEPROM at the current address
 *
 * The current address is the last address that was written to or read from + 1
 *
 * @param: Copy_pstructEEPROMChip: A pointer to the EEPROM struct that contains the
 *                                 slave address and the page size
 * @param: Copy_u8Address: The address of the byte to be read
 * @param: Copy_u8Data: The data to be read
 * @return: Error state
 * @note: The I2C protocol must be initialized before using this function
 */
ES_t EEPROM_enuReadImmediateByte(EEPROM_t* Copy_pstructEEPROMChip, u8 *Copy_u8Data);

/**
 * @brief: This function Read a byte in the EEPROM according to the address
 *
 * @param: Copy_pstructEEPROMChip: A pointer to the EEPROM struct that contains the
 *                                 slave address and the page size
 * @param: Copy_u8Address: The address of the byte to be read
 * @param: Copy_u8Data: The data to be read
 * @return: Error state
 * @note: The I2C protocol must be initialized before using this function
 */
ES_t EEPROM_enuReadByte(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8Address, u8 *Copy_u8Data);

/**
 * @brief: This function Read a page in the EEPROM according to the address
 *
 * This function reads from the EEPROM starting from Copy_u8StartAddress. See EEPROM
 * datasheet for more details about the internal address increment mechanism.
 *
 * @param: Copy_pstructEEPROMChip: A pointer to the EEPROM struct that contains the
 *                                 slave address and the page size
 * @param: Copy_u8Address: The address of the page to be read
 * @param: Copy_u8AData: The pointer to an array to which the data will be read
 * @param: Copy_u8Size: The number of bytes to be read. This must be less or 
 *                      equal to the array the pointer Copy_Au8Data points to.
 * @return: Error state
 * @note: The I2C protocol must be initialized before using this function
 */
ES_t EEPROM_enuReadPage(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8StartAddress, u8 *Copy_Au8Data, u8 Copy_u8Size);

#endif
