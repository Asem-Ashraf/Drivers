#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
/**
 * @file ADC_interface.h
 * @brief This is a header file that contains the interface for the ADC driver.
 *
 * This file contains the interface for the ADC driver. It provides functions 
 * to initialize the ADC, set the prescaler, adjustment, reference voltage, 
 * trigger, and channel, start one conversion and get the ADC value. It also 
 * provides functions to enable/disable the ADC interrupt, set the callback 
 * function, and halt the ADC.
 *
 * @author Asem Ashraf
 */


#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

#define ADC_u8CH0           0x00
#define ADC_u8CH1           0x01
#define ADC_u8CH2           0x02
#define ADC_u8CH3           0x03
#define ADC_u8CH4           0x04
#define ADC_u8CH5           0x05
#define ADC_u8CH6           0x06
#define ADC_u8CH7           0x07

#define ADC_u8AREF          0b00000000
#define ADC_u8AVCC          0b01000000
#define ADC_u8INTERNAL      0b11000000

#define ADC_u8RIGHT_ADJ     0b00000000
#define ADC_u8LEFT_ADJ      0b00100000

#define ADC_u8PRESCALER_2           0b00000001
#define ADC_u8PRESCALER_4           0b00000010
#define ADC_u8PRESCALER_8           0b00000011
#define ADC_u8PRESCALER_16          0b00000100
#define ADC_u8PRESCALER_32          0b00000101
#define ADC_u8PRESCALER_64          0b00000110
#define ADC_u8PRESCALER_128         0b00000111

#define ADC_u8INTERRUPT             0x01
#define ADC_u8POLLING               0x00

#define ADC_u8FREE_RUNNING          0b00000000
#define ADC_u8ANALOG_CMP            0b00100000
#define ADC_u8EXT_INT               0b01000000
#define ADC_u8TMR0_CMp_MATCH        0b01100000
#define ADC_u8TMR0_OVF              0b10000000
#define ADC_u8TMR1_CMP_MATCH_B      0b10100000
#define ADC_u8TMR1_OVF              0b11000000
#define ADC_u8TMR1_CAPTURE_EVENT    0b11100000

/**
 * @brief Initialize the ADC.
 *
 * This function initializes the ADC by setting the prescaler, adjustment, and 
 * reference voltage.
 * The ADC must be initialized before starting a conversion.
 * The ADC must be initialized before setting the trigger.
 *
 * @param[in] ADC_u8Prescaler The prescaler value. From the values above.
 * @param[in] ADC_u8Adjustment The adjustment value. From the values above.
 * @param[in] ADC_u8RefVoltage The reference voltage value.
 *
 * @return ES_t Returns ES_OK if the initialization is successful, otherwise 
 *         returns ES_OUT_OF_RANGE if any of the input parameters is out of range.
 */
ES_t ADC_enuInit(u8 ADC_u8Prescaler, u8 ADC_u8Adjustment, u8 ADC_u8RefVoltage);




/**
 * @brief Set the ADC trigger.
 *
 * The ADC must be initialized before setting the trigger.
 * A channel must be selected before setting the trigger.
 * This fucntion can not start a conversion.
 * The ADC_enuStartOneConversion() function must be used to start a conversions
 * This fucntion can be used even if the ADC's interrupt is enabled.
 *
 * @param[in] ADC_u8Trigger The trigger value. From the values above.
 *
 * @return ES_t Returns ES_OK if the trigger is set successfully, otherwise 
 *         returns ES_OUT_OF_RANGE if the input parameter is out of range.
 */
ES_t ADC_enuSetTrigger(u8 ADC_u8Trigger);

/**
 * @brief Disable the ADC trigger.
 *
 * This function sets the ADC to single conversion mode.
 *
 * This function disables the ADC trigger.
 */
void ADC_voidDisableTrigger(void);





/**
 * @brief Set the ADC channel.
 *
 * This function sets the ADC channel.
 * Changing the channel during a conversion will not affect the current conversion.
 *
 * @param[in] ADC_u8Channel The channel value. (0x00 - 0x1F)
 *
 * @return ES_t Returns ES_OK if the channel is set successfully, otherwise 
 *         returns ES_OUT_OF_RANGE if the input parameter is out of range.
 */
ES_t ADC_enuSetChannel(u8 ADC_u8Channel);





/**
 * @brief Start one ADC conversion.
 */
void ADC_voidStartOneConversion(void);







/**
 * @brief Get the ADC value.
 *
 * Gets the current value of the last conversion immediately.
 * Intended for use in the callback function.
 *
 * @return u16 The ADC value.
 */
u16 ADC_u16GetValue();

/**
 * @brief Get the high byte of the ADC value.
 *
 * This function gets the high byte of the ADC value.
 * Intended for use in the callback function.
 *
 * @return u8 The high byte of the ADC value.
 */
u8 ADC_u8GetHighValue();






/**
 * @brief Get the ADC value using polling.
 *
 * Waits for the current conversion to finish and returns the result.
 * If there is not a conversion in progress, it returns the last result.
 *
 * @return u16 The ADC value.
 */
u16 ADC_u16GetValuePolling();

/**
 * @brief Get the high byte of the ADC value using polling.
 *
 * Waits for the current conversion to finish and returns the result.
 * If there is not a conversion in progress, it returns the last result.
 *
 * @return u8 The high byte of the ADC value.
 */
u8 ADC_u8GetHighValuePolling();






/**
 * @brief Set the ADC callback function.
 *
 * @param[in] Copy_ptr The function pointer to the callback function.
 *
 * @return ES_t Returns ES_OK if the callback function is set successfully, 
 *         otherwise returns ES_NULL_POINTER if the input parameter is a null 
 *         pointer.
 */
ES_t ADC_enuSetCallBack(void (*Copy_pFuncAppFun)(void));

/**
 * @brief Disable the ADC interrupt.
 */
void ADC_voidDisableInterrupt(void);

/**
 * @brief Enable the ADC interrupt.
 */
void ADC_voidEnableInterrupt(void);



/**
 * @brief Halt the ADC without changing the settings.
 */
void ADC_voidHultADC(void);

#endif /* ADC_INTERFACE_H_ */
