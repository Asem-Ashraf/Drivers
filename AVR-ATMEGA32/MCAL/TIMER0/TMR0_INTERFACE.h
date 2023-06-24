#ifndef TMR0_INTERFACE_H
#define TMR0_INTERFACE_H

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


// Starts the counter with the given configuration
// TMR0_u8clkSource   : TMR0_u8NoClk         
//                      TMR0_u8Clk           
//                      TMR0_u8Clk_8         
//                      TMR0_u8Clk_64        
//                      TMR0_u8Clk_256       
//                      TMR0_u8Clk_1024      
//                      TMR0_u8ExtFallingEdge
//                      TMR0_u8ExtRisingEdge 
//
// TMR0_u8mode        : TMR0_u8NormalMode     
//                      TMR0_u8PhaseCorrectPWM
//                      TMR0_u8CTC            
//                      TMR0_u8FastPWM        
//
// TMR0_u8OC0PinConfig: TMR0_u8OC0Disconnected
//                      TMR0_u8OC0Toggle      
//                      TMR0_u8OC0Clear       
//                      TMR0_u8OC0Set         
//                      TMR0_u8OC0NonInverting
//                      TMR0_u8OC0Inverting   
//
// TMR0_u8TCNT0       : Counter initial value
//
// TMR0_u8OCR0        : OCR0 value
ES_t TMR0_enuInit(u8 TMR0_u8clkSource,
                  u8 TMR0_u8mode,
                  u8 TMR0_u8OC0PinConfig,
                  u8 TMR0_u8Preload,
                  u8 TMR0_u8CTC);


// Set Initial counter value
// TMR0_u8Preload     : Counter initial value
void TMR0_SetPreload(u8 TMR0_u8Preload);


// Set Clear on Compare Match value
// TMR0_u8CTC        : CTC value
void TMR0_SetCTC(u8 TMR0_u8CTC);


void TMR0_EnableTOV0Interrupt();


void TMR0_DisableTOV0Interrupt();


void TMR0_EnableOC0Interrupt();


void TMR0_DisableOC0Interrupt();


ES_t TMR0_enuSetTOV0Callback(void (*TMR0_pfuncIsrTOV0)());


ES_t TMR0_enuSetOC0Callback(void (*TMR0_pfuncIsrOC0)());


void TMR0_StopTimer0();



// FEATURES

// The MCU stops execution for the time specified
ES_t TMR0_enuBusyWaitms(u32 TMR0_u32Timems);

// The function is executed after the time specified Asynchronously
// The function is continuously executed with the time specified between each
// execution
ES_t TMR0_enuDelayedExecutionContiniuousms(u32 TMR0_u32Timems,void (*TMR0_pfuncIsr)());

ES_t TMR0_enuSetDuty(u8 TMR0_u8Duty);

#endif
