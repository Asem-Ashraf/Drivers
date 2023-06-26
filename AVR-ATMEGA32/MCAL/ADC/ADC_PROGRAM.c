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
    // check if the prescaler is valid
    if (ADC_u8Prescaler > 7) { return ES_OUT_OF_RANGE; }
    // check if the adjustment is valid
    if (ADC_u8Adjustment > 1) { return ES_OUT_OF_RANGE; }
    // check if the reference voltage is valid
    if (ADC_u8RefVoltage > 3) { return ES_OUT_OF_RANGE; }
    // set the prescaler 
    ADCSRA = (ADCSRA & 0xF8) | ADC_u8Prescaler;
    // set the adjustment 
    ADMUX  = (ADMUX & 0xDF) | (ADC_u8Adjustment << ADLAR);
    // set the reference voltage 
    ADMUX  = (ADMUX & 0x3F) | (ADC_u8RefVoltage << REFS0);
    // set ADEN
    SetBit(ADCSRA,ADEN);
    return ES_OK;
}

ES_t ADC_enuSetTrigger(u8 ADC_u8Trigger){
    // check if the trigger is valid
    if (ADC_u8Trigger > 0x07) { return ES_OUT_OF_RANGE; }
    // set the trigger
    SFIOR = (SFIOR & 0x1F) | (ADC_u8Trigger<<5);
    // enable the ADC auto trigger 
    SetBit(ADCSRA,ADATE);
    return ES_OK;
}
void ADC_enuDisableTrigger(){
    // disable the ADC auto trigger 
    ClrBit(ADCSRA,ADATE);
}

ES_t ADC_enuSetChannel(u8 ADC_u8Channel){
    // check if the channel is valid
    if (ADC_u8Channel > 0x31) { return ES_OUT_OF_RANGE; }
    // set the channel
    ADMUX = (ADMUX & 0xE0) | ADC_u8Channel;
    return ES_OK;
}

void ADC_enuStartOneConversion(){
    // start conversion
    SetBit(ADCSRA,ADSC);
}

ES_t ADC_enuGetValue(u16 *ADC_u16Data){
    // check if the pointer is valid
    if (ADC_u16Data == NULL) { return ES_NULL_POINTER; }
    // store the result
    *ADC_u16Data = ADC_VALUE;
    return ES_OK;
}

ES_t ADC_enuGetHighValue(u8 *ADC_u8Data){
    // check if the pointer is valid
    if (ADC_u8Data == NULL) { return ES_NULL_POINTER; }
    // store the result
    *ADC_u8Data = ADCH;
    return ES_OK;
}

ES_t ADC_enuGetValuePolling(u16 *ADC_u16Data){
    // check if the pointer is valid
    if (ADC_u16Data == NULL) { return ES_NULL_POINTER; }
    // wait until conversion is done
    while (GetBit(ADCSRA,ADSC));
    // store the result
    *ADC_u16Data = ADC_VALUE;
    return ES_OK;
}

ES_t ADC_enuGetHighValuePolling(u8 *ADC_u8Data){
    // check if the pointer is valid
    if (ADC_u8Data == NULL) { return ES_NULL_POINTER; }
    // wait until conversion is done
    while (GetBit(ADCSRA,ADSC));
    // store the result
    *ADC_u8Data = ADCH;
    return ES_OK;
}


ES_t ADC_enuSetCallBack(void (*Copy_ptr)(void)){
    if (Copy_ptr == NULL) { return ES_NULL_POINTER; }
    ADC_CallBack = Copy_ptr;
    return ES_OK;
}

void ADC_enuEnableInterrupt(){
    // enable the ADC interrupt
    SetBit(ADCSRA,ADIE);
}

void ADC_enuDisableInterrupt(){
    // disable the ADC interrupt
    ClrBit(ADCSRA,ADIE);
}

void ADC_enuHultADC(){
    ADCSRA = 0;
}
