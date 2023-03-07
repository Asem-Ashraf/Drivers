// INCLUDES
#include "stdTypes.h"
#include "ErrorStates.h"
#include "SW_priv.h"
#include "SW_config.h"
#include "DIO_int.h"


// FUNCTIONS IMPLEMENTATION
ES_t SW_enuInit(SW_t* Copy_AstructSwitchs){
    ES_t Local_enuErrorState = ES_NOK;
    for (u8 i=0; i<SW_u8NUM; i++) {
        Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstructSwitchs[i].SW_u8PORTID,
                                                     Copy_AstructSwitchs[i].SW_u8PINID,
                                                     DIO_u8INPUT);
        if (Local_enuErrorState != ES_OK) { return Local_enuErrorState; }

        Local_enuErrorState = DIO_enuSetPinValue    (Copy_AstructSwitchs[i].SW_u8PORTID,
                                                     Copy_AstructSwitchs[i].SW_u8PINID,
                                                     Copy_AstructSwitchs[i].SW_u8Mode);
        if (Local_enuErrorState != ES_OK) { return Local_enuErrorState; }
    }
    return Local_enuErrorState;
}

ES_t SW_enuGetState(SW_t* Copy_pstructSwitch, u8 *pu8State){
    ES_t Local_enuErrorState = ES_NOK;
    Local_enuErrorState = DIO_enuGetPinValue(Copy_pstructSwitch->SW_u8PORTID,
                                             Copy_pstructSwitch->SW_u8PINID,
                                             pu8State);
    return Local_enuErrorState;
}
ES_t SW_enuSetMode(SW_t* Copy_pstructSwitch, u8 Copy_u8Mode){
    ES_t Local_enuErrorState = ES_NOK;
    Local_enuErrorState = DIO_enuSetPinValue(Copy_pstructSwitch->SW_u8PORTID,
                                             Copy_pstructSwitch->SW_u8PINID,
                                             Copy_u8Mode);
    return Local_enuErrorState;
}
