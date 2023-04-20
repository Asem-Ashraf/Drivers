#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"

#include "ADC_ARG.h"


// ADC_u8Prescaler  : ADC_u8PRESCALER_2, ADC_u8PRESCALER_4, 
//                    ADC_u8PRESCALER_8, ADC_u8PRESCALER_16,
//                    ADC_u8PRESCALER_32, ADC_u8PRESCALER_64, 
//                    ADC_u8PRESCALER_128
// ADC_u8Adjustment : ADC_u8RIGHT_ADJ, ADC_u8LEFT_ADJ
// ADC_u8RefVoltage : ADC_u8AREF, ADC_u8AVCC, ADC_u8INTERNAL
ES_t ADC_enuInit(u8 ADC_u8Prescaler,u8 ADC_u8Adjustment,u8 ADC_u8RefVoltage);


// ADC_u8Trigger    : ADC_u8FREE_RUNNING, ADC_u8ANALOG_CMP,
//                    ADC_u8EXT_INT, ADC_u8TMR0_CMp_MATCH,
//                    ADC_u8TMR0_OVF, ADC_u8TMR1_CMP_MATCH_B,
//                    ADC_u8TMR1_OVF, ADC_u8TMR1_CAPTURE_EVENT,
ES_t ADC_enuSetTrigger(u8 ADC_u8Trigger);


// ADC_u8Channel : ADC_u8CH0, ADC_u8CH1, ADC_u8CH2, ADC_u8CH3,
//                 ADC_u8CH4, ADC_u8CH5, ADC_u8CH6, ADC_u8CH7
ES_t ADC_enuSetChannel(u8 ADC_u8Channel);


ES_t ADC_enuStartOneConversion(void);


// ADC_u16Data   : Pointer to variable to store the result
ES_t ADC_enuGetValuePolling(u16 *ADC_u16Data);


// Copy_ptr : Pointer to function to be called by the ISR when conversion is done
ES_t ADC_enuSetCallBack(void (*Copy_ptr)(void));


ES_t ADC_enuEnableInterrupt(void);


// Stops the current ongoing conversion by disabling the ADC
// The ADC must be reinitialized to start a new conversions
ES_t ADC_enuHultADC(void);

#endif /* ADC_INTERFACE_H_ */
