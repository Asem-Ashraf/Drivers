#ifndef TMR0_INTERFACE_H
#define TMR0_INTERFACE_H

#define TMR0_u8NormalMode       0
#define TMR0_u8PhaseCorrectPWM  1
#define TMR0_u8CTC              2
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


ES_t TMR0_enuInit(u8 TMR0_u8clkSource,
                  u8 TMR0_u8mode,
                  u8 TMR0_u8OC0PinConfig,
                  u8 TMR0_u8TCNT0,
                  u8 TMR0_u8OCR0);

void TMR0_SetTCNT0(u8 TMR0_u8TCNT0);

void TMR0_SetOCR0(u8 TMR0_u8OCR0);

void TMR0_EnableTOV0Interrupt();

void TMR0_DisableTOV0Interrupt();

void TMR0_EnableOC0Interrupt();

void TMR0_DisableOC0Interrupt();

ES_t TMR0_enuSetTOV0Callback(void (*TMR0_pfuncIsrTOV0)());

ES_t TMR0_enuSetOC0Callback(void (*TMR0_pfuncIsrOC0)());

void TMR0_StopTimer0();

// FEATURES
ES_t TMR0_enuDelaymsSync(u32 TMR0_u32Time);

#endif
