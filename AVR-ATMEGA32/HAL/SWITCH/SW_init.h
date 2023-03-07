#ifndef SW_INIT_H
#define SW_INIT_H

// INCLUDES
#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "SW_config.h"

// FUNCTIONS PROTOTYPES


// Copy_pstructSwitches : pointer to the switches struct
ES_t SW_enuInit(SW_t *SW_AstructSwitches);


// Copy_pstructSwitch : pointer to the switch struct
// Copy_pu8State      : pointer to u8 variable to store the value of the switch
ES_t SW_enuGetState(SW_t* Copy_pstructSwitch, u8 *pu8State);


// Copy_pstructSwitch : pointer to the switch struct
// Copy_u8Mode        : DIO_u8FLOAT, DIO_u8PULL_UP
ES_t SW_enuSetMode(SW_t* Copy_pstructSwitch, u8 Copy_u8Mode);


#endif // SW_INIT_H
