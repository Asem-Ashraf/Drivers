#ifndef EEPROM_CONFING_H
#define EEPROM_CONFING_H

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

typedef struct {
    u8 EEPROM_u8SlaveAddress;
    u8 EEPROM_u8PageSize;
    u8 EEPROM_u8PageCount;
}EEPROM_t;

#endif
