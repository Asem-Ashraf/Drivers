#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "LED_priv.h"
#include "LED_config.h"

ES_t LED_enuInit(LED_t* LED_AstructLed){
    ES_t local_enuErrorState = ES_NOK;
    for(u8 local_u8LedCounter = 0; local_u8LedCounter < LED_u8NUM_OF_LEDS; local_u8LedCounter++){
        local_enuErrorState = DIO_enuSetPinDirection(LED_AstructLed[local_u8LedCounter].LED_u8PORTID,
                                                     LED_AstructLed[local_u8LedCounter].LED_u8PINID,
                                                     DIO_u8OUTPUT);
        if (local_enuErrorState != ES_OK) { return local_enuErrorState; }
        local_enuErrorState = DIO_enuSetPinValue    (LED_AstructLed[local_u8LedCounter].LED_u8PORTID,
                                                     LED_AstructLed[local_u8LedCounter].LED_u8PINID,
                                                     LED_AstructLed[local_u8LedCounter].LED_u8InitState!=LED_AstructLed[local_u8LedCounter].LED_u8Connection);
        if (local_enuErrorState != ES_OK) { return local_enuErrorState; }
    }
    return local_enuErrorState;
}

ES_t LED_enuTurnOn(LED_t* LED_pstructLed){
    ES_t local_enuErrorState = ES_NOK;
    local_enuErrorState = DIO_enuSetPinValue(LED_pstructLed->LED_u8PORTID,
                                             LED_pstructLed->LED_u8PINID,
                                             DIO_u8HIGH!=LED_pstructLed->LED_u8Connection);
    return local_enuErrorState;
}

ES_t LED_enuTurnOff(LED_t* LED_pstructLed){
    ES_t local_enuErrorState = ES_NOK;
    local_enuErrorState = DIO_enuSetPinValue(LED_pstructLed->LED_u8PORTID,
                                             LED_pstructLed->LED_u8PINID,
                                             DIO_u8LOW!=LED_pstructLed->LED_u8Connection);
    return local_enuErrorState;
}

ES_t LED_enuToggle(LED_t* LED_pstructLed){
    ES_t local_enuErrorState = ES_NOK;
    local_enuErrorState = DIO_enuTogglePinValue(LED_pstructLed->LED_u8PORTID,
                                                LED_pstructLed->LED_u8PINID);
    return local_enuErrorState;
}
