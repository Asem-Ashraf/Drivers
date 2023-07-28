#ifndef TMR1_PRIVATE_H
#define TMR1_PRIVATE_H

#define TMR1_u8NormalMode                           0
#define TMR1_u8PhaseCorrectPWM_8_bit                1 
#define TMR1_u8PhaseCorrectPWM_9_bit                2              
#define TMR1_u8PhaseCorrectPWM_10_bit               3               
#define TMR1_u8CTC_OCR1A                            4
#define TMR1_u8FastPWM_8_bit                        5  
#define TMR1_u8FastPWM_9_bit                        6  
#define TMR1_u8FastPWM_10_bit                       7   
#define TMR1_u8PWMPhaseandFrequencyCorrect_ICR1     8                     
#define TMR1_u8PWMPhaseandFrequencyCorrect_OCR1A    9                      
#define TMR1_u8PWMPhaseCorrect_ICR1                 10         
#define TMR1_u8PWMPhaseCorrect_OCR1A                11          
#define TMR1_u8CTC_ICR1                             12
#define TMR1_u8FastPWM_ICR1                         14 
#define TMR1_u8FastPWM_OCR1A                        15  

#define TMR1_u8OC1xDisconnected  0
#define TMR1_u8OC1xToggle        1
#define TMR1_u8OC1xClear         2
#define TMR1_u8OC1xSet           3

#define TMR1_u8OC1xNonInverting  2
#define TMR1_u8OC1xInverting     3

#define TMR1_u8NoClk            0
#define TMR1_u8Clk              1
#define TMR1_u8Clk_8            2
#define TMR1_u8Clk_64           3
#define TMR1_u8Clk_256          4
#define TMR1_u8Clk_1024         5
#define TMR1_u8ExtFallingEdge   6
#define TMR1_u8ExtRisingEdge    7

#define TCCR1A (*(volatile u8*)0x4F)
#define TCCR1B (*(volatile u8*)0x4E)

#define TCNT1H (*(volatile u8*)0x4D)
#define TCNT1L (*(volatile u8*)0x4C)

#define OCR1AH (*(volatile u8*)0x4B)
#define OCR1AL (*(volatile u8*)0x4A)

#define OCR1BH (*(volatile u8*)0x49)
#define OCR1BL (*(volatile u8*)0x48)

#define ICR1H  (*(volatile u8*)0x47)
#define ICR1L  (*(volatile u8*)0x46)

#define TIMSK  (*(volatile u8*)0x59)
#define TIFR   (*(volatile u8*)0x58)



#define Copy_u32DelayPrescale 256
#define Copy_f32RegisterCounts 65536.0
#define Copy_u16RegisterMAX 65535

#endif // TMR1_PRIVATE_H
