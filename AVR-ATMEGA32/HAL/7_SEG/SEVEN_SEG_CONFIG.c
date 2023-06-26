#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#define SEV_SEG_u8COM_ANODE    0x0
#define SEV_SEG_u8COM_CATHODE  0x1

#define SEV_SEG_u8DOT_OFF      0x0
#define SEV_SEG_u8DOT_ON       0x1

#define SEV_SEG_u8NotConnected 0xFF

typedef struct {
    u8 SEG_u8ComPolarity;
    u8 SEG_u8SegAPort;
    u8 SEG_u8SegAPin;
    u8 SEG_u8SegBPort;
    u8 SEG_u8SegBPin;
    u8 SEG_u8SegCPort;
    u8 SEG_u8SegCPin;
    u8 SEG_u8SegDPort;
    u8 SEG_u8SegDPin;
    u8 SEG_u8SegEPort;
    u8 SEG_u8SegEPin;
    u8 SEG_u8SegFPort;
    u8 SEG_u8SegFPin;
    u8 SEG_u8SegGPort;
    u8 SEG_u8SegGPin;
    u8 SEG_u8SegDotPort;
    u8 SEG_u8SegDotPin;
    u8 SEG_u8SegInitVal;
    u8 SEG_u8SegDotInitVal;
}SEV_SEG_t;

#define SEV_SEG_NUM 2

u8 SEV_SEG_u8NUM = SEV_SEG_NUM;
SEV_SEG_t SEV_SEG_AstructConfig[SEV_SEG_NUM] = {
    {SEV_SEG_u8COM_ANODE,
     DIO_u8PORTC,DIO_u8PIN0,
     DIO_u8PORTC,DIO_u8PIN1,
     DIO_u8PORTC,DIO_u8PIN2,
     DIO_u8PORTC,DIO_u8PIN3,
     DIO_u8PORTC,DIO_u8PIN4,
     DIO_u8PORTC,DIO_u8PIN5,
     DIO_u8PORTC,DIO_u8PIN6,
     DIO_u8PORTC,DIO_u8PIN7,
     0xf,SEV_SEG_u8DOT_ON
    },
    {SEV_SEG_u8COM_CATHODE,
     DIO_u8PORTD,DIO_u8PIN0,
     DIO_u8PORTD,DIO_u8PIN1,
     DIO_u8PORTD,DIO_u8PIN2,
     DIO_u8PORTD,DIO_u8PIN3,
     DIO_u8PORTD,DIO_u8PIN4,
     DIO_u8PORTD,DIO_u8PIN5,
     DIO_u8PORTD,DIO_u8PIN6,
     DIO_u8PORTD,DIO_u8PIN7,
     0xf,SEV_SEG_u8DOT_ON
    }
};
