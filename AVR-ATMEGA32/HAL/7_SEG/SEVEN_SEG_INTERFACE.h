#ifndef SEV_SEG_INTERFACE_H_
#define SEV_SEG_INTERFACE_H_

/*  ======================== *\
   || FUNCTIONS' PROTOTYPE ||
\*  ======================== */

ES_t SEV_SEG_enuInit(SEV_SEG_t *Copy_AstructSegs);

ES_t SEV_SEG_enuDisplayNum(SEV_SEG_t *Copy_pstructSeg, u8 Copy_u8Number);

ES_t SEV_SEG_enuDisplayOn(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDisplayOff(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuIncrementNum(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDecrementNum(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDotOn(SEV_SEG_t *Copy_pstructSeg);

ES_t SEV_SEG_enuDotOff(SEV_SEG_t *Copy_pstructSeg);


#endif /* SEV_SEG_INTERFACE_H_ */
