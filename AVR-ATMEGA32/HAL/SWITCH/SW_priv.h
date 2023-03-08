#ifndef SW_PRIV_H
#define SW_PRIV_H

// NON-ARGUMENT DEFINATIONS USED IN SW_prog.c

// define the switch(es) values in SW_config.c according to the following struct
typedef struct{
    u8 SW_u8Mode;   // DIO_u8pull_up or DIO_u8FLOAT
    u8 SW_u8PORTID; // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 SW_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}SW_t;




#endif // SW_PRIV_H
