//I2C.c
#include<LPC21xx.h>
#include "I2C_defines.h"
#include "Pinconnect_block.h"
#include "defines.h"
#include "types.h"
void Init_I2C(void)
{
    CfgPortPinFunc(0,2,1);
    CfgPortPinFunc(0,3,1);
    // set the clock speed  I2CCLL AND I2CCLH
    I2SCLL=LOAD_VAL;
    I2SCLH=LOAD_VAL;
    //enable i2c  enble bit
    I2CONSET=1<<I2EN_BIT;
}
void I2C_start(void)
{
    I2CONSET=1<<STA_BIT;
    //CHECK THE status of the event
    while((READBIT(I2CONSET,SI_BIT))==0);
    //clear the start event
    I2CONCLR=1<<STA_BIT;
}
void I2C_stop(void)
{
    I2CONSET=1<<STO_BIT;
    //clear SIC BIT
    I2CONCLR=1<<SI_BIT;
    while((READBIT(I2CONSET,STO_BIT))==0);
}
void I2C_write(u8 data)
{
    I2DAT=data;
    //clear SI bit
    I2CONCLR=1<<SI_BIT;
    //CHECK FOR THE STAus 
    while((READBIT(I2CONSET,SI_BIT))==0);
}
u8 I2C_nack(void)
{
    // issue nack using AA BIT 
    I2CONCLR=1<<AA_BIT;
    //CLEAR THE si bit 
    I2CONCLR=1<<SI_BIT;
    //CHECK THE status of the event
    while((READBIT(I2CONSET,SI_BIT))==0);
    return I2DAT;
}
u8 I2C_mack(void)
{
    // issue nack using AA BIT 
    I2CONSET=1<<AA_BIT;
    //CLEAR THE si bit 
    I2CONCLR=1<<SI_BIT;
    //CHECK THE status of the event
    while((READBIT(I2CONSET,SI_BIT))==0);
    I2CONCLR=1<<AA_BIT;
    return I2DAT;
}
void I2C_restart(void)
{
    I2CONSET=1<<STA_BIT;
    //clear the si bit
    I2CONCLR=1<<SI_BIT;
    //CHECK THE status of the event
    while((READBIT(I2CONSET,SI_BIT))==0);
    //clear the start event
    I2CONCLR=1<<STA_BIT;
}
