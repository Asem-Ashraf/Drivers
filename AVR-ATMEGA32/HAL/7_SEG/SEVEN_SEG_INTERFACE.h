#ifndef SEV_SEG_INTERFACE_H_
#define SEV_SEG_INTERFACE_H_
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

typedef struct {
    u8 SEG_u8ComPolarity;
    u8 SEG_u8SegAPort;
    u8 SEG_u8SegAPin;
    u8 SEG_u8SegBPort;
    u8 SEG_u8SegBPin;
    u8 SEG_u8SegCPort;
    u8 SEG_u8SegCPin;
    u8 SEG_u8SegDPort;
    u8 SEG_u8SegDPin;
    u8 SEG_u8SegEPort;
    u8 SEG_u8SegEPin;
    u8 SEG_u8SegFPort;
    u8 SEG_u8SegFPin;
    u8 SEG_u8SegGPort;
    u8 SEG_u8SegGPin;
    u8 SEG_u8SegDotPort;
    u8 SEG_u8SegDotPin;
    u8 SEG_u8SegInitVal;
    u8 SEG_u8SegDotInitVal;
}SEV_SEG_t;


ES_t SEV_SEG_enuInit(SEV_SEG_t *Copy_AstructSegs);

ES_t SEV_SEG_enuDisplayNum(SEV_SEG_t *Copy_pstructSeg, u8 Copy_u8Number);

ES_t SEV_SEG_enuDisplayOn(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDisplayOff(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuIncrementNum(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDecrementNum(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDotOn(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDotOff(SEV_SEG_t *Copy_pstructSeg);


#endif /* SEV_SEG_INTERFACE_H_ */
