#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SetBit(Reg, Bit) ((Reg)|=(1<<Bit))
#define ClrBit(Reg, Bit) ((Reg)&=~(1<<Bit))
#define TglBit(Reg, Bit) ((Reg)^=(1<<Bit))
#define GetBit(Reg, Bit) ((((Reg)>>Bit)&1))

#endif /* BIT_MATH_H_ */
