// INCLUDES
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

typedef struct{
    u8 SW_u8Mode;   // DIO_u8pull_up or DIO_u8FLOAT
    u8 SW_u8PORTID; // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 SW_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}SW_t;

extern u8 SW_u8NUM;
extern SW_t SW_AstuSwitches[];

// FUNCTIONS IMPLEMENTATION
ES_t SW_enuInit(SW_t* Copy_AstructSwitchs){
    ES_t Local_enuErrorState = ES_NOK;

    // Error Checking
    if (Copy_AstructSwitchs == NULL)
        return ES_NULL_POINTER;
    if (Copy_AstructSwitchs!=SW_AstuSwitches)
        return ES_OUT_OF_RANGE;
    for (u8 i = 0; i<SW_u8NUM; i++) {
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

    // Error Checking
    if (Copy_pstructSwitch == NULL) 
        return ES_NULL_POINTER;
    if (Copy_pstructSwitch<SW_AstuSwitches ||
        Copy_pstructSwitch>SW_AstuSwitches+sizeof(SW_t)*(SW_u8NUM-1))
        return ES_OUT_OF_RANGE;
    Local_enuErrorState = DIO_enuGetPinValue(Copy_pstructSwitch->SW_u8PORTID,
                                             Copy_pstructSwitch->SW_u8PINID,
                                             pu8State);
    return Local_enuErrorState;
}


ES_t SW_enuSetMode(SW_t* Copy_pstructSwitch, u8 Copy_u8Mode){
    ES_t Local_enuErrorState = ES_NULL_POINTER;

    // Error Checking
    if (Copy_pstructSwitch == NULL)
        return Local_enuErrorState;
    if (Copy_pstructSwitch<SW_AstuSwitches ||
        Copy_pstructSwitch>SW_AstuSwitches+sizeof(SW_t)*(SW_u8NUM-1))
        return ES_OUT_OF_RANGE;
    Local_enuErrorState = DIO_enuSetPinValue(Copy_pstructSwitch->SW_u8PORTID,
                                             Copy_pstructSwitch->SW_u8PINID,
                                             Copy_u8Mode);
    return Local_enuErrorState;
}
