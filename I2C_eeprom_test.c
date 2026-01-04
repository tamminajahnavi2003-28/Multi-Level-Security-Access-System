// I2C_eeprom_test.c

#include <LPC21xx.h>

#include "types.h"

#include "i2c.h"
#include "LCD_drive_prac.h"	
#include "LCD_def_prac.h"
	   

#include "I2C_eeprom.h"

#define SLED 20
#define FLED 21

u8 rdat;

int main(){

    char wdat='A';
    IODIR0|=3<<SLED;
	Init_LCD();

	EEPROMInit();

    Init_I2C();
	StrLCD("sent data:");
	CharLCD(wdat);

    I2C_eeprom_bytewrite(0x50,0x00,wdat);


     rdat=I2C_eeprom_byteread(0x50,0x00);
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("read data:");
	CharLCD(rdat);

     if(rdat=='A'){

         IOPIN0|=1<<SLED;

     }

     else{

         IOPIN0|=1<<FLED;



     }

	 while(1);




}
