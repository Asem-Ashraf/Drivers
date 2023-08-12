#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#include "LED_PRIVATE.h"

extern u8 LED_u8NUM_OF_LEDS;
extern LED_t LED_AstructLed[];

/*  ============================ *\
   || FUNCTIONS' IMPLEMENTATION||
\*  ============================ */

ES_t LED_enuInit(){
    ES_t local_enuErrorState = ES_NULL_POINTER;

    for(u8 local_u8LedCounter = 0; local_u8LedCounter < LED_u8NUM_OF_LEDS; local_u8LedCounter++){
        if (LED_AstructLed[local_u8LedCounter].LED_u8InitState> LED_u8ON|| LED_AstructLed[local_u8LedCounter].LED_u8Connection> LED_u8SINK) return ES_OUT_OF_RANGE;

        local_enuErrorState = DIO_enuSetPinDirection(LED_AstructLed[local_u8LedCounter].LED_u8PORTID, LED_AstructLed[local_u8LedCounter].LED_u8PINID, DIO_u8OUTPUT);
        if (local_enuErrorState != ES_OK) return local_enuErrorState;

        local_enuErrorState = DIO_enuSetPinValue    (LED_AstructLed[local_u8LedCounter].LED_u8PORTID, LED_AstructLed[local_u8LedCounter].LED_u8PINID, (LED_AstructLed[local_u8LedCounter].LED_u8InitState!=LED_AstructLed[local_u8LedCounter].LED_u8Connection));
        if (local_enuErrorState != ES_OK) return local_enuErrorState;
    }
    return local_enuErrorState;
}

ES_t LED_enuTurnOn(LED_t* Copy_pstructLed){
    ES_t local_enuErrorState = ES_NOK;

    // Error Checking
        if (Copy_pstructLed == NULL) 
            return ES_NULL_POINTER;
        if (Copy_pstructLed< LED_AstructLed ||
            Copy_pstructLed> LED_AstructLed+sizeof(LED_t)*(LED_u8NUM_OF_LEDS-1)||
            Copy_pstructLed->LED_u8Connection> LED_u8SINK) 
            return ES_OUT_OF_RANGE;

    local_enuErrorState = DIO_enuSetPinValue(Copy_pstructLed->LED_u8PORTID,
                                             Copy_pstructLed->LED_u8PINID,
                                             (DIO_u8HIGH!=Copy_pstructLed->LED_u8Connection));
    return local_enuErrorState;
}

ES_t LED_enuTurnOff(LED_t* Copy_pstructLed){
    ES_t local_enuErrorState = ES_NULL_POINTER;

    // Error Checking
        if (Copy_pstructLed == NULL) 
            return ES_NULL_POINTER;
        if (Copy_pstructLed< LED_AstructLed ||
            Copy_pstructLed> LED_AstructLed+sizeof(LED_t)*(LED_u8NUM_OF_LEDS-1)||
            Copy_pstructLed->LED_u8Connection> LED_u8SINK) 
            return ES_OUT_OF_RANGE;

    local_enuErrorState = DIO_enuSetPinValue(Copy_pstructLed->LED_u8PORTID,
                                             Copy_pstructLed->LED_u8PINID,
                                             (DIO_u8LOW!=Copy_pstructLed->LED_u8Connection));
    return local_enuErrorState;
}

ES_t LED_enuToggle(LED_t* Copy_pstructLed){
    ES_t local_enuErrorState = ES_NULL_POINTER;

    // Error Checking
        if (Copy_pstructLed == NULL)
            return ES_NULL_POINTER;
        if (Copy_pstructLed< LED_AstructLed ||
            Copy_pstructLed> LED_AstructLed+sizeof(LED_t)*(LED_u8NUM_OF_LEDS-1)||
            Copy_pstructLed->LED_u8Connection> LED_u8SINK) 
            return ES_OUT_OF_RANGE;

    local_enuErrorState = DIO_enuTogglePinValue(Copy_pstructLed->LED_u8PORTID,
                                                Copy_pstructLed->LED_u8PINID);
    return local_enuErrorState;
}
