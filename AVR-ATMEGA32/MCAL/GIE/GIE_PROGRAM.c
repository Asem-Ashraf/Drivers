#include "../../LIB/ErrorStates.h"


ES_t GIE_enuEnable(void){
    // Enable Global Interrupt Instruction
    asm("SEI");
    return ES_OK;
}

ES_t GIE_enuDisable(void){
    // Disable Global Interrupt Instruction
    asm("CLI");
    return ES_OK;
}
