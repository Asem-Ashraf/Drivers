#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/CPU_FREQ.h"

#include "SPI_PRIVATE.h"

static void (*SPI_pvCallBack)(void) = NULL;

void __vector_12(void) __attribute__((signal,used));
void __vector_12(void){
    if(SPI_pvCallBack!=NULL){
        SPI_pvCallBack();
    }
}



ES_t SPI_enuMasterInit(u8 Copy_u8SBFirst, u8 Copy_u8DoubleSpeed, 
                       u8 Copy_u8ClkRate, u8 Copy_u8ClkPol, u8 Copy_u8ClkPh, 
                       u8 Copy_u8Duplex){
    if(Copy_u8SBFirst>1|| Copy_u8DoubleSpeed>1|| Copy_u8ClkPol>1|| Copy_u8ClkPh>1||
       Copy_u8ClkRate>3|| Copy_u8Duplex>1)
        return ES_OUT_OF_RANGE;

    SPCR = (Copy_u8SBFirst)| (Copy_u8ClkRate)| (Copy_u8ClkPol)| (Copy_u8ClkPh)|
           (SPI_MASTER);
    SPSR = Copy_u8DoubleSpeed;
    ClrBit(DDRB, SS);
    DDRB |= (Copy_u8Duplex<<MOSI)|(1<<SCK);
    // PORTB pins are automatically configured based on the values of SPCR
    // see DIO pins alternative operation modes in the datasheet
    return ES_OK;
}

ES_t SPI_enuSlaveInit(u8 Copy_u8SBFirst, u8 Copy_u8ClkPol, u8 Copy_u8ClkPh, 
                      u8 Copy_u8Duplex){
    if(Copy_u8SBFirst>1|| Copy_u8ClkPol>1|| Copy_u8ClkPh>1)
        return ES_OUT_OF_RANGE;
    SPCR = (Copy_u8SBFirst)|(Copy_u8ClkPol)| (Copy_u8ClkPh);
    DDRB |= (Copy_u8Duplex<<MISO);
    // PORTB pins are automatically configured based on the values of SPCR
    // see DIO pins alternative operation modes in the datasheet
    return ES_OK;
}


void SPI_voidEnableTransferCompleteInterrupt(){
    SetBit(SPCR, SPIE);
}

ES_t SPI_enuSetTransferCompleteCallback(void (*Copy_pvCallBack)(void)){
    if(Copy_pvCallBack==NULL) return ES_NULL_POINTER;
    SPI_pvCallBack=Copy_pvCallBack;
    return ES_OK;
}

void SPI_voidDisableTransferCompleteInterrupt(){
    ClrBit(SPCR, SPIE);
}


void SPI_voidStart(void){
    // start sending any new data written to the SPDR based on the 
    // initialization values
    SetBit(SPCR, SPE);
}
void SPI_voidStop(void){
    // Shuts down the SPI communication without changing the initial settings.
    ClrBit(SPCR, SPE);
}

// can be used on master or slave
void SPI_voidSendByte(u8 Copy_u8Data){
    // Push the data onto the shift register clearing whatever transmition was
    // going on if any and start transmition of newly pushed data.
    SPDR = Copy_u8Data;
    while (!GetBit(SPSR, SPIF));
}

// can be used on master or slave
u8 SPI_enuReceiveByte(){
    // Clear the SPI interrupt flag and read last received value
    // if the flag is already 0 this means that there isn't any received data or
    // last received data is already read. The function will wait for new data.
    while (!GetBit(SPSR, SPIF));
    return SPDR;
}

// only works if the connection is full-duplex between the two MCUs
u8 SPI_enuSendReceiveByte(u8 Copy_u8SendData){
    // Push the data onto the shift register clearing whatever transmition was
    // going on if any and start transmition of newly pushed data.
    SPDR = Copy_u8SendData;

    // Clear the SPI interrupt flag and read last received value
    // if the flag is already 0 this means that there isn't any received data or
    // last received data is already read. The function will wait for new data.
    while (!GetBit(SPSR, SPIF));
    return SPDR;
}

