#ifndef LED_INT_H_
#define LED_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "LED_config.h"

/*  ======================= *\
   || FUNCTIONS PROTOTYPE ||
\*  ======================= */


// LED_AstructLed  : pointer to the LED struct
ES_t LED_enuInit      (LED_t* LED_AstructLed);


// LED_AstructLed  : pointer to the LED struct
ES_t LED_enuTurnOn    (LED_t* LED_pstructLed);


// LED_AstructLed  : pointer to the LED struct
ES_t LED_enuTurnOff   (LED_t* LED_pstructLed);


// LED_AstructLed  : pointer to the LED struct
ES_t LED_enuToggle    (LED_t* LED_pstructLed);


#endif