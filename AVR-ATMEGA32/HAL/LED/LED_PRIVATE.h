#ifndef LED_PRIV_H_
#define LED_PRIV_H_

#define LED_u8SINK         1
#define LED_u8SOURCE       0

#define LED_u8ON           1
#define LED_u8OFF          0

typedef struct {
    u8 LED_u8PORTID;        // DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
    u8 LED_u8PINID;         // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
    u8 LED_u8Connection;    // LED_u8SINK, LED_u8SOURCE
    u8 LED_u8InitState;     // LED_u8ON, LED_u8OFF
}LED_t;
#endif /* LED_PRIV_H_ */
