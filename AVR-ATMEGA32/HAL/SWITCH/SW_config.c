#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "SW_config.h"

// Define the number of switches in the system [1-255].
// This number has to reflect the number of switches in the SW_AstuSwitches array.
#define SW_u8NUMSWITCHES 1

u8 SW_u8NUM = SW_u8NUMSWITCHES;
SW_t SW_AstuSwitches[SW_u8NUMSWITCHES]={
    {DIO_u8FLOAT, DIO_u8PORTA, DIO_u8PIN0}
};
