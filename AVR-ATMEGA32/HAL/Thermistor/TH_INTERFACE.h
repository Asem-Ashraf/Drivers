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


/**
 * @brief Initialize all thermistors defined in TH_AstuThemistors array.
 * 
 * @param[in] Copy_AstructThemistors Pointer to an array of TH_t structures containing the thermistor configurations.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Initialization successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer passed as argument.
 */
ES_t TH_enuInit(TH_t* Copy_AstructThemistors);

/**
 * @brief Get the temperature reading from a thermistor.
 * 
 * @param[in] Copy_pstructThemistor Pointer to a TH_t structure containing the thermistor configuration.
 * @param[out] pf32temp Pointer to a variable that will hold the temperature reading in degrees Celsius.
 * 
 * @return ES_t Error status.
 *         - ES_OK: Get temperature operation successful.
 *         - ES_NULL_POINTER: Null pointer passed as argument.
 *         - ES_OUT_OF_RANGE: Invalid pointer passed as argument.
 */
ES_t TH_enuGetTemp(TH_t* Copy_pstructThemistor, f32 *pf32temp);

#endif // SW_INIT_H
