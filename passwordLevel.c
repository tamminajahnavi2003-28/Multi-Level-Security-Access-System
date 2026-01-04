// passwordLevel.c
#include <LPC21xx.h>
#include "types.h"
#include "Lcd.h"
#include "Lcd_defines.h"
#include "kpm.h"
#include "I2C_eeprom.h"
#include <string.h>
#include "delay.h"
//extern volatile 
char *readnum()
{
    static char arr[5];
    char key = '\0';
    int i = 0, j;
    long count = 0;

    for (j = 0; j < 5; j++)
        arr[j] = '\0';

    while (1)
    {
        key = '\0';
        count = 0;
			
        while (!ColScan()) 
		{
            if (count++ > 12000000)
                return NULL;
        }
				
		    count=0;

        key = keyScan();


        while (ColScan() == 1) 
		{
            if (count++ > 48000000)
                return NULL;
        }

        delay_ms(150);  // debounce delay

        if (key >= '0' && key <= '9') 
		{
            if (i < 4) {
                arr[i++] = key;
                CharLCD('*');
            }
        }
        else if (key == 'c')
		 {
            if (i > 0) {
                i--;
                arr[i] = '\0';
                CmdLCD(SHIFT_CUR_LEFT);
                CharLCD(' ');
                CmdLCD(SHIFT_CUR_LEFT);
            }
        }
        else if (key == '=') 
		{
            arr[i] = '\0';
            break;
        }
    }

    return arr;
}
int password_level()
{	
  int i;
  int count = 4;
  char *pass;
  char OG_pass[5]="1234";
  for(i=0;i<4;i++)
	{
	  OG_pass[i]=I2C_eeprom_byteread(0x50,0X00+i);
	}
	OG_pass[4] = '\0';
    while (count--)	  
    {
        CmdLCD(GOTO_LINE2_POS0);
        pass = readnum();
        if(pass==NULL)
		{
			CmdLCD(0x01);
			StrLCD("Timeout!");
			count--;
			delay_ms(500);
		    continue;
        }
		CmdLCD(CLEAR_LCD);
		StrLCD("Verifying");
        delay_ms(1000);
				
        if (strcmp(pass, OG_pass) == 0)
        {
			CmdLCD(0x01);
			StrLCD("Correct");
			delay_ms(2000);
			CmdLCD(0x01);
            return 1;
        }
		else
		{
			CmdLCD(0x01);
			StrLCD("Wrong Pass");
			delay_ms(2000);
					
			if(count==1)
			{
				CmdLCD(CLEAR_LCD);
				StrLCD("Card Blocked!");
				delay_ms(3000);
				CmdLCD(0x01) ;
				return 0;
			}
		    CmdLCD(0x01);
			StrLCD("Try Again");
			delay_ms(2000);
			}
        }
   CmdLCD(0x01);
   return 0;
}
