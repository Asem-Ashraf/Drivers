#ifndef DIO_INT_H_
#define DIO_INT_H_


// INCLUDES
#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"


// ARGUMENTS
#define DIO_u8PORTA 3
#define DIO_u8PORTB 2
#define DIO_u8PORTC 1
#define DIO_u8PORTD 0

#define DIO_u8DDRA 3
#define DIO_u8DDRB 2
#define DIO_u8DDRC 1
#define DIO_u8DDRD 0

#define DIO_u8PIN0 0
#define DIO_u8PIN1 1
#define DIO_u8PIN2 2
#define DIO_u8PIN3 3
#define DIO_u8PIN4 4
#define DIO_u8PIN5 5
#define DIO_u8PIN6 6
#define DIO_u8PIN7 7

#define DIO_u8INPUT  0
#define DIO_u8OUTPUT 1

#define DIO_u8LOW  0
#define DIO_u8HIGH 1
#define DIO_u8FLOAT 0
#define DIO_u8PULL_UP 1


// FUNCTIONS PROTOTYPES
ES_t DIO_enuInit                (void);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8Direction : DIO_u8INPUT, DIO_u8OUTPUT
ES_t DIO_enuSetPortDirection    (u8 Copy_u8PortID, u8 Copy_u8Direction);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8Value     : DIO_u8LOW, DIO_u8HIGH
ES_t DIO_enuSetPortValue        (u8 Copy_u8PortID, u8 Copy_u8Value);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_pu8Value    : pointer to u8 variable to store the value of the port
ES_t DIO_enuGetPortValue        (u8 Copy_u8PortID, u8 *Copy_pu8Value);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
ES_t DIO_enuTogglePortValue     (u8 Copy_u8PortID);



// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8PinID     : DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
// Copy_u8Direction : DIO_u8INPUT, DIO_u8OUTPUT
ES_t DIO_enuSetPinDirection     (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8PinID     : DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
// Copy_u8Value     : DIO_u8LOW, DIO_u8HIGH
ES_t DIO_enuSetPinValue         (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8PinID     : DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
// Copy_pu8Value    : pointer to u8 variable to store the value of the pin
ES_t DIO_enuGetPinValue         (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 *Copy_pu8Value);


// Copy_u8PortID    : DIO_u8PORTA, DIO_u8PORTB, DIO_u8PORTC, DIO_u8PORTD
// Copy_u8PinID     : DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3, DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
ES_t DIO_enuTogglePinValue      (u8 Copy_u8PortID, u8 Copy_u8PinID);

#endif /* DIO_INT_H_ */
