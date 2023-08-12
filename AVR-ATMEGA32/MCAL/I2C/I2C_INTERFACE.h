#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"


#define I2C_WRITE_OPERATION                             (0x00)
#define I2C_READ_OPERATION                              (0x01)

#define I2C_SEND_ACK                                    (0x01)
#define I2C_SEND_NACK                                   (0x00)


// MASTER MODE

// start condition transmitted
#define I2C_MASTER_START_SENT                           (0x08)
// repeated start condition transmitted 
#define I2C_MASTER_REPEATED_START_SENT                  (0x10)


// Master transmit

// SLA+W transmitted, ACK received
#define I2C_MASTER_SLA_W_SENT_ACK_RECEIVED              (0x18)
// SLA+W transmitted, NACK received
#define I2C_MASTER_SLA_W_SENT_NACK_RECEIVED             (0x20)

// Data transmitted, ACK received
#define I2C_MASTER_DATA_SENT_ACK_RECEIVED               (0x28)
// Data transmitted, NACK received
#define I2C_MASTER_DATA_SENT_NACK_RECEIVED              (0x30)

// Master receive

// SLA+R transmitted, ACK received
#define I2C_MASTER_SLA_R_SENT_ACK_RECEIVED              (0x40)
// SLA+R transmitted, NACK received  
#define I2C_MASTER_SLA_R_SENT_NACK_RECEIVED             (0x48)

// Data received, ACK returned
#define I2C_MASTER_DATA_RECEIVED_ACK_SENT               (0x50)
// Data received, NACK returned
#define I2C_MASTER_DATA_RECEIVED_NACK_SENT              (0x58)



// master arbitration lost in SLA+W/R or data bytes

// Arbitration lost while transmitting or receiving operation or data
#define I2C_MASTER_ARB_LOST                             (0x38)
// Arbitration lost, own SLA+W received, ACK returned
#define I2C_MASTER_ARB_LOST_SLA_W_RECEIVED_ACK_SENT     (0x68)
// Arbitration lost, own SLA+R received, ACK returned
#define I2C_MASTER_ARB_LOST_SLA_R_RECEIVED_ACK_SENT     (0xB0)
// Arbitration lost, General call received, ACK returned
#define I2C_MASTER_ARB_LOST_GEN_CALL_RECEIVED_ACK_SENT  (0x78)




// SLAVE MODE

// Slave receive
// Own SLA+W received, ACK returned
#define I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT               (0x60)
// General call received, ACK returned 
#define I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT            (0x70)

// Previously addressed, data received, ACK returned
#define I2C_SLAVE_DATA_RECEIVED_ACK_SENT                (0x80)
// Previously addressed, data received, NACK returned
#define I2C_SLAVE_DATA_RECEIVED_NACK_SENT               (0x88)
// Previously addressed from general call, data received, ACK returned
#define I2C_SLAVE_GEN_CALL_DATA_RECEIVED_ACK_SENT       (0x90)
// Previously addressed from general call, data received, NACK returned
#define I2C_SLAVE_GEN_CALL_DATA_RECEIVED_NACK_SENT      (0x98)




// Slave transmit
// Own SLA+R received, ACK returned  
#define I2C_SLAVE_SLA_R_RECEIVED_ACK_SENT               (0xA8)

// Data transmitted, ACK received
#define I2C_SLAVE_DATA_SENT_ACK_RECEIVED                (0xB8)
// Data transmitted, NACK received
#define I2C_SLAVE_DATA_SENT_NACK_RECEIVED               (0xC0)
// Last data byte transmitted, ACK received
#define I2C_SLAVE_LAST_DATA_BYTE_SENT_ACK_RECEIVED      (0xC8)

// STOP or repeated START received while addressed as slave
#define I2C_SLAVE_STOP_RECEIVED                         (0xA0)




// general call
#define I2C_GENERAL_CALL_ACCEPT                         (0x01)
#define I2C_GENERAL_CALL_REJECT                         (0x00)

/* 
* @brief: This function is used to initialize the I2C peripheral as a master and 
*         a slave
*
* @param Copy_u8Address: The address of the MCU with which the I2C peripheral 
*                        will be communicated.
*                        It can be any value from 0x01 to 0x77.
*                        The address 0x00 is reserved for the general call 
*                        address.
*                        The top 8 addresses (0x78 to 0x7F) are reserved.
* @param Copy_u16BitRate:     The bit rate of the I2C peripheral in KHz. It can 
*                             be any value from 1 to 400.
* @param Copy_u8GeneralCall: The general call status. It can be either 
*                            I2C_GENERAL_CALL_ACCEPT or I2C_GENERAL_CALL_REJECT
*
* @return: Error code
*         - ES_OK: If the I2C peripheral is initialized successfully
*         - ES_OUT_OF_RANGE: If any of the input parameters is out of range
*/
ES_t I2C_enuInit_Master_And_Slave(u8 Copy_u8Address, u16 Copy_u16BitRate, 
                                  u8 Copy_u8GeneralCall);


/*
* @brief: This function is used to initialize the I2C peripheral as a master
*
* @param Copy_u16BitRate: The bit rate of the I2C peripheral in KHz. It can be 
* any value from 1 to 400.
*
* @return: Error code
*         - ES_OK: If the I2C peripheral is initialized successfully
*         - ES_OUT_OF_RANGE: If any of the input parameters is out of range
*/
ES_t I2C_enuInit_Master(u16 Copy_u16BitRate);


/*
* @brief: This function is used to initialize the I2C peripheral as a slave
*
* @param Copy_u8Address:    The address of the MCU with which the I2C peripheral 
*                           will be communicated.
*                           It can be any value from 0x01 to 0x77.
*                           The address 0x00 is reserved for the general call 
*                           address.
*                           The top 8 addresses (0x78 to 0x7F) are reserved.
* @param Copy_u8GeneralCall: The general call status. It can be either 
*                            I2C_GENERAL_CALL_ACCEPT or I2C_GENERAL_CALL_REJECT
*
* @return: Error code
*    - ES_OK: If the I2C peripheral is initialized successfully
*    - ES_OUT_OF_RANGE: If any of the input parameters is out of range
*/
ES_t I2C_enuInit_Slave(u8 Copy_u8Address, u8 Copy_u8GeneralCall);


/*
* @brief: This function is used to send a start condition as a master transmit 
*         or receive operation
*
* @param Copy_pu8StatusCode: a variable to hold the status code of the I2C 
* peripheral after sending the start condition. Expected status codes after 
* sending the repeated start condition:
*  - I2C_MASTER_START_SENT
*
* @return: Error code
*   - ES_OK: If the start condition is sent successfully
*   - ES_NULL_POINTER: If the input parameter is NULL
*/
ES_t I2C_enuStartCondition_Master(u8 * Copy_pu8StatusCode);


/*
* @brief: This function is used to send a repeated start condition as a master 
*         transmit or receive operation
*
* @param Copy_pu8StatusCode: a variable to hold the status code of the I2C 
* peripheral after sending the repeated start condition. Expected status codes 
* after sending the repeated start condition:
* - I2C_MASTER_REPEATED_START_SENT
*
* @return: Error code
*   - ES_OK: If the repeated start condition is sent successfully
*   - ES_NULL_POINTER: If the input parameter is NULL
*/
ES_t I2C_enuRepeatedStartCondition_Master(u8 * Copy_pu8StatusCode);


/*
* @brief: This function is used to send a stop condition as a master transmit or 
*         receive operation
* 
* Calling this function immediately after calling 
* I2C_enuStartCondition_Master_Only() or 
* I2C_enuRepeatedStartCondition_Master_Only() is illegal.
*
* This function is called after I2C_enuStartCondition_Master or 
* I2C_enuRepeatedStartCondition_Master, followed by 
* I2C_enuSendSlaveAddressOperation_Master,
* followed by any number of I2C_enuSendDataByte_Master, or 
* I2C_enuReceiveDataByte_Master,
* if the returned status code from any of these functions is one of:
*   - I2C_MASTER_DATA_SENT_ACK_RECEIVED
*   - I2C_MASTER_DATA_SENT_NACK_RECEIVED
*   - I2C_MASTER_DATA_RECEIVED_ACK_SENT
*   - I2C_MASTER_DATA_RECEIVED_NACK_SENT
*
* @return: Error code
*  - ES_OK: If the stop condition is sent successfully
*/
ES_t I2C_enuStopCondition_Master();


/*
* @brief: This function is used to send the slave address and the read/write bit 
*         as a master transmit or receive operation
* This function is called after calling I2C_enuStartCondition_Master or 
* I2C_enuRepeatedStartCondition_Master and before calling 
* I2C_enuStopCondition_Master
* This function is called only once per master transmit or receive operation
* This function is called if and only if:
*   - I2C_enuStartCondition_Master   
*       returns I2C_MASTER_START_SENT
*   - I2C_enuRepeatedStartCondition_Master
*       returns I2C_MASTER_REPEATED_START_SENT
*
*
* @param Copy_u8SlaveAddress: 
* The address of the slave that the master will communicate with.
* It can be any value from 0x01 to 0x77.
* The address 0x00 is reserved for the general call address.
* The top 8 addresses (0x78 to 0x7F) are reserved.
*
* @param Copy_u8ReadWriteBit:
* The read/write bit. It can be either I2C_WRITE or I2C_READ
*
* @param Copy_pu8StatusCode:
* a variable to hold the status code of the I2C peripheral after sending the 
* slave address and the read/write bit. 
* Expected status codes after sending the slave address and the read/write bit:
*  - I2C_MASTER_SLA_R_SENT_ACK_RECEIVED
*  - I2C_MASTER_SLA_R_SENT_NACK_RECEIVED
*  - I2C_MASTER_SLA_W_SENT_ACK_RECEIVED
*  - I2C_MASTER_SLA_W_SENT_NACK_RECEIVED
*  - I2C_MASTER_ARB_LOST
*  - I2C_MASTER_ARB_LOST_SLA_W_RECEIVED_ACK_SENT
*  - I2C_MASTER_ARB_LOST_SLA_R_RECEIVED_ACK_SENT
*  - I2C_MASTER_ARB_LOST_GEN_CALL_RECEIVED_ACK_SENT
*
* @return: Error code
*   - ES_OK: If the slave address and the read/write bit are sent successfully
*/
ES_t I2C_enuSendSLA_R_W_Master(u8 Copy_u8SlaveAddress, u8 Copy_u8ReadWriteBit, 
                               u8 * Copy_pu8StatusCode);


/*
* @brief: This function is used to send a data byte as a master
* 
* Called after calling I2C_enuSendSLA_R_W_Master function 
* and receiving the status code I2C_MASTER_SLA_W_SENT_ACK_RECEIVED or
* I2C_MASTER_SLA_W_SENT_NACK_RECEIVED
*
* @param Copy_u8Data: The data byte to be sent
*
* @param Copy_pu8StatusCode:
* a variable to hold the status code of the I2C peripheral after sending the 
* data byte. Expected status codes after sending the data byte:
*       - I2C_MASTER_DATA_SENT_ACK_RECEIVED
*       - I2C_MASTER_DATA_SENT_NACK_RECEIVED
*       - I2C_MASTER_ARB_LOST
*
* @return: Error code
*  - ES_OK: If the data byte is sent successfully
*/
ES_t I2C_enuSendDataByte_Master(u8 Copy_u8Data, u8 * Copy_pu8StatusCode);


/*
* @brief: This function is used to receive a byte of data as a master
*
* Called after calling I2C_enuSendSLA_R_W_Master function 
* and receiving the status code I2C_MASTER_SLA_R_SENT_ACK_RECEIVED or
* I2C_MASTER_SLA_R_SENT_NACK_RECEIVED
*
* @param Copy_pu8Data: a variable to hold the received data byte
*
* @param Copy_u8AcknowledgeBit: Whether to send an ACK or a NACK after receiving
*
* @param Copy_pu8StatusCode:
* a variable to hold the status code of the I2C peripheral after receiving the 
* data byte. Expected status codes after receiving the data byte:
*     - I2C_MASTER_DATA_RECEIVED_ACK_SENT
*     - I2C_MASTER_DATA_RECEIVED_NACK_SENT
*     - I2C_MASTER_ARB_LOST
*
* @return: Error code
* - ES_OK: If the data byte is received successfully
*/
ES_t I2C_enuReceiveDataByte_Master(u8 * Copy_pu8Data, u8 Copy_u8AcknowledgeBit, u8 * Copy_pu8StatusCode);


/*
* @brief: Check the operation and the status of the I2C peripheral as a slave
* 
* Called after calling 
*  - I2C_enuInit_Slave() function
*  - I2C_enuSendDataByte_Slave function
*  - I2C_enuReceiveDataByte_Slave function
*
* @param Copy_pu8StatusCode:
* a variable to hold the status code of the I2C peripheral after sending the 
* data byte. Expected status codes after sending the data byte:
*      - I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT
*      - I2C_SLAVE_SLA_R_RECEIVED_ACK_SENT
*      - I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT
*
*
* @return: Error code
*  - ES_OK: If the data byte is sent successfully
*/
ES_t I2C_enuResetAndCheckStatus_Slave(u8 * Copy_pu8StatusCode);


/*
* @brief: Check the operation and the status of the I2C peripheral as a slave
* 
* Called after calling 
*  - I2C_enuInit_Slave() function
*  - I2C_enuSendDataByte_Slave function
*  - I2C_enuReceiveDataByte_Slave function
*
* @param Copy_pu8StatusCode:
* a variable to hold the status code of the I2C peripheral after sending the 
* data byte. Expected status codes after sending the data byte:
*      - I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT
*      - I2C_SLAVE_SLA_R_RECEIVED_ACK_SENT
*      - I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT
*
*
* @return: Error code
*  - ES_OK: If the data byte is sent successfully
*/
ES_t I2C_enuCheckStatus_Slave(u8 * Copy_pu8StatusCode);

/*
* @brief: This function is used to receive a byte of data as a slave
*
* Called DIRECTLY(or as soon as possible) after calling I2C_enuCheckSLA_R_W_Slave 
* function and receiving the status code I2C_SLAVE_SLA_R_RECEIVED_ACK_SENT
* 
* @param Copy_u8Data:        The data byte to be sent
*
* @param Copy_u8AcknowledgeBit: Whether to send ACK or NACK
*
* @return: Error code
*  - ES_OK: If the data byte is sent successfully
*/
ES_t I2C_enuSendDataByte_Slave(u8 Copy_u8Data, u8 Copy_u8AcknowledgeBit);

/*
* @brief: This function is used to receive a byte of data as a slave
*
* Called after calling I2C_enuCheckSLA_R_W() function and receiving the
* status code I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT or 
* I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT
*
* @param Copy_pu8Data:       a variable to hold the received data byte
*
* @param Copy_u8AcknowledgeBit: Whether to send ACK or NACK
*
* @return: Error code
* - ES_OK: If the data byte is received successfully
*/
ES_t I2C_enuReceiveDataByte_Slave(u8 * Copy_pu8Data, u8 Copy_u8AcknowledgeBit);




/*
* @brief: This function is used to set the callback function that will be called 
*         when the I2C interrupt occurs
*
* @param Copy_pvCallBack: The callback function
*
* @return: Error code
*   - ES_OK: If the data byte is sent successfully
*   - ES_NULL_POINTER: If the input parameter is NULL
*/
ES_t I2C_enuSetInterruptCallback(void (*Copy_pvCallBack)(void));

/*
* @brief: This function is used to enable the I2C interrupt
*/
void I2C_enuEnableInterrupt(void);

/*
* @brief: This function is used to disable the I2C interrupt
*/
void I2C_enuDisableInterrupt(void);

#endif
