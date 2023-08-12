#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_PRIVATE.h"

static void (*EXTI_AFptrCallback[3])(void)={NULL,NULL,NULL};
void __vector_1(void) __attribute__((signal));
void __vector_1(void){if(EXTI_AFptrCallback[int0]!= NULL)EXTI_AFptrCallback[int0]();}
void __vector_2(void) __attribute__((signal));
void __vector_2(void){if(EXTI_AFptrCallback[int1]!= NULL)EXTI_AFptrCallback[int1]();}
void __vector_3(void) __attribute__((signal));
void __vector_3(void){if(EXTI_AFptrCallback[int2]!= NULL)EXTI_AFptrCallback[int2]();}

ES_t EXTI_enuInitInterrupt(u8 EXTI_u8InterruptID, void (*EXTI_FptrCallback)(void)){
    if (EXTI_u8InterruptID>2)           return ES_OUT_OF_RANGE;
    if (EXTI_FptrCallback==NULL)        return ES_NULL_POINTER;
    EXTI_AFptrCallback[EXTI_u8InterruptID]=EXTI_FptrCallback;
    return ES_OK;
}
ES_t EXTI_enuSetSenseControl(u8 EXTI_u8InterruptID, u8 EXTI_u8SenseControl){
    if (EXTI_u8SenseControl>RISING_EDGE) return ES_OUT_OF_RANGE;
    switch (EXTI_u8InterruptID) {
        case int0: MCUCR = (MCUCR&0xFC)|EXTI_u8SenseControl; return ES_OK;
        case int1: MCUCR = (MCUCR&0xF3)|EXTI_u8SenseControl<<ISC10; return ES_OK;
        case int2: MCUCSR=(MCUCSR&0xBF)|((EXTI_u8SenseControl&0x01)<<ISC2); return ES_OK;
        default: return ES_OUT_OF_RANGE;
    }
}
ES_t EXTI_enuEnableInterrupt(u8 EXTI_u8InterruptID){
    switch (EXTI_u8InterruptID) {
        case int0: SetBit(GICR,INT0); return ES_OK;
        case int1: SetBit(GICR,INT1); return ES_OK;
        case int2: SetBit(GICR,INT2); return ES_OK;
        default:                      return ES_OUT_OF_RANGE;
    }
}
ES_t EXTI_enuDisableInterrupt(u8 EXTI_u8InterruptID){
    switch (EXTI_u8InterruptID) {
        case int0: ClrBit(GICR,INT0); return ES_OK;
        case int1: ClrBit(GICR,INT1); return ES_OK;
        case int2: ClrBit(GICR,INT2); return ES_OK;
        default:                      return ES_OUT_OF_RANGE;
    }
}
