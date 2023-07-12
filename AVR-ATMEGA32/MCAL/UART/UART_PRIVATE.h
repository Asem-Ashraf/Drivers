#ifndef UART_PRIVATE_H__
#define UART_PRIVATE_H__

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"


#define UART_5BIT_DATA          0
#define UART_6BIT_DATA          1
#define UART_7BIT_DATA          2
#define UART_8BIT_DATA          3
#define UART_9BIT_DATA          4

#define UART_PARITY_DISABLED    0
#define UART_PARITY_EVEN        1
#define UART_PARITY_ODD         2

#define UART_1STOP_BIT          0
#define UART_2STOP_BIT          1

#define UART_DOUBLE_SPEED_OFF   0
#define UART_DOUBLE_SPEED_ON    1


#define UDR   *((volatile u8 *) 0x2C)

#define UCSRA *((volatile u8 *) 0x2B)
#define RXC  7
#define TXC  6
#define UDRE 5
#define FE   4
#define DOR  3
#define PE   2
#define U2X  1
#define MPCM 0

#define UCSRB *((volatile u8 *) 0x2A)
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0

#define UCSRC *((volatile u8 *) 0x40)
#define URSEL 7
#define UMSEL 6
#define UPM1  5
#define UPM0  4
#define USBS  3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0

#define UBRRH *((volatile u8 *) 0x40)
#define UBRRL *((volatile u8 *) 0x29)

#define UBRRH_URSEL 7


#endif
