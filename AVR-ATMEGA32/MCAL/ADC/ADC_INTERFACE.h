#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"

#include "ADC_ARG.h"


// Initializes the ADC with the given configuration.
// The ADC must be initialized before starting a conversion.
// The ADC must be initialized before setting the trigger.
// ADC_u8Prescaler  : ADC_u8PRESCALER_2, ADC_u8PRESCALER_4, 
//                    ADC_u8PRESCALER_8, ADC_u8PRESCALER_16,
//                    ADC_u8PRESCALER_32, ADC_u8PRESCALER_64, 
//                    ADC_u8PRESCALER_128
// ADC_u8Adjustment : ADC_u8RIGHT_ADJ, ADC_u8LEFT_ADJ
// ADC_u8RefVoltage : ADC_u8AREF, ADC_u8AVCC, ADC_u8INTERNAL
ES_t ADC_enuInit(u8 ADC_u8Prescaler,u8 ADC_u8Adjustment,u8 ADC_u8RefVoltage);


// Sets the trigger source for the ADC and enables the auto trigger 
// Functionalities.
// The ADC must be initialized before setting the trigger.
// A channel must be selected before setting the trigger.
// ADC_u8Trigger    : ADC_u8FREE_RUNNING, ADC_u8ANALOG_CMP,
//                    ADC_u8EXT_INT, ADC_u8TMR0_CMp_MATCH,
//                    ADC_u8TMR0_OVF, ADC_u8TMR1_CMP_MATCH_B,
//                    ADC_u8TMR1_OVF, ADC_u8TMR1_CAPTURE_EVENT,
ES_t ADC_enuSetTrigger(u8 ADC_u8Trigger);


// Disable the auto trigger functionality.
// This function sets the ADC to single conversion mode.
ES_t ADC_enuDisableTrigger(void);


// Selects the configuration of the ADC according to the datasheet.
// Changing the channel during a conversion will not affect the current conversion.
// ADC_u8Channel : Any number from 0x00 to 0x1F
//                 0x00 to 0x07 for single ended input
//                 0x08 to 0x0F for differential input
//                 0x10 to 0x1F for internal channels
ES_t ADC_enuSetChannel(u8 ADC_u8Channel);


// Manually starts a single conversion and returns immediately.
// The ADC must be initialized before starting a conversion.
// A channel must be selected before starting a conversion.
ES_t ADC_enuStartOneConversion(void);


// Waits for the current conversion to finish and returns the result.
// If there is not a conversion in progress, it returns the last result.
// This fucntion does not depend whether the ADC is in auto trigger mode or not.
// This fucntion can be used even if the ADC's interrupt is enabled.
// ADC_u16Data   : Pointer to variable to store the result
ES_t ADC_enuGetValuePolling(u16 *ADC_u16Data);


// Copy_ptr : Pointer to function to be called by the ISR when conversion is done.
ES_t ADC_enuSetCallBack(void (*Copy_ptr)(void));


// Enables the ADC interrupt
ES_t ADC_enuEnableInterrupt(void);


// Disables the ADC interrupt
ES_t ADC_enuDisableInterrupt(void);


// Stops the current ongoing conversion by disabling the ADC
// The ADC must be reinitialized to start a new conversions
ES_t ADC_enuHultADC(void);

#endif /* ADC_INTERFACE_H_ */
