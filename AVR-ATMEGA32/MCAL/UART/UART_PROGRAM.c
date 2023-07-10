#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/CPU_FREQ.h"

#include "UART_PRIVATE.h"

// callback functions
static void (*UART_pvTransmitCompleteCallBack)(void) = NULL;
static void (*UART_pvTransmitRegisterEmptyCallBack)(void) = NULL;
static void (*UART_pvReceiveCompleteCallBack)(void) = NULL;

// ISR
void __vector_13(void) __attribute__((signal,used));
void __vector_13(void){
    if(UART_pvTransmitCompleteCallBack!=NULL)
        UART_pvTransmitCompleteCallBack();
}

void __vector_15(void) __attribute__((signal,used));
void __vector_15(void){
    if(UART_pvTransmitRegisterEmptyCallBack!=NULL)
        UART_pvTransmitRegisterEmptyCallBack();
}

void __vector_14(void) __attribute__((signal,used));
void __vector_14(void){
    if(UART_pvReceiveCompleteCallBack!=NULL)
        UART_pvReceiveCompleteCallBack();
}

ES_t UART_enuInit(u32 Copy_u32BaudRate, u8 Copy_u8DataBits, u8 Copy_u8Parity,
                  u8 Copy_u8StopBits, u8 Copy_u8DoubleSpeed){
    if(Copy_u8Parity>2||
       Copy_u8StopBits>1||
       Copy_u8DataBits>4||
       Copy_u8DoubleSpeed>1)
        return ES_OUT_OF_RANGE;

    // setting baud rate
    Copy_u32BaudRate *= 2*Copy_u8DoubleSpeed;
    u16 Local_u16UBRR = (CPU_FREQ/(16*Copy_u32BaudRate))-1;
    if(Local_u16UBRR>4095) Local_u16UBRR = 4095;
    UBRRH = (u8)(Local_u16UBRR>>8);
    UBRRL = (u8)(Local_u16UBRR&0xFF);

    // settting Double Speed
    UCSRA |= (Copy_u8DoubleSpeed<<U2X);

    // Adjusting value of data bits
    if(Copy_u8DataBits==4){
        SET_BIT(UCSRB,UCSZ2);
        Copy_u8DataBits = 3;
    }

    // Adjusting value of parity
    if(Copy_u8Parity>0) Copy_u8DataBits++;

    // Setting data bits, parity and stop bits
    UCSRC = (1<<URSEL) | (Copy_u8Parity<<UPM0) | (Copy_u8StopBits<<USBS) |
            ((Copy_u8DataBits&3)<<UCSZ0);

    return ES_OK;
}


void UART_voidEnableTransmitUnit(void){
    SET_BIT(UCSRB,TXEN);
}

void UART_enuTransmit(u8 Copy_u8Data){
    // wait until transmit buffer is empty
    while(GET_BIT(UCSRA,UDRE)==0);
    UDR = Copy_u8Data;
}

void UART_enuTransmit9bit(u16 Copy_u8Data){
    // wait until transmit buffer is empty
    while(GET_BIT(UCSRA,UDRE)==0);
    // setting 9th bit
    USARTB = (USARTB&0xFE) | (GET_BIT(Copy_u8Data,8));
    UDR = (u8)Copy_u8Data;
}

void UART_voidEnableTransmitCompleteInterrupt(void){
    SET_BIT(UCSRB,TXCIE);
}

ES_t UART_voidSetTransmitCompleteCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvTransmitCompleteCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableTransmitCompleteInterrupt(void){
    CLR_BIT(UCSRB,TXCIE);
}

void UART_voidEnableTransmitRegisterEmptyInterrupt(void){
    SET_BIT(UCSRB,UDRIE);
}

ES_t UART_voidSetTransmitRegisterEmptyCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvTransmitRegisterEmptyCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableTransmitRegisterEmptyInterrupt(void){
    CLR_BIT(UCSRB,UDRIE);
}

void UART_voidDisableTransmitUnit(void){
    CLR_BIT(UCSRB,TXEN);
}


void UART_voidEnableReceiveUnit(void){
    SET_BIT(UCSRB,RXEN);
}

ES_t UART_enuReceive(u8 * Copy_pu8Data){
    if(Copy_pu8Data==NULL) return ES_NULL_POINTER;
    // wait until receive buffer is full
    while(GET_BIT(UCSRA,RXC)==0);
    *Copy_pu8Data = UDR;
    return ES_OK;
}

ES_t UART_enuReceive9bit(u16 * Copy_pu8Data){
    if(Copy_pu8Data==NULL) return ES_NULL_POINTER;
    // wait until receive buffer is full
    while(GET_BIT(UCSRA,RXC)==0);
    *Copy_pu8Data = UDR;
    // getting 9th bit
    *Copy_pu8Data |= (UCSRB&2)<<7;
    return ES_OK;
}

void UART_voidEnableReceiveCompleteInterrupt(void){
    SET_BIT(UCSRB,RXCIE);
}

ES_t UART_voidSetReceiveCompleteCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvReceiveCompleteCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableReceiveCompleteInterrupt(void){
    CLR_BIT(UCSRB,RXCIE);
}

void UART_voidDisableReceiveUnit(void){
    CLR_BIT(UCSRB,RXEN);
}


ES_t UART_enuTransmitString(u8 * Copy_pu8Data){
    if(Copy_pu8Data==NULL) return ES_NULL_POINTER;
    UART_voidEnableTransmitUnit();
    while(*Copy_pu8Data!='\0'){
        UART_enuTransmit(*Copy_pu8Data);
        Copy_pu8Data++;
    }
    return ES_OK;
}
