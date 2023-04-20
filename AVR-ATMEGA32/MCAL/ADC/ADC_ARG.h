#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
// ADMUX Register
#define ADC_u8CH0           0
#define ADC_u8CH1           1
#define ADC_u8CH2           2
#define ADC_u8CH3           3
#define ADC_u8CH4           4
#define ADC_u8CH5           5
#define ADC_u8CH6           6
#define ADC_u8CH7           7

#define ADC_u8AREF          0
#define ADC_u8AVCC          1
#define ADC_u8INTERNAL      3

#define ADC_u8RIGHT_ADJ     0
#define ADC_u8LEFT_ADJ      1

// ADCSRA Register
#define ADC_u8PRESCALER_2           1
#define ADC_u8PRESCALER_4           2
#define ADC_u8PRESCALER_8           3
#define ADC_u8PRESCALER_16          4
#define ADC_u8PRESCALER_32          5
#define ADC_u8PRESCALER_64          6
#define ADC_u8PRESCALER_128         7

#define ADC_u8INTERRUPT             1
#define ADC_u8POLLING               0

// SFIOR Register
#define ADC_u8FREE_RUNNING          0
#define ADC_u8ANALOG_CMP            1
#define ADC_u8EXT_INT               2
#define ADC_u8TMR0_CMp_MATCH        3
#define ADC_u8TMR0_OVF              4
#define ADC_u8TMR1_CMP_MATCH_B      5
#define ADC_u8TMR1_OVF              6
#define ADC_u8TMR1_CAPTURE_EVENT    7

#endif /* ADC_PRIVATE_H_ */
