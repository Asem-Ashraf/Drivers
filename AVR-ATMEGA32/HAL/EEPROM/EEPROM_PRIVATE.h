#ifndef EEPROM_PRIVATE_H
#define EEPROM_PRIVATE_H

typedef struct {
    u8 EEPROM_u8SlaveAddress;
    u8 EEPROM_u8PageSize;
    u8 EEPROM_u8PageCount;
}EEPROM_t;

#define TWCR	*((volatile u8 *) 0x56)
#define TWEN	2

#endif
