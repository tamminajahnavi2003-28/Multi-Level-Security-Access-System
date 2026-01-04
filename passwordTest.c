//passwordTest.c
#include <LPC21xx.h>
#include "kpm.h"
#include "Lcd.h"
#include "Lcd_defines.h"
#include "delay.h"
#include <stdio.h>
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

        while (!ColScan()) {
            if (count++ > 6000000)
                return NULL;
        }

        key = keyScan();

        // Wait until key release
        while (ColScan() == 1) {
            if (count++ > 48000000)
                return NULL;
        }

        delay_ms(150);  // debounce delay

        if (key >= '0' && key <= '9') {
            if (i < 4) {
                arr[i++] = key;
                CharLCD('*');
            }
        }
        else if (key == 'c') {
            if (i > 0) {
                i--;
                arr[i] = '\0';
                CmdLCD(SHIFT_CUR_LEFT);
                CharLCD(' ');
                CmdLCD(SHIFT_CUR_LEFT);
            }
        }
        else if (key == '=') {
            arr[i] = '\0';
            break;
        }
    }

    return arr;
}

int main(){
    char *arr;
    Init_KPM();
    InitLCD();
    StrLCD("enter:");
    CmdLCD(GOTO_LINE2_POS0);
    arr=readnum();
	  if(arr==NULL){
			CmdLCD(CLEAR_LCD);
            StrLCD("too delay");
            delay_ms(5000);
		}
		else{
						CmdLCD(CLEAR_LCD);
            StrLCD("good");
            delay_ms(5000);
		}
    while(1);
    

    


}
