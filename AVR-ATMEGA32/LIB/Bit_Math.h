#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SetBit(Reg, Bit) (Reg|=(1<<Bit))
#define ClearBit(Reg, Bit) (Reg&=~(1<<Bit))
#define ToggleBit(Reg, Bit) (Reg^=(1<<Bit))
#define GetBit(Reg, Bit) (((Reg>>Bit)&1))

#endif /* BIT_MATH_H_ */
