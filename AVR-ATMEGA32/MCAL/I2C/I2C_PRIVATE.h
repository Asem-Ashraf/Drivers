#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define I2C_WRITE	0
#define I2C_READ	1

#define GETTWBR(Bitrate) ((((CPU_u32Freq/1000)/(Bitrate*2))-8))


#define I2C_ACK_ENABLE    1
#define I2C_ACK_DISABLE   0


/* I2C Prescaler Bits */
#define I2C_PRESCALER_1				0x00
#define I2C_PRESCALER_4				0x01
#define I2C_PRESCALER_16			0x02
#define I2C_PRESCALER_64			0x03

#define I2C_WRITE_OPERATION           (0x00)
#define I2C_READ_OPERATION            (0x01)

// MASTER MODE

// start condition transmitted
#define I2C_MASTER_START_SENT                           (0x08)
// repeated start condition transmitted 
#define I2C_MASTER_REPEATED_START_SENT                  (0x10)


// Master transmit

// SLA+W transmitted, ACK received
#define I2C_MASTER_SLA_W_SENT_ACK_RECEIVED              (0x18)
// SLA+W transmitted, NACK received
#define I2C_MASTER_SLA_W_SENT_NACK_RECEIVED             (0x20)

// Data transmitted, ACK received
#define I2C_MASTER_DATA_SENT_ACK_RECEIVED               (0x28)
// Data transmitted, NACK received
#define I2C_MASTER_DATA_SENT_NACK_RECEIVED              (0x30)

// Master receive

// SLA+R transmitted, ACK received
#define I2C_MASTER_SLA_R_SENT_ACK_RECEIVED              (0x40)
// SLA+R transmitted, NACK received  
#define I2C_MASTER_SLA_R_SENT_NACK_RECEIVED             (0x48)

// Data received, ACK returned
#define I2C_MASTER_DATA_RECEIVED_ACK_SENT               (0x50)
// Data received, NACK returned
#define I2C_MASTER_DATA_RECEIVED_NACK_SENT              (0x58)



// master arbitration lost in SLA+W/R or data bytes

// Arbitration lost while transmitting or receiving operation or data
#define I2C_MASTER_ARB_LOST                             (0x38)
// Arbitration lost, own SLA+W received, ACK returned
#define I2C_MASTER_ARB_LOST_SLA_W_RECEIVED_ACK_SENT     (0x68)
// Arbitration lost, own SLA+R received, ACK returned
#define I2C_MASTER_ARB_LOST_SLA_R_RECEIVED_ACK_SENT     (0xB0)
// Arbitration lost, General call received, ACK returned
#define I2C_MASTER_ARB_LOST_GEN_CALL_RECEIVED_ACK_SENT  (0x78)




// SLAVE MODE

// Slave receive
// Own SLA+W received, ACK returned
#define I2C_SLAVE_SLA_W_RECEIVED_ACK_SENT               (0x60)
// General call received, ACK returned 
#define I2C_SLAVE_GEN_CALL_RECEIVED_ACK_SENT            (0x70)

// Previously addressed, data received, ACK returned
#define I2C_SLAVE_DATA_RECEIVED_ACK_SENT                (0x80)
// Previously addressed, data received, NACK returned
#define I2C_SLAVE_DATA_RECEIVED_NACK_SENT               (0x88)




// Slave transmit
// Own SLA+R received, ACK returned  
#define I2C_SLAVE_SLA_R_RECEIVED_ACK_SENT               (0xA8)

// Data transmitted, ACK received
#define I2C_SLAVE_DATA_SENT_ACK_RECEIVED                (0xB8)
// Data transmitted, NACK received
#define I2C_SLAVE_DATA_SENT_NACK_RECEIVED               (0xC0)
// Last data byte transmitted, ACK received
#define I2C_SLAVE_LAST_DATA_BYTE_SENT_ACK_RECEIVED      (0xC8)

// STOP or repeated START received while addressed as slave
#define I2C_SLAVE_STOP_RECEIVED                         (0xA0)


// general call
#define I2C_GENERAL_CALL_ACCEPT                         (0x00)
#define I2C_GENERAL_CALL_REJECT                         (0x01)


// Register
#define TWBR	*((volatile u8 *) 0x20)

#define TWSR	*((volatile u8 *) 0x21)

#define TWAR	*((volatile u8 *) 0x22)

#define TWDR	*((volatile u8 *) 0x23)

#define TWCR	*((volatile u8 *) 0x56)
#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWWC	3
#define TWEN	2
#define TWIE	0


#endif
