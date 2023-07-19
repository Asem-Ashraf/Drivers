#ifndef TMR0_PRIVATE_H
#define TMR0_PRIVATE_H

#define TMR0_u8NormalMode       0b00000000
#define TMR0_u8PhaseCorrectPWM  0b01000000
#define TMR0_u8CTCMode          0b00001000
#define TMR0_u8FastPWM          0b01001000

#define TMR0_u8OC0Disconnected  0b00000000
#define TMR0_u8OC0Toggle        0b00010000
#define TMR0_u8OC0Clear         0b00100000
#define TMR0_u8OC0Set           0b00110000

#define TMR0_u8OC0NonInverting  0b00100000
#define TMR0_u8OC0Inverting     0b00110000

#define TMR0_u8NoClk            0
#define TMR0_u8Clk              1
#define TMR0_u8Clk_8            2
#define TMR0_u8Clk_64           3
#define TMR0_u8Clk_256          4
#define TMR0_u8Clk_1024         5
#define TMR0_u8ExtFallingEdge   6
#define TMR0_u8ExtRisingEdge    7

#define TIMSK (*(volatile u8*)0x59)
#define TOIE0 0
#define OCIE0 1

#define TCCR0 (*(volatile u8*)0x53)
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7

#define TCNT0 (*(volatile u8*)0x52)

#define OCR0  (*(volatile u8*)0x5C)

#define TIFR  (*(volatile u8*)0x58)

#define OC0   DIO_u8PIN3

#define Copy_u32DelayPrescale 1024
#define Copy_f32RegisterCounts 256.0
#define Copy_u8RegisterMAX 255

#endif // TMR0_PRIVATE_H
