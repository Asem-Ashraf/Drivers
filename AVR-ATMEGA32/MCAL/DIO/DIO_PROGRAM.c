// INCLUDES
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "DIO_PRIVATE.h"
#include "DIO_CONFIG.h"


// FUNCTIONS IMPLEMENTATION
void DIO_voidInit(void){
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRA) = CONC(PORTA7_DIR,PORTA6_DIR,PORTA5_DIR,PORTA4_DIR,PORTA3_DIR,PORTA2_DIR,PORTA1_DIR,PORTA0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRB) = CONC(PORTB7_DIR,PORTB6_DIR,PORTB5_DIR,PORTB4_DIR,PORTB3_DIR,PORTB2_DIR,PORTB1_DIR,PORTB0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRC) = CONC(PORTC7_DIR,PORTC6_DIR,PORTC5_DIR,PORTC4_DIR,PORTC3_DIR,PORTC2_DIR,PORTC1_DIR,PORTC0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRD) = CONC(PORTD7_DIR,PORTD6_DIR,PORTD5_DIR,PORTD4_DIR,PORTD3_DIR,PORTD2_DIR,PORTD1_DIR,PORTD0_DIR);

    Value(DIO_u8PORTbaseaddress, DIO_u8PORTA) = CONC(PORTA7_VAL,PORTA6_VAL,PORTA5_VAL,PORTA4_VAL,PORTA3_VAL,PORTA2_VAL,PORTA1_VAL,PORTA0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTB) = CONC(PORTB7_VAL,PORTB6_VAL,PORTB5_VAL,PORTB4_VAL,PORTB3_VAL,PORTB2_VAL,PORTB1_VAL,PORTB0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTC) = CONC(PORTC7_VAL,PORTC6_VAL,PORTC5_VAL,PORTC4_VAL,PORTC3_VAL,PORTC2_VAL,PORTC1_VAL,PORTC0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTD) = CONC(PORTD7_VAL,PORTD6_VAL,PORTD5_VAL,PORTD4_VAL,PORTD3_VAL,PORTD2_VAL,PORTD1_VAL,PORTD0_VAL);
}

ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Direction){
    if(Copy_u8PortID > DIO_u8PORTA) return ES_OUT_OF_RANGE;
    Value(DIO_u8DDRbaseaddress, Copy_u8PortID) = Copy_u8Direction;
    return ES_OK;
}

ES_t DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Value){
    if(Copy_u8PortID > DIO_u8PORTA) return ES_OUT_OF_RANGE;
    Value(DIO_u8PORTbaseaddress, Copy_u8PortID) = Copy_u8Value;
    return ES_OK;
}

ES_t DIO_enuGetPortValue(u8 Copy_u8PortID, u8 *Copy_pu8Value){
    if(Copy_u8PortID > DIO_u8PORTA) return ES_OUT_OF_RANGE;
    if (Copy_pu8Value == NULL) return ES_NULL_POINTER;
    *Copy_pu8Value = Value(DIO_u8PINbaseaddress, Copy_u8PortID);
    return ES_OK;
}

ES_t DIO_enuTogglePortValue(u8 Copy_u8PortID){
    if(Copy_u8PortID > DIO_u8PORTA) return ES_OUT_OF_RANGE;
    Value(DIO_u8PORTbaseaddress, Copy_u8PortID) = ~Value(DIO_u8PORTbaseaddress, Copy_u8PortID);
    return ES_OK;
}

ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value){
    if((Copy_u8PortID > DIO_u8PORTA) || (Copy_u8PinID > DIO_u8PIN7) || (Copy_u8Value > OUTPUT)) return ES_OUT_OF_RANGE;
    if(Copy_u8Value == OUTPUT){
        SetBit(Value(DIO_u8DDRbaseaddress, Copy_u8PortID), Copy_u8PinID);
    }
    else{
        ClrBit(Value(DIO_u8DDRbaseaddress, Copy_u8PortID), Copy_u8PinID);
    }
    return ES_OK;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value){
    if((Copy_u8PortID > DIO_u8PORTA)|| (Copy_u8PinID  > DIO_u8PIN7) || (Copy_u8Value  > HIGH)) return ES_OUT_OF_RANGE;
    if(Copy_u8Value == HIGH){
        SetBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
    }
    else{
        ClrBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
    }
    return ES_OK;
}

ES_t DIO_enuGetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 *Copy_pu8Value){
    if((Copy_u8PortID > DIO_u8PORTA) || (Copy_u8PinID > DIO_u8PIN7)) return ES_OUT_OF_RANGE;
    if (Copy_pu8Value == NULL) return ES_NULL_POINTER;
    *Copy_pu8Value = GetBit(Value(DIO_u8PINbaseaddress, Copy_u8PortID), Copy_u8PinID);
    return ES_OK;
}

ES_t DIO_enuTogglePinValue(u8 Copy_u8PortID, u8 Copy_u8PinID){
    if((Copy_u8PortID > DIO_u8PORTA) || (Copy_u8PinID > DIO_u8PIN7)) return ES_OUT_OF_RANGE;
    TglBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
    return ES_OK;
}
