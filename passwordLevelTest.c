//passwordLevelTest.c
#include <LPC21xx.h>
#include "passwordLevel.h"
#include "Lcd.h"
#include "Lcd_defines.h"
#include "delay.h"
#include "kpm.h"
#include "I2C.h"
#include "I2C_eeprom.h"
#define R_LED 0
#define W_LED 1
int main(){
int i;
    char arr[5]="1234";
	
	IODIR0 |=(1<<R_LED) |(1<<W_LED);
	Init_KPM();
    InitLCD();

    Init_I2C();
    EEPROMInit();

	
	//I2C_eeprom_pagewrite(AT24C256,0x0000, arr, 4);
	  for(i=0;i<4;i++){
	  I2C_eeprom_bytewrite(0x50,0X00+i,arr[i]);
	  }
	delay_ms(2200);/*
		  for(i=0;i<4;i++){
//	I2C_eeprom_byteread(u8 SlaveAddr, u8 ReadBuffAddr)
	  test[i]=I2C_eeprom_byteread(0x50,0X00+i);
	  }
	test[4]='\0';
    StrLCD("eeprom: ");
	StrLCD(test);
	delay_ms(20000);
	CmdLCD(GOTO_LINE2_POS0); */
    if(password_level()){
        IOSET0=1<<R_LED;
        
    }
    else{
        IOCLR0=1<<W_LED;
        
    // CmdLCD(CLEAR_LCD);
    // StrLCD("Wrong Password");
    // delay_s(2);
    }

}

