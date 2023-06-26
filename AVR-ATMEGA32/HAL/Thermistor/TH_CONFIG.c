#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#define TH_u8Positive 1
#define TH_u8Negative 0

typedef struct{
    u8 TH_u8Type;   // TH_u8Positive, TH_u8Negative
    u8 TH_u8PINID;  // DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3,
                    // DIO_u8PIN4, DIO_u8PIN5, DIO_u8PIN6, DIO_u8PIN7
}TH_t;

// Define the number of Themistor in the system [1-255].
#define TH_u8NUMTHEMISTORS 1

u8 TH_u8NUM = TH_u8NUMTHEMISTORS;
TH_t TH_AstuThemistors[TH_u8NUMTHEMISTORS]={
    {TH_u8Negative, DIO_u8PIN0}
};
