#include "../../LIB/Bit_Math.h"
#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"

#include "TMR0_PRIVATE.h"

extern u16 CPU_u16FreqKHz;
// Timer0 Compare Match interrupt
static void (*TMR0_CompareMatchCallBack)(void) = NULL;
void __vector_10(void) __attribute__((signal));
void __vector_10(void){
    if (TMR0_CompareMatchCallBack!=NULL)
        TMR0_CompareMatchCallBack();
}

// Timer0 Overflow interrupt
static void (*TMR0_OverflowCallback)(void) = NULL;
void __vector_11(void) __attribute__((signal));
void __vector_11(void){ 
    if (TMR0_OverflowCallback!=NULL)
        TMR0_OverflowCallback();
}

ES_t TMR0_enuInit(u8 TMR0_u8clkSource, u8 TMR0_u8mode,
                  u8 TMR0_u8OC0PinConfig, u8 TMR0_u8Preload,
                  u8 TMR0_u8CTC){
    if ((TMR0_u8clkSource>7)||(TMR0_u8mode>3)||
        (TMR0_u8OC0PinConfig>3)) {
        return ES_OUT_OF_RANGE;
    }
    // Stop T/C
    TCCR0 = 0;
    // Set register values
    OCR0  = TMR0_u8CTC;
    TCNT0 = TMR0_u8Preload;
    // Setting OC0 pin to output
    if (TMR0_u8OC0PinConfig>0) SetBit(DDRB,3);
    // Set operation mode
    TCCR0 = TMR0_u8clkSource 
          + (TMR0_u8OC0PinConfig<<4)
          + ((TMR0_u8mode&(2))<<2) 
          + ((TMR0_u8mode&(1))<<6);
    return ES_OK;
}

void TMR0_SetPreload(u8 TMR0_u8Preload){
    TCNT0 = TMR0_u8Preload;
}
void TMR0_SetOCR0(u8 TMR0_u8CTC){
    OCR0 = TMR0_u8CTC;
}
ES_t TMR0_enuSetTOV0Callback(void (*TMR0_pfuncIsrTOV0)()){
    if (TMR0_pfuncIsrTOV0!=NULL) {
        TMR0_OverflowCallback = TMR0_pfuncIsrTOV0;
        return ES_OK;
    }
    else {
        return ES_NULL_POINTER;
    }
}
void TMR0_EnableTOV0Interrupt(){
    SetBit(TIMSK, 0);
}
void TMR0_DisableTOV0Interrupt(){
    ClrBit(TIMSK, 0);
}
ES_t TMR0_enuSetOC0Callback(void (*TMR0_pfuncIsrOC0)()){
    if (TMR0_pfuncIsrOC0!=NULL) {
        TMR0_CompareMatchCallBack = TMR0_pfuncIsrOC0;
        return ES_OK;
    }
    else {
        return ES_NULL_POINTER;
    }
}
void TMR0_EnableOC0Interrupt(){
    SetBit(TIMSK, 1);
}
void TMR0_DisableOC0Interrupt(){
    ClrBit(TIMSK, 1);
}
void TMR0_StopTimer0(){
    TCCR0=0;
}

// FEATURES
#define TMR0_u32DelayPrescale 1024

// visible only in this file
static volatile u32 TMR0_u32DelayCountSync;
void TMR0_SyncDelayISR(){
    TMR0_u32DelayCountSync++;
}
ES_t TMR0_enuBusyWaitms(u32 TMR0_u32Timems){
    if(TMR0_u32Timems==0) return ES_OK;
    TCCR0 = 0;
    const f32 fullCountTime = (CPU_u16FreqKHz*256.0/TMR0_u32DelayPrescale);
    f32 perciseOvf = TMR0_u32Timems/fullCountTime;
    u32 overflowCountSync = perciseOvf;
    u8 startValueSync = 255*(1 - (perciseOvf-(u32)perciseOvf));
    if (startValueSync!=0) overflowCountSync++;
    TMR0_u32DelayCountSync=0;
    TMR0_OverflowCallback= &TMR0_SyncDelayISR;
    SetBit(TIMSK, 0);
    ES_t error = TMR0_enuInit(TMR0_u8Clk_1024, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValueSync, 0);
    if (error != ES_OK) return error;
    while (1){
        if (overflowCountSync<=TMR0_u32DelayCountSync) {
            break;
        }
    }
    TCCR0 = 0;
    ClrBit(TIMSK, 0);
    return ES_OK;
}
ES_t TMR0_enuSetDuty(u8 TMR0_u8Duty){
    if(TMR0_u8Duty>100) return ES_OUT_OF_RANGE;
    u8 compareValue = (u8)TMR0_u8Duty*255.0/100.0;
    return TMR0_enuInit(TMR0_u8Clk_8, TMR0_u8FastPWM, TMR0_u8OC0NonInverting, 0, compareValue);
}

static u32 TMR0_u32DelayCountAsync;
static void (*TMR0_DelayCountAsyncFunc)(void) = NULL;
static u32 overflowCount;
static u8 startValue;
void TMR0_AsyncDelayISR(){
    if(!(--TMR0_u32DelayCountAsync)) {
        TMR0_DelayCountAsyncFunc();
        TCNT0 = startValue;
        TMR0_u32DelayCountAsync=overflowCount;
    }
}
ES_t TMR0_enuDelayedExecutionContiniuousms(u32 TMR0_u32Timems,void (*TMR0_pfuncIsr)()){
    if (TMR0_pfuncIsr==NULL) return ES_NULL_POINTER;
    TCCR0 = 0;
    const f32 fullCountTime = (CPU_u16FreqKHz*256.0/TMR0_u32DelayPrescale);
    f32 perciseOvf = TMR0_u32Timems/fullCountTime;
    overflowCount = (u32)perciseOvf;
    startValue = 256*(1 - (perciseOvf-overflowCount));
    if (startValue!=0) overflowCount++;
    TMR0_u32DelayCountAsync=overflowCount;
    TMR0_DelayCountAsyncFunc=TMR0_pfuncIsr;
    TMR0_OverflowCallback = &TMR0_AsyncDelayISR;
    ES_t error = TMR0_enuInit(TMR0_u8Clk_1024, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValue, 0);
    if (error != ES_OK) return error;
    SetBit(TIMSK, 0);
    return ES_OK;
}

// TODO
ES_t TMR0_enuSetDutyandFrequency(u8 TMR0_u8Duty,u8 frequency){

}
