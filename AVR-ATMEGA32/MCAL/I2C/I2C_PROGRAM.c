#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/CPU_FREQ.h"


#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

#include "I2C_PRIVATE.h"

void (*I2C_pvCallBack)(void) = NULL;

void __vector_19(void) __attribute__((signal, used));
void __vector_19(void){
    if(I2C_pvCallBack != NULL){
        I2C_pvCallBack();
    }
}

ES_t I2C_enuInit_Master_And_Slave(u8 Copy_u8Address, u16 Copy_u16BitRate, u8 Copy_u8GeneralCall){
    if(Copy_u8Address > 0x77|| Copy_u8Address == 0x00|| // checking the address according to the data sheet bounds
       0xff < GETTWBR(Copy_u16BitRate)||                 // checking the bit rate according to the data sheet bounds
       Copy_u8GeneralCall > I2C_GENERAL_CALL_REJECT)    // checking the general call bound
        return ES_OUT_OF_RANGE;
    

    // Set the address of the MCU and the general call bit
    // to be addressed as a slave
    TWAR = Copy_u8Address<<1|Copy_u8GeneralCall;

    // Set the bit rate or master clock
    TWBR = GETTWBR(Copy_u16BitRate);

    TWCR = (1<<TWEN);

    return ES_OK;
}

ES_t I2C_enuInit_Master(u16 Copy_u16BitRate){
    if(0xff < GETTWBR(Copy_u16BitRate)) // checking the bit rate according to the data sheet bounds
        return ES_OUT_OF_RANGE;


    // Disable the I2C as slave
    TWAR = 0;
    // Set the bit rate or master clock
    TWBR = GETTWBR(Copy_u16BitRate);

    TWCR = (1<<TWEN)|(1<<TWINT);
    return ES_OK;
}

ES_t I2C_enuInit_Slave(u8 Copy_u8Address, u8 Copy_u8GeneralCall){
    if(Copy_u8Address > 0x77|| Copy_u8Address == 0x00|| // checking the address according to the data sheet bounds
       Copy_u8GeneralCall > I2C_GENERAL_CALL_REJECT)    // checking the general call bound
        return ES_OUT_OF_RANGE;
    
    // Set the address of the MCU and the general call bit
    // to be addressed as a slave
    TWAR = Copy_u8Address<<1|Copy_u8GeneralCall;

    // Enable the I2C and clear the flag
    TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT);

    return ES_OK;
}

ES_t I2C_enuStartCondition_Master(u8 * Copy_pu8StatusCode){
    if(Copy_pu8StatusCode == NULL) 
        return ES_NULL_POINTER;
    
    // Send the start condition, enable the I2C and clear the flag
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    return ES_OK;
}

ES_t I2C_enuRepeatedStartCondition_Master(u8 * Copy_pu8StatusCode){
    return I2C_enuStartCondition_Master(Copy_pu8StatusCode);
}

void I2C_enuStopCondition_Master(){
    // Send the stop condition, enable the I2C and clear the flag
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

ES_t I2C_enuSendSLA_R_W_Master(u8 Copy_u8SlaveAddress, u8 Copy_u8ReadWriteBit, u8 * Copy_pu8StatusCode){
    if(Copy_u8SlaveAddress > 0x77 ||   // checking the address according to the data sheet bounds allowing general call
       Copy_u8ReadWriteBit > I2C_READ) // checking the read write bit bound
        return ES_OUT_OF_RANGE;
    
    if(Copy_pu8StatusCode == NULL) return ES_NULL_POINTER;
    
    // Send the slave address and the read/write bit, enable the I2C and clear the flag
    TWDR = Copy_u8SlaveAddress<<1|Copy_u8ReadWriteBit;
    TWCR = (1<<TWINT)|(1<<TWEN);
    
    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    return ES_OK;
}

ES_t I2C_enuSendDataByte_Master(u8 Copy_u8Data, u8 * Copy_pu8StatusCode){
    if(Copy_pu8StatusCode == NULL)
        return ES_NULL_POINTER;
    
    // Send the data byte, enable the I2C and clear the flag
    TWDR = Copy_u8Data;
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    return ES_OK;
}
ES_t I2C_enuReceiveDataByte_Master(u8 * Copy_pu8Data, u8 Copy_u8AcknowledgeBit, u8 * Copy_pu8StatusCode){
    if(Copy_pu8Data == NULL || Copy_pu8StatusCode == NULL) 
        return ES_NULL_POINTER;
    
    // Enable the I2C and clear the flag
    TWCR = (1<<TWINT)|(1<<TWEN)|(Copy_u8AcknowledgeBit<<TWEA);

    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    if(*Copy_pu8StatusCode == I2C_SLAVE_STOP_RECEIVED)
        return ES_OK;

    // Get the data byte and the status code
    *Copy_pu8Data = TWDR;

    return ES_OK;
}

ES_t I2C_enuResetAndCheckStatus_Slave(u8 * Copy_pu8StatusCode){
    if(Copy_pu8StatusCode == NULL)
        return ES_NULL_POINTER;

    TWCR = (1<<TWINT)|(1<<TWEN);
    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    return ES_OK;
}
ES_t I2C_enuCheckStatus_Slave(u8 * Copy_pu8StatusCode){
    if(Copy_pu8StatusCode == NULL)
        return ES_NULL_POINTER;

    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the status code
    *Copy_pu8StatusCode = TWSR & 0xF8;

    return ES_OK;
}

ES_t I2C_enuSendDataByte_Slave(u8 Copy_u8Data, u8 Copy_u8AcknowledgeBit){
    if(Copy_u8AcknowledgeBit > I2C_ACK_ENABLE) 
        return ES_OUT_OF_RANGE;

    // Send the data byte, enable the I2C and clear the flag
    TWDR = Copy_u8Data;

    // clear the flag
    TWCR = (1<<TWEN)|(1<<TWINT)|(Copy_u8AcknowledgeBit<<TWEA);

    return ES_OK;
}
ES_t I2C_enuReceiveDataByte_Slave(u8 * Copy_pu8Data, u8 Copy_u8AcknowledgeBit){
    if(Copy_pu8Data == NULL) 
        return ES_NULL_POINTER;

    if(Copy_u8AcknowledgeBit > I2C_ACK_ENABLE) 
        return ES_OUT_OF_RANGE;

    // clear the flag
    TWCR = (1<<TWINT)|(Copy_u8AcknowledgeBit<<TWEA)|(1<<TWEN);

    // Wait for the flag to be set and operation to be done
    while(GetBit(TWCR, TWINT) == 0);

    // Get the data byte and the status code
    *Copy_pu8Data = TWDR;

    return ES_OK;
}



ES_t I2C_enuSetInterruptCallback(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack == NULL)
        return ES_NULL_POINTER;
    
    // Set the call back function
    I2C_pvCallBack = Copy_pvCallBack;

    return ES_OK;
}

void I2C_enuEnableInterrupt(void){
    // Enable the I2C interrupt
    SetBit(TWCR, TWIE);
}

void I2C_enuDisableInterrupt(void){
    // Disable the I2C interrupt
    ClrBit(TWCR, TWIE);
}

