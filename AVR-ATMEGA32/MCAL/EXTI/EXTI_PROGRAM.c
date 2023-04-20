#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../LIB/Bit_Math.h"

#define int0           0
#define int1           1
#define int2           2

#define MCUCR          (*(u8*)0x55)
#define ISC00          0
#define ISC01          1
#define ISC10          2
#define ISC11          3

#define MCUCSR         (*(u8*)0x54)
#define ISC2           6

#define GICR           (*(u8*)0x5b)
#define INT1           7
#define INT0           6
#define INT2           5

#define LEVEL_LOW      0b11111100
#define LEVEL_CHANGE   0b11111101
#define FALLING_EDGE   0b11111110
#define RISING_EDGE    0b11111111


static void (*EXTI_AFptrCallback[3])(void)={NULL,NULL,NULL};


ES_t EXTI_enuInitInterrupt(u8 EXTI_u8InterruptID, void (*EXTI_FptrCallback)(void)){
    if (EXTI_u8InterruptID>2) { return ES_OUT_OF_RANGE; }
    if (EXTI_FptrCallback==NULL) { return ES_NULL_POINTER; }
    EXTI_AFptrCallback[EXTI_u8InterruptID]=EXTI_FptrCallback;
    return ES_OK;
}
ES_t EXTI_enuSetSenseControl(u8 EXTI_u8InterruptID, u8 EXTI_u8SenseControl){
    if (EXTI_u8InterruptID>2) { return ES_OUT_OF_RANGE; }
    if (EXTI_u8SenseControl<0b11111100) { return ES_OUT_OF_RANGE; }
    switch (EXTI_u8InterruptID) {
        case int0:
            MCUCR&=EXTI_u8SenseControl;
            return ES_OK;
        case int1:
            MCUCR&=((EXTI_u8SenseControl<<ISC10)&0xff);
            return ES_OK;
        case int2:
            MCUCSR&=((EXTI_u8SenseControl<<ISC2)&0xff);
            return ES_OK;
        default: return ES_OUT_OF_RANGE;
    }
}
ES_t EXTI_enuEnableInterrupt(u8 EXTI_u8InterruptID){
    if (EXTI_u8InterruptID>2) { return ES_OUT_OF_RANGE; }
    switch (EXTI_u8InterruptID) {
        case int0:
            SetBit(GICR,INT0);
            return ES_OK;
        case int1:
            SetBit(GICR,INT1);
            return ES_OK;
        case int2:
            SetBit(GICR,INT2);
            return ES_OK;
        default: return ES_OUT_OF_RANGE;
    }
}
ES_t EXTI_enuDisableInterrupt(u8 EXTI_u8InterruptID){
    if (EXTI_u8InterruptID>2) { return ES_OUT_OF_RANGE; }
    switch (EXTI_u8InterruptID) {
        case int0:
            ClrBit(GICR,INT0);
            return ES_OK;
        case int1:
            ClrBit(GICR,INT1);
            return ES_OK;
        case int2:
            ClrBit(GICR,INT2);
            return ES_OK;
        default: return ES_OUT_OF_RANGE;
    }
}


void __vector_0(void) __attribute__((signal));
void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));

void __vector_0(void){
    if (EXTI_AFptrCallback[int0] != NULL) {
        EXTI_AFptrCallback[int0]();
    }
}
void __vector_1(void){
    if (EXTI_AFptrCallback[int1] != NULL) {
        EXTI_AFptrCallback[int1]();
    }
}
void __vector_2(void){
    if (EXTI_AFptrCallback[int2] != NULL) {
        EXTI_AFptrCallback[int2]();
    }
}
