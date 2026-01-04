//rfidLevel.c
#include "types.h"
volatile extern s8 buff[14];

static char arr[3][10]={"12555657","12535708","12601094"};
static char mas[10]="01157435";
int RfidLevel()
{
    int i=0,j;
    for(i=0;i<8;i++)
	{
        if(buff[i+1]!=mas[i])
		{
            break;
        }

    }
    if(i==8)
	{
        return 2;
    }

	for(j=0;j<4;j++)
	{
       for(i=0;i<8;i++)
	   {
          if(arr[j][i]!=buff[i+1])
		  {
             break;
          }
       }
	   if(i==8)
	   {
	   return 1;
	   }
	}
    return 0;
}
