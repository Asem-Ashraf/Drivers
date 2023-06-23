#include "../../LIB/Bit_Math.h"
#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"

#include "TMR0_PRIVATE.h"

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
                  u8 TMR0_u8OC0PinConfig, u8 TMR0_u8TCNT0,
                  u8 TMR0_u8OCR0){
    if ((TMR0_u8clkSource>7)||(TMR0_u8mode>3)||
        (TMR0_u8OC0PinConfig>3)) {
        return ES_OUT_OF_RANGE;
    }
    // Stop T/C
    TCCR0 = 0;
    // Set register values
    OCR0  = TMR0_u8OCR0;
    TCNT0 = TMR0_u8TCNT0;
    // Setting OC0 pin to output
    if (TMR0_u8OC0PinConfig>0) SetBit(DDRB,3);
    // Set operation mode
    TCCR0 = TMR0_u8clkSource 
          + (TMR0_u8OC0PinConfig<<4)
          + ((TMR0_u8mode&(1))<<3) 
          + ((TMR0_u8mode&(2))<<6);
    return ES_OK;
}

void TMR0_SetTCNT0(u8 TMR0_u8TCNT0){
    TCNT0 = TMR0_u8TCNT0;
}
void TMR0_SetOCR0(u8 TMR0_u8OCR0){
    OCR0 = TMR0_u8OCR0;
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
#define CPU_u16FreqKHz 1000u
#define TMR0_u32DelayPrescale 1024u

// visible only in this file
static u32 TMR0_u32DelayCountSync;
static void TMR0_SyncDelayISR(){
    TMR0_u32DelayCountSync++;
}

ES_t TMR0_enuBusyWait(u32 TMR0_u32Time){
    if(TMR0_u32Time==0) return ES_OK;
    TCCR0 = 0;
    u32 clkCounts = TMR0_u32Time*CPU_u16FreqKHz;
    u32 prescaledClkCounts = clkCounts/TMR0_u32DelayPrescale;
    if (TMR0_u32Time==1) prescaledClkCounts = 1;
    u32 overflowCount =1 + prescaledClkCounts/256;
    u32 startValue = 256 - prescaledClkCounts%256;
    TMR0_u32DelayCountSync=0;
    TMR0_CompareMatchCallBack = TMR0_SyncDelayISR;
    SetBit(TIMSK, 0);
    ES_t error;
    error = TMR0_enuInit(TMR0_u8Clk_1024, TMR0_u8NormalMode, TMR0_u8OC0Disconnected, startValue, 0);
    if (error != ES_OK) return error;
    while (overflowCount>TMR0_u32DelayCountSync);
    TCCR0 = 0;
    ClrBit(TIMSK, 0);
    return ES_OK;
}
ES_t TMR0_enuSetDuty(u8 TMR0_u8Duty){
    if(TMR0_u8Duty>100) return ES_OUT_OF_RANGE;
    u8 initialValue = TMR0_u8Duty*255.0/100.0;
    return TMR0_enuInit(TMR0_u8Clk_8, TMR0_u8FastPWM, TMR0_u8OC0NonInverting, 0, initialValue);
}

// TODO
static u32 TMR0_u32DelayCountAsync;
ES_t TMR0_enuDelaymsAsync(u32 TMR0_u8Time,void (*TMR0_pfuncIsrOC0)()){
    return ES_OK;
}
