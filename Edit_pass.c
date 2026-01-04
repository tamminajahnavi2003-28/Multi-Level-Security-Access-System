// interupt_main.c
#include <LPC21xx.h>
#include "interupt_defines.h"
#include "Lcd.h"
#include "Lcd_defines.h"
#include <stdlib.h>
#include "delay.h"
//#include "rtc.h"
#include "kpm.h"
#include "Pinconnect_block.h"
#include "types.h"
#include "passwordLevel.h"
#include "rfidLevel.h"
#include "I2C_eeprom.h"
#include "delay.h"
#include <string.h>
volatile extern u32 eint0_flag;
volatile extern u8 r_flag;
void SetPassword(){
int i;
char arr[5]="1234";

for(i=0;i<4;i++){
I2C_eeprom_bytewrite(0x50,0x0000+i,arr[i]);
}
}
char inp()
{
  char key = '\0';
  while(1)
  {
    key = keyScan();
	if(key!='\0')
	{
    while (ColScan == 0);
    delay_ms(400);
    CharLCD(key);
  return key;
  }													 
  }
}
void ShowMenu()
{
  CmdLCD(CLEAR_LCD);
  StrLCD("1.EdtPWD");
  CmdLCD(GOTO_LINE2_POS0);
  StrLCD(" 2.RSTPWD");
  

 
}
void handleMenu()
{
    char key;
    int i;
    char pass[5], pass1[5];   // local buffers for passwords
	   char *temp ;
    key = inp();
	  delay_ms(2000);
    switch (key)
    {
        case '1':
            CmdLCD(CLEAR_LCD);
            StrLCD("Place card...");
            delay_ms(1000);

            while (r_flag == 0);
            r_flag = 0;

            if (RfidLevel() == 1)
            {
                CmdLCD(CLEAR_LCD);
                StrLCD("Enter Old Pass:");
                delay_ms(500);

                if (password_level())   // old password correct
                {
                    CmdLCD(CLEAR_LCD);
                    delay_ms(100);
                    StrLCD("New Passwd:");
                    CmdLCD(GOTO_LINE2_POS0);

                    temp = readnum();
                    if (temp == NULL)
                    {
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Timeout/Error");
                        delay_ms(2000);
                        return;
                    }
                    strcpy(pass, temp);   // copy 1st entry

                    CmdLCD(CLEAR_LCD);
                    delay_ms(100);
                    StrLCD("Enter again:");
                    CmdLCD(GOTO_LINE2_POS0);

                    temp = readnum();
                    if (temp == NULL)
                    {
											
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Timeout/Error");
                        delay_ms(500);
                        return;
                    }
                    strcpy(pass1, temp);  // copy 2nd entry

                    if (strcmp(pass, pass1) == 0)
                    {
                        for (i = 0; i < 4; i++)
                        {
                            I2C_eeprom_bytewrite(0x50, 0x00 + i, pass[i]);
                            delay_ms(10); // EEPROM safe delay
                        }

                        CmdLCD(CLEAR_LCD);
                        StrLCD("Password");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("Changed OK");
                        delay_ms(2000);
                        CmdLCD(CLEAR_LCD);
                        return;
                    }
                    else
                    {
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Not matched");
                        delay_ms(2000);
                        return;
                    }
                }
                else
                {
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Wrong Pass");
                    CmdLCD(GOTO_LINE2_POS0);
                    StrLCD("Access Denied");
                    delay_ms(2000);
                }
            }
            else
            {
                CmdLCD(CLEAR_LCD);
                StrLCD("Invalid RFID");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("Try Again...");
                delay_ms(2000);
            }
            break;

        case '2':
            CmdLCD(CLEAR_LCD);
            StrLCD("Place Card...");
            delay_ms(1000);

            while (r_flag == 0);
            r_flag = 0;

            if (RfidLevel() == 1)
            {
							  
                CmdLCD(CLEAR_LCD);
                StrLCD("Resetting...");
                delay_ms(1000);

                SetPassword();

                CmdLCD(CLEAR_LCD);
                StrLCD("Password Reset");
                delay_ms(2000);
            }
            else if (RfidLevel() == -1)
            {
                CmdLCD(CLEAR_LCD);
                StrLCD("RFID Failed");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("Try Again...");
                delay_ms(2000);
            }
            else
            {
                CmdLCD(CLEAR_LCD);
                StrLCD("No Card Found");
                delay_ms(2000);
            }
            break;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("Invalid Option");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("Press 1 or 2");
            delay_ms(2000);
            break;
    }

    eint0_flag = 0;
}

void eint0qw(void) __irq
{
  eint0_flag = 1;

  // set flag for main
  EXTINT = 1 << 0; // clear EINT0
  VICVectAddr = 0; // Acknowledge
}
void enable_eint0(void)
{
    // Configure P0.16 as input
    IO0DIR &= ~(1 << 16);
    
    // Configure P0.16 as EINT0 function
    PINSEL1 &= ~(0x3 << 0);  // Clear bits first
    PINSEL1 |= (1 << 0);     // Set EINT0 function (01)
    // Configure interrupt as edge-sensitive, falling edge
    EXTMODE |= (1 << 0);      // Edge triggered
    EXTPOLAR &= ~(1 << 0);    // Falling edge (FIX: was wrong before)
    
    // Clear any pending interrupt
    EXTINT = (1 << 0);
    
    // Configure VIC
    VICIntSelect &= ~(1 << EINT0);    // IRQ (not FIQ)
    VICVectAddr2 = (unsigned int)eint0qw;
    VICVectCntl2 = (1 << 5) | EINT0;
    VICIntEnable = (1 << EINT0);      // Enable EINT0
}
