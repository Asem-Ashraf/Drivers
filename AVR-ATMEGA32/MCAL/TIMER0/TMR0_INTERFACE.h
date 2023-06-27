#ifndef TMR0_INTERFACE_H
#define TMR0_INTERFACE_H
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#define TMR0_u8NormalMode       0
#define TMR0_u8PhaseCorrectPWM  1
#define TMR0_u8CTCMode          2
#define TMR0_u8FastPWM          3

#define TMR0_u8OC0Disconnected  0
#define TMR0_u8OC0Toggle        1
#define TMR0_u8OC0Clear         2
#define TMR0_u8OC0Set           3

#define TMR0_u8OC0NonInverting  2
#define TMR0_u8OC0Inverting     3

#define TMR0_u8NoClk            0
#define TMR0_u8Clk              1
#define TMR0_u8Clk_8            2
#define TMR0_u8Clk_64           3
#define TMR0_u8Clk_256          4
#define TMR0_u8Clk_1024         5
#define TMR0_u8ExtFallingEdge   6
#define TMR0_u8ExtRisingEdge    7


/**
 * @brief  Initializes Timer0 with the specified configuration settings.
 *         This function initializes Timer0 with the specified clock source, 
 *         mode, output compare pin configuration, preload value, and Clear 
 *         Timer on Compare (CTC) mode settings.
 * @param  Copy_u8clkSource The clock source to use for Timer0.
 * @values TMR0_u8NoClk         
 *         TMR0_u8Clk           
 *         TMR0_u8Clk_8         
 *         TMR0_u8Clk_64        
 *         TMR0_u8Clk_256       
 *         TMR0_u8Clk_1024      
 *         TMR0_u8ExtFallingEdge
 *         TMR0_u8ExtRisingEdge 
 *
 * @param  Copy_u8mode The mode to use for Timer0.
 * @values TMR0_u8NormalMode     
//         TMR0_u8PhaseCorrectPWM
//         TMR0_u8CTC            
//         TMR0_u8FastPWM        
//
 * @param  Copy_u8OC0PinConfig The output compare pin configuration to use for 
 *         Timer0.
 * @values TMR0_u8OC0Disconnected
 *         TMR0_u8OC0Toggle      
 *         TMR0_u8OC0Clear       
 *         TMR0_u8OC0Set         
 *         TMR0_u8OC0NonInverting
 *         TMR0_u8OC0Inverting   
 *
 * @param  Copy_u8Preload The preload value to use for Timer0 (0-255).
 *
 * @param  Copy_u8OCValue The Output-Compare value mode setting to use for Timer0 (0-255).
 *
 * @return An error status code of type ES_t, indicating success or failure of 
 *         the initialization process.
 */
ES_t TMR0_enuInit(u8 Copy_u8clkSource,
                  u8 Copy_u8mode,
                  u8 Copy_u8OC0PinConfig,
                  u8 Copy_u8Preload,
                  u8 Copy_u8OCValue);


/**
 * @brief Sets the preload value of Timer0.
 *        This function sets the preload value of Timer0, which determines the 
 *        initial value of the timer counter.
 *        The preload value is used to adjust the frequency and duty cycle of 
 *        the PWM waveform generated by Timer0.
 *
 * @param TMR0_u8Preload Preload value to set for Timer0 (0-255).
 *
 * @return None.
 */
void TMR0_SetPreload(u8 Copy_u8Preload);


/**
 * @brief Sets the output compare value of Timer0.
 *        This function sets the output compare value of Timer0, which controls 
 *        the behavior of the output waveform generated by Timer0.
 *        The output compare value determines when the output waveform changes 
 *        state, either from low to high or from high to low.
 *
 * @param TMR0_u8OCValue Output compare value to set for Timer0 (0-255).
 *
 * @return None.
 */
void TMR0_SetOutputCompareValue(u8 Copy_u8OCValue);



void TMR0_EnableOverflowInterrupt();

ES_t TMR0_enuSetOverflowCallback(void (*Copy_pfuncIsrOverflow)());

void TMR0_DisableOverflowInterrupt();



void TMR0_EnableCompareMatchInterrupt();

ES_t TMR0_enuSetCompareMatchCallback(void (*Copy_pfuncIsrCTC)());

void TMR0_DisableCompareMatchInterrupt();



void TMR0_StopTimer0();



// FEATURES

/**
 * @brief  Waits for a specified number of milliseconds using busy-waiting and 
 *         Timer0 interrupts.
 *         This function uses the Timer0 hardware to generate interrupts at a 
 *         specified interval to count the delay time.
 *         The function waits for the specified delay time to elapse before 
 *         returning.
 *
 * @param  Copy_u32Timems Delay time in milliseconds to wait for.
 *
 * @return ES_t Returns ES_OK if the function was executed successfully, or an 
 *         error code if execution failed.
 */
ES_t TMR0_enuBusyWaitms(u32 Copy_u32Timems);

/**
 * @brief  Executes a function continuously with a specified delay between each 
 *         execution.
 *         This function uses the Timer0 hardware to generate interrupts at the 
 *         specified interval.
 *         The function is executed in the interrupt service routine (ISR).
 *
 * @param  Copy_u32Timems Delay in milliseconds between each execution of the 
 *         function.
 *
 * @param  Copy_pfuncIsr Pointer to the function to be executed.
 *
 * @return ES_t Returns ES_OK if the function was registered successfully, or an 
 *         error code if registration failed.
 *         Possible error codes are: ES_NULL_POINTER.
 */
ES_t TMR0_enuDelayedExecutionContiniuousms(u32 Copy_u32Timems,void (*Copy_pfuncIsr)());

/**
 * @brief  Sets the duty cycle of a PWM waveform generated by Timer0.
 *         This function uses Timer0 hardware to generate a PWM waveform with a 
 *         specified duty cycle and frequency.
 *
 * @param  Copy_u8Duty PWM duty cycle as a percentage (0-100).
 *
 * @return ES_t Returns ES_OK if the function was executed successfully, or an 
 *         error code if execution failed.
 *         Possible error codes are: ES_OUT_OF_RANGE.
 */
ES_t TMR0_enuSetDuty(u8 Copy_u8Duty);

#endif
