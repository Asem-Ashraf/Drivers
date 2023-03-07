#include "SW_config.h"
#include "../../MCAL/DIO/DIO_int.h"

SW_t SW_AstuSwitches[SW_u8NUM]={
    {DIO_u8PULL_UP, DIO_u8PORTA, DIO_u8PIN0},
    {DIO_u8FLOAT,   DIO_u8PORTA, DIO_u8PIN1},
};
