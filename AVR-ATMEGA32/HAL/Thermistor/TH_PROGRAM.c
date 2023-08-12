// INCLUDES
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "../../MCAL/ADC/ADC_INTERFACE.h"

#define TH_u8Positive 1
#define TH_u8Negative 0

typedef struct{
    u8 TH_u8Type;   // TH_u8Positive, TH_u8Negative
    u8 TH_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3,
                    // DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}TH_t;

extern u8 TH_u8NUM;
extern TH_t TH_AstuThemistors[];

// FUNCTIONS IMPLEMENTATION
ES_t TH_enuInit(TH_t* Copy_AstructThemistors){
    ES_t Local_enuErrorState = ES_NOK;

    // Error Checking
    if (Copy_AstructThemistors == NULL)
        return ES_NULL_POINTER;
    if (Copy_AstructThemistors!=TH_AstuThemistors)
        return ES_OUT_OF_RANGE;
    for (u8 i = 0; i<TH_u8NUM; i++) {
        Local_enuErrorState = 
            DIO_enuSetPinDirection(DIO_u8PORTA,
                                   Copy_AstructThemistors[i].TH_u8PINID,
                                   DIO_u8INPUT);
        if (Local_enuErrorState != ES_OK) { return Local_enuErrorState; }
    }
    return Local_enuErrorState;
}


ES_t TH_enuGetTemp(TH_t* Copy_pstructThemistor, f32 *pf32temp){
    ES_t Local_enuErrorState = ES_NOK;

    // Error Checking
    if (Copy_pstructThemistor == NULL) 
        return ES_NULL_POINTER;
    if (Copy_pstructThemistor<TH_AstuThemistors ||
        Copy_pstructThemistor>TH_AstuThemistors+sizeof(TH_t)*(TH_u8NUM-1))
        return ES_OUT_OF_RANGE;

    Local_enuErrorState = ADC_enuSetChannel(Copy_pstructThemistor->TH_u8PINID);
    if (Local_enuErrorState != ES_OK) { return Local_enuErrorState; }
    ADC_voidStartOneConversion();
    u16 local_u16reading = ADC_u16GetValuePolling();
    if (Copy_pstructThemistor->TH_u8Type == TH_u8Positive)
        local_u16reading = 1023 - local_u16reading;
    *pf32temp = (f64)local_u16reading * 0.488;
    return Local_enuErrorState;
}
