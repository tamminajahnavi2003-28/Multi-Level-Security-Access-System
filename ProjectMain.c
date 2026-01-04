#include <LPC21xx.h>
#include <string.h>
#include "Lcd.h"
#include "Lcd_defines.h"
#include "types.h"
#include "passwordLevel.h"
#include "rfidLevel.h"
#include "Uart_Rfid.h"
#include "R305.h"
#include "kpm.h"
#include "delay.h"
#include "Motor_driver.h"
#include "Edit_pass.h"
#include "Uart_r305.h"
#include "I2C.h"
volatile u32 eint0_flag = 0;
volatile extern u8 r_flag;

int main()
{
	
    int x;
    static int f=0;
    unsigned int fi;
    Init_KPM();
    Init_Motor();
    InitLCD();
    Init_I2C();
    InitUART1();
    InitUART0();
    enable_eint0();
    //SetPassword();
	while (1)
    {
        while (r_flag == 0)
        {
	     	CmdLCD(GOTO_LINE1_POS0);
		    StrLCD("***Place RFID***");
            if(eint0_flag)	 //External Interrupt  
            {
              ShowMenu();
              handleMenu();
		      eint0_flag=0;
            }
			CmdLCD(GOTO_LINE1_POS0);
        }
        r_flag = 0;
		CmdLCD(0x01);
		CmdLCD(GOTO_LINE1_POS0);
		delay_ms(2000);
		x = RfidLevel();
		S32LCD(x);
		delay_ms(2000);
        if (x == 1)	 //When RFID passed
        {
			StrLCD("Rfid Passed-->");
		    delay_ms(2000);
			CmdLCD(0x01);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Enter Password:");
            if (password_level())	//If Entered password is correct
            {
                CmdLCD(0x01);
                StrLCD("Place Finger");
				delay_ms(2000);
                fi=search_fp();	//Searches for the enrolled fingerprint
				if(fi>0) //if found 
				{
				  S32LCD(fi);
				  delay_ms(2000);
				  CmdLCD(0x01);
				  StrLCD("Securely");
				  CmdLCD(GOTO_LINE2_POS0);
				  StrLCD("Verified");
				  delay_ms(2000);
			//After passing all the levels ..
            // === L293D Motor Control ===
                  Motor_Open();   // Open door or rotate motor
                  CmdLCD(CLEAR_LCD);
                  StrLCD("Door Opening...");
                  delay_s(1); // motor runs for 1 second 
                  CmdLCD(0x01);
                  Motor_Stop();
                  CmdLCD(0x01);
                  StrLCD("Door Opened");
                  delay_s(1);
                  CmdLCD(0x01);
                  delay_s(1);
                  Motor_Close();  // Close door after short delay
                  StrLCD("Door Closing...");
                  delay_s(1);
 		          CmdLCD(0x01);
	              delay_s(1);
                  Motor_Stop();
                  StrLCD("Door Locked");
                  delay_s(1);
                  CmdLCD(0x01);
				}
				else if(fi==0)//if fingerprint not found
				{
				CmdLCD(0x01);
				StrLCD("Fingerprint");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Not Found");
				delay_ms(2000);
				CmdLCD(0x01);
				StrLCD("Access Denied");
				delay_ms(2000);
				}
				else
				{
				StrLCD("Finger print Error");
				delay_ms(1500);
				}
		     }
             else
             {
				CmdLCD(0x01);
                StrLCD("Wrong Password");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Access Blocked");
				delay_ms(2000);
             }
        }
        else if (x == -1)//if invalid RFID card placed
        {
			CmdLCD(0x01);
			StrLCD("Invalid RFID");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Try Again...");
			delay_ms(2000);
        }
		else if(x==2)
		{
			enroll(++f);
		}
		else
		{
			CmdLCD(0x01);
			StrLCD("RFID Error");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Please Retry");
			delay_ms(2000);
		}
    CmdLCD(0x01);

    }
}

