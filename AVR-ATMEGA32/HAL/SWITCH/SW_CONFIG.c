#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

typedef struct{
    u8 SW_u8Mode;   // DIO_u8pull_up or DIO_u8FLOAT
    u8 SW_u8PORTID; // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 SW_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}SW_t;

// Define the number of switches in the system [1-255].
// This number has to reflect the number of switches in the SW_AstuSwitches array.
#define SW_u8NUMSWITCHES 1

u8 SW_u8NUM = SW_u8NUMSWITCHES;
SW_t SW_AstuSwitches[SW_u8NUMSWITCHES]={
    {DIO_u8FLOAT, DIO_u8PORTA, DIO_u8PIN0}
};
