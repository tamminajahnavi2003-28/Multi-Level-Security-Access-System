#include <LPC21xx.h>
#include "defines.h"
#include "kpm_defines.h"
#include "Lcd_defines.h"
#include "Lcd.h"

unsigned int kpmLUT[4][4] = 
{
    {'1',  '2',  '3',  '/'},
    {'4',  '5',  '6',  '*'},
    {'7',  '8',  '9',  '-'},
    {'c',  '0',  '=',  '+'}
};

void Init_KPM(void){
//Cfg P1.16 TO P1.19
//row lines //all rows are grounded
WRITENIBBLE(IODIR1,ROW0,15);
//DEFAULT ALL COL LINES ARE HIGH
}

unsigned int ColScan(void) 
{
    unsigned int status;
    status = (READNIBBLE(IOPIN1, COL0) != 0x0F) ? 1 : 0; // any column low?
    return status;
}

unsigned int RowCheck(void) 
{
    unsigned int r;
    for (r = 0; r <= 3; r++) 
	{
            WRITENIBBLE(IOPIN1,ROW0,~(1<<r));  
            if (ColScan()) 
		    {                       // if column detects low
             break;
            }
    }
    WRITENIBBLE(IOPIN1,ROW0,0);
    return r;
}

unsigned char ColCheck(void) 
{
    unsigned int c;
    for (c = 0; c <= 3; c++)
    {
        if (READBIT(IOPIN1, (COL0 + c)) == 0) //active low
		{
            break;
        }
    }
    return c;
}



unsigned int keyScan(void) 
{
    unsigned int r, c, key;
    // Wait until a key is pressed   
    // Identify row
    r = RowCheck();
    // Identify column
    c = ColCheck();
    key = kpmLUT[r][c];	 
    // Wait until key released
    //while (ColScan());
    return key;
}

