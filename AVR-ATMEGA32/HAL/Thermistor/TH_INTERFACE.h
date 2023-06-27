#ifndef SW_INIT_H
#define SW_INIT_H
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

typedef struct{
    u8 TH_u8Type;   // TH_u8Positive, TH_u8Negative
    u8 TH_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3,
                    // DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}TH_t;


// Copy_pstructThemistor: pointer to the thermistor structure.
ES_t TH_enuInit   (TH_t *TH_AstructThemistors);


// Copy_pstructThemistor: pointer to the thermistor structure.
// pf32temp             : pointer to f32 variable to store the temperature in.
ES_t TH_enuGetTemp(TH_t* Copy_pstructThemistor, f32 *pf32temp);

#endif // SW_INIT_H
