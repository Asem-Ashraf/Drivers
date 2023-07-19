#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H


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

#define LEVEL_LOW      0b00000000
#define LEVEL_CHANGE   0b00000001
#define FALLING_EDGE   0b00000010
#define RISING_EDGE    0b00000011


#endif
