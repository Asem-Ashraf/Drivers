#include "../../LIB/STD_TYPE.h"
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

    // Setting baud rate
    Copy_u32BaudRate *= (1+Copy_u8DoubleSpeed);
    u16 Local_u16UBRR = (CPU_u32Freq/(16*Copy_u32BaudRate))-1;
    if(Local_u16UBRR>4095) return ES_OUT_OF_RANGE;
    UBRRH = (u8)(Local_u16UBRR>>8);
    UBRRL = (u8)(Local_u16UBRR&0xFF);

    // Settting Double Speed
    UCSRA |= (Copy_u8DoubleSpeed<<U2X);

    // Adjusting value of data bits
    if(Copy_u8DataBits==4){
        SetBit(UCSRB,UCSZ2);
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
    SetBit(UCSRB,TXEN);
}

void UART_voidTransmit(u8 Copy_u8Data){
    // wait until transmit buffer is empty
    while(GetBit(UCSRA,UDRE)==0);
    UDR = Copy_u8Data;
}

void UART_voidTransmit9bit(u16 Copy_u8Data){
    // wait until transmit buffer is empty
    while(GetBit(UCSRA,UDRE)==0);
    // Setting 9th bit
    UCSRB= (UCSRB&0xFE) | (GetBit(Copy_u8Data,8));
    UDR = (u8)Copy_u8Data;
}

void UART_voidEnableTransmitCompleteInterrupt(void){
    SetBit(UCSRB,TXCIE);
}

ES_t UART_enuSetTransmitCompleteCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvTransmitCompleteCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableTransmitCompleteInterrupt(void){
    ClrBit(UCSRB,TXCIE);
}

void UART_voidEnableTransmitRegisterEmptyInterrupt(void){
    SetBit(UCSRB,UDRIE);
}

ES_t UART_enuSetTransmitRegisterEmptyCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvTransmitRegisterEmptyCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableTransmitRegisterEmptyInterrupt(void){
    ClrBit(UCSRB,UDRIE);
}

void UART_voidDisableTransmitUnit(void){
    ClrBit(UCSRB,TXEN);
}


void UART_voidEnableReceiveUnit(void){
    SetBit(UCSRB,RXEN);
}

u8 UART_enuReceive(){
    // wait until receive buffer is full
    while(GetBit(UCSRA,RXC)==0);
    return UDR;
}

u16 UART_enuReceive9bit(){
    // wait until receive buffer is full
    while(GetBit(UCSRA,RXC)==0);
    return  UDR | (UCSRB&2)<<7;
}

void UART_voidEnableReceiveCompleteInterrupt(void){
    SetBit(UCSRB,RXCIE);
}

ES_t UART_enuSetReceiveCompleteCallBack(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    UART_pvReceiveCompleteCallBack = Copy_pvCallBack;
    return ES_OK;
}

void UART_voidDisableReceiveCompleteInterrupt(void){
    ClrBit(UCSRB,RXCIE);
}

void UART_voidDisableReceiveUnit(void){
    ClrBit(UCSRB,RXEN);
}


ES_t UART_enuTransmitString(u8 * Copy_pu8Data){
    if(Copy_pu8Data==NULL) return ES_NULL_POINTER;
    UART_voidEnableTransmitUnit();
    while(*Copy_pu8Data!='\0'){
        UART_voidTransmit(*Copy_pu8Data);
        Copy_pu8Data++;
    }
    return ES_OK;
}
