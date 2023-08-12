#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

// ADMUX Register
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

// ADCSRA Register
#define ADC_u8PRESCALER_2           0b00000001
#define ADC_u8PRESCALER_4           0b00000010
#define ADC_u8PRESCALER_8           0b00000011
#define ADC_u8PRESCALER_16          0b00000100
#define ADC_u8PRESCALER_32          0b00000101
#define ADC_u8PRESCALER_64          0b00000110
#define ADC_u8PRESCALER_128         0b00000111

#define ADC_u8INTERRUPT             0x01
#define ADC_u8POLLING               0x00

// SFIOR Register
#define ADC_u8FREE_RUNNING          0b00000000
#define ADC_u8ANALOG_CMP            0b00100000
#define ADC_u8EXT_INT               0b01000000
#define ADC_u8TMR0_CMp_MATCH        0b01100000
#define ADC_u8TMR0_OVF              0b10000000
#define ADC_u8TMR1_CMP_MATCH_B      0b10100000
#define ADC_u8TMR1_OVF              0b11000000
#define ADC_u8TMR1_CAPTURE_EVENT    0b11100000

#define ADCSRA      (*(volatile u8 *)0x26)
#define ADEN    0x07
#define ADSC    0x06
#define ADATE   0x05
#define ADIF    0x04
#define ADIE    0x03
#define ADPS2   0x02
#define ADPS1   0x01
#define ADPS0   0x00

#define ADMUX       (*(volatile u8 *)0x27)
#define REFS1   0x07
#define REFS0   0x06
#define ADLAR   0x05
#define MUX4    0x04
#define MUX3    0x03
#define MUX2    0x02
#define MUX1    0x01
#define MUX0    0x00

#define SFIOR       (*(volatile u8 *)0x50)
#define ADTS2   0x07
#define ADTS1   0x06
#define ADTS0   0x05

#define ADCH        (*(volatile u8 *)0x25)
#define ADCL        (*(volatile u8 *)0x24)
#define ADC_VALUE   (*(volatile u16*)0x24)

#endif /* ADC_PRIVATE_H_ */
