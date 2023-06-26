#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#include "SEVEN_SEG_PRIVATE.h"

extern u8 SEV_SEG_u8NUM;
extern SEV_SEG_t SEV_SEG_AstructConfig[];

#define DISPLAY_OFF        16
u8 static SEV_SEG_Au8Nums[]= {0x3F,0x06,0x5B,
                              0x4F,0x66,0x6D,
                              0x7D,0x07,0x7F,
                              0x6F,0x77,0x7C,
                              0x39,0x5E,0x79,
                              0x71,0x00};

/*  ============================ *\
   || FUNCTIONS' IMPLEMENTATION||
\*  ============================ */


ES_t SEV_SEG_enuDisplayNum(SEV_SEG_t *Copy_pstructSeg, u8 Copy_u8Number){
    u8 Local_u8ES;
    if(Copy_pstructSeg == NULL)
        return ES_NULL_POINTER;
    if (Copy_pstructSeg< SEV_SEG_AstructConfig ||
        Copy_pstructSeg> SEV_SEG_AstructConfig+sizeof(SEV_SEG_t)*(SEV_SEG_u8NUM-1))
        return ES_OUT_OF_RANGE;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegAPort,
                                    Copy_pstructSeg->SEG_u8SegAPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>0) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegBPort,
                                    Copy_pstructSeg->SEG_u8SegBPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>1) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegCPort,
                                    Copy_pstructSeg->SEG_u8SegCPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>2) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegDPort,
                                    Copy_pstructSeg->SEG_u8SegDPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>3) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegEPort,
                                    Copy_pstructSeg->SEG_u8SegEPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>4) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegFPort,
                                    Copy_pstructSeg->SEG_u8SegFPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>5) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    if(Local_u8ES != ES_OK) return Local_u8ES;
    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegGPort,
                                    Copy_pstructSeg->SEG_u8SegGPin,
                                    ((SEV_SEG_Au8Nums[Copy_u8Number]>>6) & 1)==Copy_pstructSeg->SEG_u8ComPolarity);
    Copy_pstructSeg->SEG_u8SegInitVal = Copy_u8Number;
    if(Local_u8ES != ES_OK) return Local_u8ES;
    return ES_OK;
}

ES_t SEV_SEG_enuDotOn(SEV_SEG_t *Copy_pstructSeg){
    u8 Local_u8ES;
    if(Copy_pstructSeg == NULL)
        return ES_NULL_POINTER;
    if (Copy_pstructSeg< SEV_SEG_AstructConfig ||
        Copy_pstructSeg> SEV_SEG_AstructConfig+sizeof(SEV_SEG_t)*(SEV_SEG_u8NUM-1))
        return ES_OUT_OF_RANGE;
    if(Copy_pstructSeg->SEG_u8SegDotPort == SEV_SEG_u8NotConnected)
        return ES_NOT_CONNECTED;

    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegDotPort,
                                    Copy_pstructSeg->SEG_u8SegDotPin,
                                    Copy_pstructSeg->SEG_u8ComPolarity);
    Copy_pstructSeg->SEG_u8SegDotInitVal = SEV_SEG_u8DOT_ON;
    return Local_u8ES;
}
ES_t SEV_SEG_enuDotOff(SEV_SEG_t *Copy_pstructSeg){
    u8 Local_u8ES;
    if(Copy_pstructSeg == NULL)
        return ES_NULL_POINTER;
    if (Copy_pstructSeg< SEV_SEG_AstructConfig ||
        Copy_pstructSeg> SEV_SEG_AstructConfig+sizeof(SEV_SEG_t)*(SEV_SEG_u8NUM-1))
        return ES_OUT_OF_RANGE;
    if(Copy_pstructSeg->SEG_u8SegDotPort == SEV_SEG_u8NotConnected)
        return ES_NOT_CONNECTED;

    Local_u8ES = DIO_enuSetPinValue(Copy_pstructSeg->SEG_u8SegDotPort,
                                    Copy_pstructSeg->SEG_u8SegDotPin,
                                    !Copy_pstructSeg->SEG_u8ComPolarity);
    Copy_pstructSeg->SEG_u8SegDotInitVal = SEV_SEG_u8DOT_OFF;
    return Local_u8ES;
}

ES_t SEV_SEG_enuInit(SEV_SEG_t *Copy_AstructSegs){
    u8 Local_u8ES;
    if(Copy_AstructSegs == NULL){
        return ES_NULL_POINTER;
    }
    if(SEV_SEG_u8NUM == 0){
        return ES_INVALID_CONFIG;
    }
    if (Copy_AstructSegs != SEV_SEG_AstructConfig) {
        return ES_INVALID_INPUT;
    }
    for(u8 i=0; i<SEV_SEG_u8NUM; i++){
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegAPort,
                               Copy_AstructSegs[i].SEG_u8SegAPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegBPort,
                               Copy_AstructSegs[i].SEG_u8SegBPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegCPort,
                               Copy_AstructSegs[i].SEG_u8SegCPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegDPort,
                               Copy_AstructSegs[i].SEG_u8SegDPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegEPort,
                               Copy_AstructSegs[i].SEG_u8SegEPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegFPort,
                               Copy_AstructSegs[i].SEG_u8SegFPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegGPort,
                               Copy_AstructSegs[i].SEG_u8SegGPin,
                               DIO_u8OUTPUT);
        if(Local_u8ES != ES_OK) return Local_u8ES;
        if(Copy_AstructSegs[i].SEG_u8SegDotPin != SEV_SEG_u8NotConnected){
            Local_u8ES= DIO_enuSetPinDirection(Copy_AstructSegs[i].SEG_u8SegDotPort,
                                               Copy_AstructSegs[i].SEG_u8SegDotPin,
                                               DIO_u8OUTPUT);
            if(Local_u8ES != ES_OK) return Local_u8ES;
            Local_u8ES = DIO_enuSetPinValue(Copy_AstructSegs[i].SEG_u8SegDotPort,
                                            Copy_AstructSegs[i].SEG_u8SegDotPin,
                                            Copy_AstructSegs[i].SEG_u8SegDotInitVal==Copy_AstructSegs[i].SEG_u8ComPolarity);
            if(Local_u8ES != ES_OK) return Local_u8ES;
        }
        // displaying the initial values
        Local_u8ES = SEV_SEG_enuDisplayNum(&Copy_AstructSegs[i], Copy_AstructSegs[i].SEG_u8SegInitVal);
        if(Local_u8ES != ES_OK) return Local_u8ES;
    }
    return ES_OK;
}

ES_t SEV_SEG_enuDisplayOn(SEV_SEG_t *Copy_pstructSeg){
    u8 Local_u8ES;
    if(Copy_pstructSeg->SEG_u8SegDotInitVal == SEV_SEG_u8DOT_ON) {
        Local_u8ES=SEV_SEG_enuDotOn(Copy_pstructSeg);
        if(Local_u8ES != ES_OK) return Local_u8ES;
    }
    Local_u8ES= SEV_SEG_enuDisplayNum(Copy_pstructSeg, Copy_pstructSeg->SEG_u8SegInitVal);
    return Local_u8ES;
}

ES_t SEV_SEG_enuDisplayOff(SEV_SEG_t *Copy_pstructSeg){
    u8 Local_u8ES,Local_u8NumReserve;
    Local_u8NumReserve= Copy_pstructSeg->SEG_u8SegInitVal;
    Local_u8ES = SEV_SEG_enuDisplayNum(Copy_pstructSeg, DISPLAY_OFF);
    Copy_pstructSeg->SEG_u8SegInitVal =Local_u8NumReserve ;
    if(Copy_pstructSeg->SEG_u8SegDotPin != SEV_SEG_u8NotConnected){
        Local_u8NumReserve = Copy_pstructSeg->SEG_u8SegDotInitVal;
        Local_u8ES = SEV_SEG_enuDotOff(Copy_pstructSeg);
        Copy_pstructSeg->SEG_u8SegDotInitVal = Local_u8NumReserve;
        if(Local_u8ES != ES_OK) return Local_u8ES;
    }
    return Local_u8ES;
}

ES_t SEV_SEG_enuIncrementNum(SEV_SEG_t *Copy_pstructSeg){
    return SEV_SEG_enuDisplayNum(Copy_pstructSeg, (Copy_pstructSeg->SEG_u8SegInitVal+1)%16);
}

ES_t SEV_SEG_enuDecrementNum(SEV_SEG_t *Copy_pstructSeg){
    return SEV_SEG_enuDisplayNum(Copy_pstructSeg, (Copy_pstructSeg->SEG_u8SegInitVal-1)%16);
}


