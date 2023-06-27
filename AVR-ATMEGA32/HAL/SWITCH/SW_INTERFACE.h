#ifndef SW_INIT_H
#define SW_INIT_H
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

typedef struct{
    u8 SW_u8Mode;   // DIO_u8pull_up or DIO_u8FLOAT
    u8 SW_u8PORTID; // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 SW_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}SW_t;


// Copy_pstructSwitches : pointer to the switches struct
ES_t SW_enuInit      (SW_t *SW_AstructSwitches);


// Copy_pstructSwitch   : pointer to the switch struct
// Copy_pu8State        : pointer to u8 variable to store the state of the switch
ES_t SW_enuGetState  (SW_t* Copy_pstructSwitch, u8 *pu8State);


// Copy_pstructSwitch   : pointer to the switch struct
// Copy_u8Mode          : DIO_u8FLOAT, DIO_u8PULL_UP
ES_t SW_enuSetMode   (SW_t* Copy_pstructSwitch, u8 Copy_u8Mode);


#endif // SW_INIT_H
