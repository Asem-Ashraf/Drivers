#include "SW_config.h"
#include "../../MCAL/DIO/DIO_int.h"

// Define the number of switches in the system [1-255],
u8 SW_u8NUM =2; // This number has to reflect the number of switches in the array below
SW_t SW_AstuSwitches[]={
    {DIO_u8PULL_UP, DIO_u8PORTA, DIO_u8PIN0},
    {DIO_u8FLOAT,   DIO_u8PORTA, DIO_u8PIN1},
};
