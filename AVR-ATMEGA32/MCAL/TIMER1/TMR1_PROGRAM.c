#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/CPU_FREQ.h"

#include "TMR1_PRIVATE.h"

ES_t TMR1_enuInit(u8 Copy_u8clkSource,
                  u8 Copy_u8mode,
                  u8 Copy_u8OC1APinConfig,
                  u8 Copy_u8OC1BPinConfig,
                  u16 Copy_u16Preload,
                  u16 Copy_u16ICValue,
                  u16 Copy_u16OCAValue,
                  u16 Copy_u16OCBValue){

}


void TMR1_SetPreload(u16 Copy_u16Preload){

}


void TMR1_SetOutputCompareValue(u16 Copy_u16OCValue){

}


void TMR1_EnableOverflowInterrupt(){

}
ES_t TMR1_enuSetOverflowCallback(void (*Copy_pfuncIsrOverflow)()){

}
void TMR1_DisableOverflowInterrupt(){

}


void TMR1_EnableCompareMatchAInterrupt(){

}
ES_t TMR1_enuSetCompareMatchACallback(void (*Copy_pfuncIsrCTC)()){

}
void TMR1_DisableCompareMatchAInterrupt(){

}


void TMR1_EnableCompareMatchBInterrupt(){

}
ES_t TMR1_enuSetCompareMatchBCallback(void (*Copy_pfuncIsrCTC)()){

}
void TMR1_DisableCompareMatchBInterrupt(){

}


void TMR1_EnableCaptureInterrupt(){

}
ES_t TMR1_enuSetCaptureCallback(void (*Copy_pfuncIsrIC)()){

}
void TMR1_DisableCaptureInterrupt(){

}


void TMR1_Stop(){

}



// FEATURES

ES_t TMR1_enuBusyWaitms(u32 Copy_u32Timems){

}

ES_t TMR1_enuDelayedExecutionContiniuousms(u32 Copy_u32Timems,void (*Copy_pfuncIsr)()){

}

ES_t TMR1_enuSetDutyandFrequency(u8 Copy_u8Duty,f32 Copy_f32Frequency){

}
