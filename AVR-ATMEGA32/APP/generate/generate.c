#include "../../LIB/STD_TYPE.h"

#include "../../MCAL/ADC/ADC_INTERFACE.h"

// uses ADC to generate random 32-bit number
u32 rand(){
    u32 x = 0;
    ADC_voidStartOneConversion();
    x = ADC_u8GetHighValuePolling();
    ADC_voidStartOneConversion();
    x |= (u32)ADC_u8GetHighValuePolling()<<8;
    ADC_voidStartOneConversion();
    x |= (u32)ADC_u8GetHighValuePolling()<<16;
    ADC_voidStartOneConversion();
    x |= (u32)ADC_u8GetHighValuePolling()<<24;
    return x;
}
