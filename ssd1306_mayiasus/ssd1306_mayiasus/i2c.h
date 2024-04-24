/*
 * i2c.h
 *
 * Created: 4/1/2024 5:27:08 PM
 *  Author: jlb
 */ 


#ifndef I2C_H_
#define I2C_H_
  #include <avr/io.h>

  #define TWI_TWAR            TWAR // TWI (Slave) Address Register
  #define TWI_TWBR            TWBR // TWI Bit Rate Register
  #define TWI_TWDR            TWDR // TWI Data Register
  #define TWI_TWCR            TWCR // TWI Control Register
  #define TWI_TWSR            TWSR // TWI Status Register

  // Success
  #ifndef SUCCESS
  #define SUCCESS             0
  #endif
  // Error
  #ifndef ERROR
  #define ERROR               1
  #endif

  // -------------------------------------------------------------------------------------
  //
  //        M A S T E R   M O D E
  //
  // -------------------------------------------------------------------------------------
  // Master Mode - Transmitter / Receiver
  #define TWI_START_ACK         0x08  // A START condition has been transmitted
  #define TWI_REP_START_ACK     0x10  // A repeated START condition has been transmitted
  #define TWI_FLAG_ARB_LOST     0x38  // Arbitration lost in SLA+W or NOT ACK bit
  // Master Transmitter Mode
  #define TWI_MT_SLAW_ACK       0x18  // SLA+W has been transmitted; ACK has been received
  #define TWI_MT_SLAW_NACK      0x20  // SLA+W has been transmitted; NOT ACK has been received
  #define TWI_MT_DATA_ACK       0x28  // Data byte has been transmitted; ACK has been received
  #define TWI_MT_DATA_NACK      0x30  // Data byte has been transmitted; NOT ACK has been received
  // Master Receiver Mode
  #define TWI_MR_SLAR_ACK       0x40  // SLA+R has been transmitted; ACK has been received
  #define TWI_MR_SLAR_NACK      0x48  // SLA+R has been transmitted; NOT ACK has been received
  #define TWI_MR_DATA_ACK       0x50  // Data byte has been received; ACK has been received
  #define TWI_MR_DATA_NACK      0x58  // Data byte has been received; NOT ACK has been received
  
  // -------------------------------------------------------------------------------------
  //
  //         S L A V E   M O D E
  //
  // -------------------------------------------------------------------------------------
  // Slave Receiver Mode
  #define TWI_SR_SLAW_ACK       0x60  // Own Slave address has been received; ACK returned
  #define TWI_SR_ALMOA_ACK      0x68  // Arbitration Lost in SLA+R/W as Master; Own Slave address has been received; ACK returned
  #define TWI_SR_GCALL_ACK      0x70  // General call address has been received; ACK returned
  #define TWI_SR_ALMGA_ACK      0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK returned
  #define TWI_SR_OA_DATA_ACK    0x80  // Previously addressed with own SLA+W; data has been received; ACK returned
  #define TWI_SR_OA_DATA_NACK   0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK returned
  #define TWI_SR_GC_DATA_ACK    0x90  // Previously addressed with general call; data has been received; ACK returned
  #define TWI_SR_GC_DATA_NACK   0x98  // Previously addressed with general call; data has been received; NOT ACK returned
  #define TWI_SR_STOP_RSTART    0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave
  // Slave Transmitter Mode
  #define TWI_ST_OA_ACK         0xA8  // Own SLA+R has been received; ACK has been returned
  #define TWI_ST_ALMOA_ACK      0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been received
  #define TWI_ST_DATA_ACK       0xB8  // Data byte in TWDR has been transmitted; ACK has been received
  #define TWI_ST_DATA_NACK      0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
  #define TWI_ST_DATA_LOST_ACK  0xC8  // Last data byte in TWDR has been transmitted (TWEA = '0'); ACK has been received

  // TWI CLK frequency
  // -------------------------------------------------------------------------------------
  //  @param TWBR
  //  @param Prescaler
  //    TWPS1 TWPS0  - PRESCALER
  //      0     0    -     1
  //      0     1    -     4
  //      1     0    -    16
  //      1     1    -    64
  #define TWI_FREQ(BIT_RATE, PRESCALER) { TWI_TWBR = BIT_RATE; TWI_TWSR |= (TWI_TWSR & 0x03) | PRESCALER; }

  // TWI start condition
  // (1 <<  TWEN) - TWI Enable
  // (1 << TWINT) - TWI Interrupt Flag - must be cleared by set
  // (1 << TWSTA) - TWI Start
  #define TWI_START()                   { TWI_TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA); }

  // TWI stop condition
  // (1 <<  TWEN) - TWI Enable
  // (1 << TWINT) - TWI Interrupt Flag - must be cleared by set
  // (1 << TWSTO) - TWI Stop
  #define TWI_STOP()                    { TWI_TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO); }

  // TWI enable
  // (1 <<  TWEN) - TWI Enable
  // (1 << TWINT) - TWI Interrupt Flag - must be cleared by set
  #define TWI_ENABLE()                  { TWI_TWCR = (1 << TWEN) | (1 << TWINT); }

  // TWI test if TWINT Flag is set
  #define TWI_WAIT_TILL_TWINT_IS_SET()  { while (!(TWI_TWCR & (1 << TWINT))); }

  // TWI status mask
  #define TWI_STATUS                    ( TWI_TWSR & 0xF8 )
  
  void TWI_Init (void);
  char TWI_MT_Start (void);
  char TWI_MT_Send_SLAW (char);
  char TWI_MT_Send_Data (char);
  char TWI_MR_Send_SLAR (char);
  void TWI_Stop (void);
  
#endif /* I2C_H_ */