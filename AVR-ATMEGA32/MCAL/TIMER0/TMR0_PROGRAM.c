#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/CPU_FREQ.h"

#include "../DIO/DIO_INTERFACE.h"

#include "TMR0_PRIVATE.h"

// Timer0 Overflow interrupt
static void (*TMR0_OverflowCallback)(void) = NULL;

void __vector_11(void) __attribute__((signal));
void __vector_11(void){ 
    if (TMR0_OverflowCallback!=NULL)
        TMR0_OverflowCallback();
}
// Timer0 Compare Match interrupt
static void (*TMR0_CompareMatchCallBack)(void) = NULL;

void __vector_10(void) __attribute__((signal));
void __vector_10(void){
    if (TMR0_CompareMatchCallBack!=NULL)
        TMR0_CompareMatchCallBack();
}




ES_t TMR0_enuInit(u8 Copy_u8clkSource,
                  u8 Copy_u8mode,
                  u8 Copy_u8OC0PinConfig,
                  u8 Copy_u8Preload,
                  u8 Copy_u8OCValue){
    if ((Copy_u8clkSource>7)||
        ((Copy_u8mode&0b10110111)!=0)||
        ((Copy_u8OC0PinConfig&0b11001111)!=0)) {
        return ES_OUT_OF_RANGE;
    }
    // Stop T/C
    TCCR0 = 0;
    // Set register values
    OCR0  = Copy_u8OCValue;
    TCNT0 = Copy_u8Preload;
    ES_t local_error = ES_OK;
    // Setting OC0 pin to output
    if (Copy_u8OC0PinConfig>0)
        local_error = DIO_enuSetPinDirection(DIO_u8DDRB, OC0, DIO_u8OUTPUT);
    // Set operation mode
    TCCR0 = Copy_u8clkSource 
          + Copy_u8OC0PinConfig
          + Copy_u8mode;
    return local_error;
}
void TMR0_SetPreload(u8 Copy_u8Preload){
    TCNT0 = Copy_u8Preload;
}
void TMR0_SetOutputCompareValue(u8 Copy_u8OCValue){
    OCR0 = Copy_u8OCValue;
}





void TMR0_EnableOverflowInterrupt(){
    SetBit(TIMSK, TOIE0);
}
ES_t TMR0_enuSetOverflowCallback(void (*Copy_pfuncIsrOverflow)()){
    if (Copy_pfuncIsrOverflow==NULL) return ES_NULL_POINTER;
    TMR0_OverflowCallback = Copy_pfuncIsrOverflow;
    return ES_OK;
}
void TMR0_DisableOverflowInterrupt(){
    ClrBit(TIMSK, TOIE0);
}




ES_t TMR0_enuSetCompareMatchCallback(void (*Copy_pfuncIsrCTC)()){
    if (Copy_pfuncIsrCTC==NULL)  return ES_NULL_POINTER;
    TMR0_CompareMatchCallBack = Copy_pfuncIsrCTC;
    return ES_OK;
}
void TMR0_EnableCompareMatchInterrupt(){
    SetBit(TIMSK, OCIE0);
}
void TMR0_DisableCompareMatchInterrupt(){
    ClrBit(TIMSK, OCIE0);
}



void TMR0_StopTimer0(){
    TCCR0=0;
}




// FEATURES

// visible only in this file
static volatile u32 Copy_u32DelayCountSync;
static void TMR0_SyncDelayISR(){
    Copy_u32DelayCountSync++;
}
ES_t TMR0_enuBusyWaitms(u32 Copy_u32Timems){
    if(Copy_u32Timems==0) return ES_OK;
    TCCR0 = 0;
    const f32 fullCountTimems = ((1000.0/CPU_u32Freq)*Copy_f32RegisterCounts)*Copy_u32DelayPrescale;
    f32 perciseOvf = Copy_u32Timems/fullCountTimems;
    u32 overflowCountSync = perciseOvf;
    u8 startValueSync = Copy_u8RegisterMAX*(1 - (perciseOvf-(u32)perciseOvf));
    if (startValueSync!=0) overflowCountSync++;
    Copy_u32DelayCountSync=0;
    TMR0_OverflowCallback= &TMR0_SyncDelayISR;
    SetBit(TIMSK, 0);
    ES_t error = TMR0_enuInit(TMR0_u8Clk_1024, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValueSync, 0);
    if (error != ES_OK) return error;
    while (1){
        if (overflowCountSync<=Copy_u32DelayCountSync) {
            break;
        }
    }
    TCCR0 = 0;
    ClrBit(TIMSK, 0);
    return ES_OK;
}
// It does not go bellow 1.1ms because the MCU instruction take 1us on 1MHz freq
// useless function
ES_t TMR0_enuBusyWaitus(u32 Copy_u32Timeus){
    if(Copy_u32Timeus==0) return ES_OK;
    TCCR0 = 0;
    const f32 fullCountTimeus = ((1000000.0/CPU_u32Freq)*Copy_f32RegisterCounts);
    f32 perciseOvf = Copy_u32Timeus/fullCountTimeus;
    u32 overflowCountSync = perciseOvf;
    u8 startValueSync = Copy_u8RegisterMAX*(1 - (perciseOvf-(u32)perciseOvf));
    if (startValueSync!=0) overflowCountSync++;
    Copy_u32DelayCountSync=0;
    TMR0_OverflowCallback= &TMR0_SyncDelayISR;
    SetBit(TIMSK, 0);
    ES_t error = TMR0_enuInit(TMR0_u8Clk, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValueSync, 0);
    if (error != ES_OK) return error;
    while (1){
        if (overflowCountSync<=Copy_u32DelayCountSync) {
            break;
        }
    }
    TCCR0 = 0;
    ClrBit(TIMSK, 0);
    return ES_OK;
}
ES_t TMR0_enuSetDuty(u8 Copy_u8Duty){
    if(Copy_u8Duty>100) return ES_OUT_OF_RANGE;
    u8 compareValue = (u8)((Copy_u8Duty*Copy_u8RegisterMAX)/100.0);
    return TMR0_enuInit(TMR0_u8Clk_8, TMR0_u8FastPWM, TMR0_u8OC0NonInverting, 0, compareValue);
}

static u32 Copy_u32DelayCountAsync;
static void (*TMR0_DelayCountAsyncFunc)(void) = NULL;
static u32 overflowCount;
static u8 startValue;
static void TMR0_AsyncDelayISR(){
    if(!(--Copy_u32DelayCountAsync)) {
        TMR0_DelayCountAsyncFunc();
        TCNT0 = startValue;
        Copy_u32DelayCountAsync=overflowCount;
    }
}
ES_t TMR0_enuDelayedExecutionContiniuousms(u32 Copy_u32Timems,void (*TMR0_pfuncIsr)()){
    if (TMR0_pfuncIsr==NULL) return ES_NULL_POINTER;
    TCCR0 = 0;
    const f32 fullCountTimems = ((1000.0/CPU_u32Freq)*Copy_f32RegisterCounts)*Copy_u32DelayPrescale;
    f32 perciseOvf = Copy_u32Timems/fullCountTimems;
    overflowCount = (u32)perciseOvf;
    startValue = Copy_u8RegisterMAX*(1 - (perciseOvf-overflowCount));
    if (startValue!=0) overflowCount++;
    Copy_u32DelayCountAsync=overflowCount;
    TMR0_DelayCountAsyncFunc=TMR0_pfuncIsr;
    TMR0_OverflowCallback = &TMR0_AsyncDelayISR;
    SetBit(TIMSK, 0);
    return  TMR0_enuInit(TMR0_u8Clk_1024, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValue, 0);
}

// TODO
// ES_t TMR0_enuSetDutyandFrequency(u8 Copy_u8Duty,u8 frequency){
//
// }
