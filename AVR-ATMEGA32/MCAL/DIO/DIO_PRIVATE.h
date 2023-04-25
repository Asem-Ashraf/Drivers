#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

// MACRO DEFINATIONS USED BY THE DRIVER FUNCTIONS
#define INPUT  0
#define OUTPUT 1

#define LOW  0
#define HIGH 1
#define FLOAT 0
#define PULL_UP 1

#define ADDRESS_OFFSET_MULTIPLIER 3

//                                  0x32
#define DIO_u8PORTbaseaddress ((u8*)'2')
#define DIO_u8PORTA 3
#define DIO_u8PORTB 2
#define DIO_u8PORTC 1
#define DIO_u8PORTD 0

//                                  0x31
#define DIO_u8DDRbaseaddress  ((u8*)'1')
#define DIO_u8DDRA 3
#define DIO_u8DDRB 2
#define DIO_u8DDRC 1
#define DIO_u8DDRD 0

//                                           0x30
#define DIO_u8PINbaseaddress  ((volatile u8*)'0')
#define DIO_u8PINA 3
#define DIO_u8PINB 2
#define DIO_u8PINC 1
#define DIO_u8PIND 0

#define DIO_u8PIN0 0
#define DIO_u8PIN1 1
#define DIO_u8PIN2 2
#define DIO_u8PIN3 3
#define DIO_u8PIN4 4
#define DIO_u8PIN5 5
#define DIO_u8PIN6 6
#define DIO_u8PIN7 7


#define Value(baseaddress,register) (*((baseaddress)+(ADDRESS_OFFSET_MULTIPLIER*(register))))

#define CONC_HELP(PIN7,PIN6,PIN5,PIN4,PIN3,PIN2,PIN1,PIN0) 0b##PIN7##PIN6##PIN5##PIN4##PIN3##PIN2##PIN1##PIN0
#define CONC(PIN7,PIN6,PIN5,PIN4,PIN3,PIN2,PIN1,PIN0)      CONC_HELP(PIN7,PIN6,PIN5,PIN4,PIN3,PIN2,PIN1,PIN0)



#endif /* DIO_PRIV_H_ */
