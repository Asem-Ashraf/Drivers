#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/I2C/I2C_INTERFACE.h"

#include "EEPROM_PRIVATE.h"

extern u8 EEPROM_u8ChipsCount;

extern EEPROM_t EEPROM_AstructChips[];


ES_t EEPROM_enuInit(){
    if(!GetBit(TWCR, TWEN)) return ES_I2C_NOT_INITIALIZED;
    for(u8 i = 0; i < EEPROM_u8ChipsCount; i++){
        if(EEPROM_AstructChips[i].EEPROM_u8SlaveAddress >  0b1111000 ||
           EEPROM_AstructChips[i].EEPROM_u8SlaveAddress == 0b0000000)
            return ES_OUT_OF_RANGE;
    }
    return ES_OK;
}


ES_t EEPROM_enuWriteByte(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8Address, u8 Copy_u8Data){
    if(Copy_pstructEEPROMChip == NULL) return ES_NULL_POINTER;

    u8 local_u8statuscode;

    // Send start condition
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Send slave address
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_WRITE_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Send address
    I2C_enuSendDataByte_Master(Copy_u8Address, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    
    // Send data
    I2C_enuSendDataByte_Master(Copy_u8Data, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Acknowledge polling
    I2C_enuStopCondition_Master();
    local_u8statuscode = 0;
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress,I2C_WRITE_OPERATION, &local_u8statuscode);
    while(local_u8statuscode!=I2C_MASTER_SLA_W_SENT_ACK_RECEIVED){
        I2C_enuRepeatedStartCondition_Master(&local_u8statuscode);
        if(local_u8statuscode != I2C_MASTER_REPEATED_START_SENT) {
            I2C_enuStopCondition_Master();
            return ES_EEPROM_I2C_FAILED;
        }
        I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress,I2C_WRITE_OPERATION, &local_u8statuscode);
    }
    I2C_enuStopCondition_Master();

    return ES_OK;
}

ES_t EEPROM_enuWritePage(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8StartAddress, u8 *Copy_Au8Data, u8 Copy_u8Size){
    if(Copy_pstructEEPROMChip == NULL|| Copy_Au8Data == NULL) return ES_NULL_POINTER;
    if(Copy_u8Size > Copy_pstructEEPROMChip->EEPROM_u8PageSize) return ES_OUT_OF_RANGE;

    u8 local_u8statuscode;

    // Send start condition
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Send slave address
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_WRITE_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Send address
    I2C_enuSendDataByte_Master(Copy_u8StartAddress, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }

    // Send data bytes (page size) according to page roll over mechanism see datasheet
    for(u8 i = 0; i < Copy_u8Size; i++){
        I2C_enuSendDataByte_Master(Copy_Au8Data[i], &local_u8statuscode);
        if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
            I2C_enuStopCondition_Master();
            return ES_EEPROM_I2C_FAILED;
        }
    }
    I2C_enuStopCondition_Master();

    return ES_OK;
}


ES_t EEPROM_enuReadImmediateByte(EEPROM_t* Copy_pstructEEPROMChip, u8 *Copy_u8Data){
    if(Copy_pstructEEPROMChip == NULL || Copy_u8Data == NULL) return ES_NULL_POINTER;
    u8 local_u8statuscode;
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_READ_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_R_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuReceiveDataByte_Master(Copy_u8Data, I2C_SEND_NACK, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_RECEIVED_ACK_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuStopCondition_Master();

    return ES_OK;
}

ES_t EEPROM_enuReadByte(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8Address, u8 *Copy_u8Data){
    if(Copy_pstructEEPROMChip == NULL || Copy_u8Data == NULL) return ES_NULL_POINTER;
    u8 local_u8statuscode;
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_WRITE_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendDataByte_Master(Copy_u8Address, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuRepeatedStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_REPEATED_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_READ_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_R_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuReceiveDataByte_Master(Copy_u8Data,I2C_SEND_NACK, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_RECEIVED_NACK_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuStopCondition_Master();

    return ES_OK;
}

ES_t EEPROM_enuReadPage(EEPROM_t* Copy_pstructEEPROMChip, u8 Copy_u8StartAddress, u8 *Copy_Au8Data, u8 Copy_u8Size){
    if(Copy_pstructEEPROMChip == NULL || Copy_Au8Data == NULL) return ES_NULL_POINTER;
    u8 local_u8statuscode;
    I2C_enuStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_WRITE_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_W_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendDataByte_Master(Copy_u8StartAddress, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_DATA_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuRepeatedStartCondition_Master(&local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_REPEATED_START_SENT) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    I2C_enuSendSLA_R_W_Master(Copy_pstructEEPROMChip->EEPROM_u8SlaveAddress, I2C_READ_OPERATION, &local_u8statuscode);
    if(local_u8statuscode != I2C_MASTER_SLA_R_SENT_ACK_RECEIVED) {
        I2C_enuStopCondition_Master();
        return ES_EEPROM_I2C_FAILED;
    }
    for(u8 i = 0; i < Copy_u8Size; i++){
        if(i == Copy_u8Size - 1){
            I2C_enuReceiveDataByte_Master(&Copy_Au8Data[i], I2C_SEND_NACK, &local_u8statuscode);
            if(local_u8statuscode != I2C_MASTER_DATA_RECEIVED_NACK_SENT) {
                I2C_enuStopCondition_Master();
                return ES_EEPROM_I2C_FAILED;
            }
        }
        else{
            I2C_enuReceiveDataByte_Master(&Copy_Au8Data[i], I2C_SEND_ACK, &local_u8statuscode);
            if(local_u8statuscode != I2C_MASTER_DATA_RECEIVED_ACK_SENT) {
                I2C_enuStopCondition_Master();
                return ES_EEPROM_I2C_FAILED;
            }
        }
    }
    I2C_enuStopCondition_Master();

    return ES_OK;
}
