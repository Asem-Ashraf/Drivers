#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_PRIVATE.h"

static void (*ADC_CallBack)(void) = NULL;

void __vector_16(void) __attribute__((signal,used));
void __vector_16(void) {
    if (ADC_CallBack != NULL) {
        ADC_CallBack();
    }
}

ES_t ADC_enuInit(u8 ADC_u8Prescaler,u8 ADC_u8Adjustment,u8 ADC_u8RefVoltage){
    if (((ADC_u8Prescaler &0b11111000) != 0)||
        ((ADC_u8Adjustment&0b11011111) != 0)||
        ((ADC_u8RefVoltage&0b00111111) != 0)||
         (ADC_u8RefVoltage == 0b10000000)) 
        return ES_OUT_OF_RANGE;

    // set the adjustment, set the reference voltage
    ADMUX  = (ADC_u8Adjustment|ADC_u8RefVoltage);
    // set the prescaler and enable the ADC
    ADCSRA = ADC_u8Prescaler|(1<<ADEN);
    return ES_OK;
}

ES_t ADC_enuSetTrigger(u8 ADC_u8Trigger){
    // check if the trigger is valid
    if ((ADC_u8Trigger&0b00011111) != 0)
        return ES_OUT_OF_RANGE;
    // overwrite the trigger
    SFIOR =(SFIOR & 0x0F)|ADC_u8Trigger;
    // enable the ADC auto trigger 
    SetBit(ADCSRA,ADATE);
    return ES_OK;
}
void ADC_voidDisableTrigger(){
    // disable the ADC auto trigger 
    ClrBit(ADCSRA,ADATE);
}

ES_t ADC_enuSetChannel(u8 ADC_u8Channel){
    // check if the channel is valid
    if (ADC_u8Channel > 0x31) 
        return ES_OUT_OF_RANGE;
    // overwrite channel
    ADMUX = (ADMUX & 0xE0) | ADC_u8Channel;
    return ES_OK;
}

void ADC_voidStartOneConversion(){
    // start conversion
    SetBit(ADCSRA,ADSC);
}

u16 ADC_u16GetValue(){
    return ADC_VALUE;
}

u8 ADC_u8GetHighValue(){
    return ADCH;
}

u16 ADC_u16GetValuePolling(){
    // wait until conversion is done
    while (GetBit(ADCSRA,ADSC));
    return  ADC_VALUE;
}

u8 ADC_u8GetHighValuePolling(){
    // wait until conversion is done
    while (GetBit(ADCSRA,ADSC));
    return ADCH;
}


ES_t ADC_enuSetCallBack(void (*Copy_ptr)(void)){
    if (Copy_ptr == NULL) { return ES_NULL_POINTER; }
    ADC_CallBack = Copy_ptr;
    return ES_OK;
}

void ADC_voidEnableInterrupt(){
    // enable the ADC interrupt
    SetBit(ADCSRA,ADIE);
}

void ADC_voidDisableInterrupt(){
    // disable the ADC interrupt
    ClrBit(ADCSRA,ADIE);
}

void ADC_voidHultADC(){
    ADCSRA = 0;
}
