// INCLUDES
#include "../../LIB/stdTypes.h"
#include "../../LIB/ErrorStates.h"
#include "../../LIB/Bit_Math.h"
#include "DIO_priv.h"
#include "DIO_config.h"


// FUNCTIONS IMPLEMENTATION
ES_t DIO_enuInit(void){
    ES_t Local_enuErrorState = ES_NOK;
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRA) = CONC(PORTA7_DIR,PORTA6_DIR,PORTA5_DIR,PORTA4_DIR,PORTA3_DIR,PORTA2_DIR,PORTA1_DIR,PORTA0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRB) = CONC(PORTB7_DIR,PORTB6_DIR,PORTB5_DIR,PORTB4_DIR,PORTB3_DIR,PORTB2_DIR,PORTB1_DIR,PORTB0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRC) = CONC(PORTC7_DIR,PORTC6_DIR,PORTC5_DIR,PORTC4_DIR,PORTC3_DIR,PORTC2_DIR,PORTC1_DIR,PORTC0_DIR);
    Value(DIO_u8DDRbaseaddress, DIO_u8DDRD) = CONC(PORTD7_DIR,PORTD6_DIR,PORTD5_DIR,PORTD4_DIR,PORTD3_DIR,PORTD2_DIR,PORTD1_DIR,PORTD0_DIR);

    Value(DIO_u8PORTbaseaddress, DIO_u8PORTA) = CONC(PORTA7_VAL,PORTA6_VAL,PORTA5_VAL,PORTA4_VAL,PORTA3_VAL,PORTA2_VAL,PORTA1_VAL,PORTA0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTB) = CONC(PORTB7_VAL,PORTB6_VAL,PORTB5_VAL,PORTB4_VAL,PORTB3_VAL,PORTB2_VAL,PORTB1_VAL,PORTB0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTC) = CONC(PORTC7_VAL,PORTC6_VAL,PORTC5_VAL,PORTC4_VAL,PORTC3_VAL,PORTC2_VAL,PORTC1_VAL,PORTC0_VAL);
    Value(DIO_u8PORTbaseaddress, DIO_u8PORTD) = CONC(PORTD7_VAL,PORTD6_VAL,PORTD5_VAL,PORTD4_VAL,PORTD3_VAL,PORTD2_VAL,PORTD1_VAL,PORTD0_VAL);

    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}

ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Direction){
    ES_t Local_enuErrorState = ES_NOK;
    if(Copy_u8PortID <= DIO_u8PORTA){
        Value(DIO_u8DDRbaseaddress, Copy_u8PortID) = Copy_u8Direction;
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Value){
    ES_t Local_enuErrorState = ES_NOK;
    if(Copy_u8PortID <= DIO_u8PORTA){
        Value(DIO_u8PORTbaseaddress, Copy_u8PortID) = Copy_u8Value;
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuGetPortValue(u8 Copy_u8PortID, u8 *Copy_pu8Value){
    ES_t Local_enuErrorState = ES_NOK;
    if(Copy_u8PortID <= DIO_u8PORTA){
        if (Copy_pu8Value != NULL) {
            *Copy_pu8Value = Value(DIO_u8PINbaseaddress, Copy_u8PortID);
            Local_enuErrorState = ES_OK;
        }
        else{
            Local_enuErrorState = ES_NULL_POINTER;
        }
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuTogglePortValue(u8 Copy_u8PortID){
    ES_t Local_enuErrorState = ES_NOK;
    if(Copy_u8PortID <= DIO_u8PORTA){
        Value(DIO_u8PORTbaseaddress, Copy_u8PortID) = ~Value(DIO_u8PORTbaseaddress, Copy_u8PortID);
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value){
    ES_t Local_enuErrorState = ES_NOK;
    if((Copy_u8PortID <= DIO_u8PORTA) && (Copy_u8PinID <= DIO_u8PIN7) && (Copy_u8Value <= OUTPUT)){
        if(Copy_u8Value == OUTPUT){
            SetBit(Value(DIO_u8DDRbaseaddress, Copy_u8PortID), Copy_u8PinID);
        }
        else{
            ClrBit(Value(DIO_u8DDRbaseaddress, Copy_u8PortID), Copy_u8PinID);
        }
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value){
    ES_t Local_enuErrorState = ES_NOK;
    if((Copy_u8PortID <= DIO_u8PORTA) && (Copy_u8PinID <= DIO_u8PIN7) && (Copy_u8Value <= HIGH)){
        if(Copy_u8Value == HIGH){
            SetBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
        }
        else{
            ClrBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
        }
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}

ES_t DIO_enuGetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 *Copy_pu8Value){
    ES_t Local_enuErrorState = ES_NOK;
    if((Copy_u8PortID <= DIO_u8PORTA) && (Copy_u8PinID <= DIO_u8PIN7)){
        if (Copy_pu8Value != NULL) {
            *Copy_pu8Value = GetBit(Value(DIO_u8PINbaseaddress, Copy_u8PortID), Copy_u8PinID);
            Local_enuErrorState = ES_OK;
        }
        else{
            Local_enuErrorState = ES_NULL_POINTER;
        }
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

ES_t DIO_enuTogglePinValue(u8 Copy_u8PortID, u8 Copy_u8PinID){
    ES_t Local_enuErrorState = ES_NOK;
    if((Copy_u8PortID <= DIO_u8PORTA) && (Copy_u8PinID <= DIO_u8PIN7)){
        TglBit(Value(DIO_u8PORTbaseaddress, Copy_u8PortID), Copy_u8PinID);
        Local_enuErrorState = ES_OK;
    }
    else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}
