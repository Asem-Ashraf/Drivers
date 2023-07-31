#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"


#include "EEPROM_CONFING.h"

#define EEPROM_u8CHIP_NUM 1

u8 EEPROM_u8ChipsCount= EEPROM_u8CHIP_NUM;
const EEPROM_t EEPROM_AstructChips[EEPROM_u8CHIP_NUM] = {
    {
        .EEPROM_u8SlaveAddress= 0b1010000,
        .EEPROM_u8PageSize = 8,
        .EEPROM_u8PageCount = 32
    }
};
