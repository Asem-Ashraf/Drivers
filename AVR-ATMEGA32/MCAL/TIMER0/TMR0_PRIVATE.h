#ifndef TMR0_PRIVATE_H
#define TMR0_PRIVATE_H

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

#define TIMSK (*(volatile u8*)0x59)
#define TCCR0 (*(volatile u8*)0x53)
#define TCNT0 (*(volatile u8*)0x52)
#define OCR0  (*(volatile u8*)0x5C)
#define TIFR  (*(volatile u8*)0x58)
#define DDRB  (*(volatile u8*)0x37)

#define Copy_u32DelayPrescale 1024
#define Copy_u32DelayPrescaleus 1
#define Copy_f32RegisterCounts 256.0
#define Copy_u8RegisterMAX 255

#endif // TMR0_PRIVATE_H
