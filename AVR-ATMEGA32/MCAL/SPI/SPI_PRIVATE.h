#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#include "../../LIB/STD_TYPE.h"

#define SPI_DISABLE         0b00000000
#define SPI_ENABLE          0b01000000

#define SPI_SLAVE           0b00000000
#define SPI_MASTER          0b00010000

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

#define SPI_MASTER_INPUT_ONLY   0
#define SPI_MASTER_INPUT_OUTPUT 1

#define SPI_SLAVE_INPUT_ONLY    0
#define SPI_SLAVE_INPUT_OUTPUT  1





#define SPCR (*(volatile u8*)0x2D)
#define SPIE 7
#define SPE  6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define DDRB (*(volatile u8*)0x37)
#define MISO 6
#define MOSI 5
#define SS   4
#define SCK  7

#define SPSR (*(volatile u8*)0x2E)
#define SPIF 7
#define WCOL 6
#define SPI2X 0

#define SPDR (*(volatile u8*)0x2F)


#endif
