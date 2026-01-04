// I2C_eeprom.c
#include "types.h"
#include "I2C.h"
#include "delay.h"
#include <LPC21xx.h>
#define  WP 11

void I2C_eeprom_bytewrite(u8 SlaveAddr, u8 wBuffAddr, u8 data)
{
    // issue start event
	  IOCLR0=1<<WP;
    I2C_start();
    //  SLAVE ADDR+ WRITE BIT
    I2C_write(SlaveAddr << 1);
    // WRITE BUDD ADDR
    //higher byte
    I2C_write((wBuffAddr>>8)&0xFF);
	 //lower byte
	  I2C_write(wBuffAddr&0xFF);
    // WITING DATA  
    I2C_write(data);
    // issue the stop
    I2C_stop();
    // write cycle delay
    delay_ms(9);
}
u8 I2C_eeprom_byteread(u8 SlaveAddr, u8 ReadBuffAddr)
{
	  u8 rdat;
    // issue start event
	  IOSET1=1<<WP;
    I2C_start();
    // SLAVE ADDR + WRITE BIT
    I2C_write(SlaveAddr << 1);                                                 
    // read buff addr
    //higher byte
    I2C_write((ReadBuffAddr>>8)&0xff);
	  //lower byte
	  I2C_write((ReadBuffAddr)&0xff);
    // issue restart event
    I2C_restart();
    // write slave addr + read bit
    I2C_write(SlaveAddr << 1 | 1);
    // SENDING NACK ACK
    rdat = I2C_nack();
    // issue the stop event;
    I2C_stop();
    return rdat;
}
void I2C_eeprom_pagewrite(u8 SlaveAddr, u8 wBuffAddr, s8 *p, u8 nbytes)
{
	  int i;
    // start event
	  IOCLR1=1<<WP;
    I2C_start();
    //  SLAVE ADDR+ WRITE BIT
    I2C_write(SlaveAddr << 1);
    // writ buff addr
    I2C_write((wBuffAddr>>8)& 0x0f);
	  I2C_write((wBuffAddr)& 0x0f);
    for (i = 0; i < nbytes; i++)
    {
        I2C_write(p[i]);
    }
    I2C_stop();
    delay_ms(10);
}
void I2C_eeprom_seqread(u8 SlaveAddr, u8 rBuffSAddr, s8 *p, u8 nbytes)
{
    int i;
	  IOSET1=1<<WP;
    // issue  the start event
    I2C_start();
    // slave addr
    I2C_write(SlaveAddr << 1);
    // issue the restart event
    I2C_restart();
    // issue the slave addr + read bit
    I2C_write(SlaveAddr << 1 | 1);
    for (i = 0; i < (nbytes - 1); i++)
    {
        p[i] = I2C_mack(); // ACK
    }
    p[i] = I2C_nack(); // NACK last byte
    I2C_stop();
}
