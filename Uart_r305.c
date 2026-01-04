
#include <LPC21xx.H>

#include "Uart_r305.h"

char rec_buff[25],dummy1;
unsigned char k=0,ch1;

extern unsigned char buf[25]; 

void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		ch1 = U0RBR;	/* Read to Clear Receive Interrupt */
		if(k<25)
			rec_buff[k++] = ch1; 
  }
  else
  {
      dummy1=U0IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; /* dummy1 write */
}

void InitUART0(void) /* Initialize Serial Interface       */ 
{  
            		
  PINSEL0 |= 0x00000005; /* Enable RxD0 and TxD0              */
  U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U0DLL = DIVISOR;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
  U0DLM = DIVISOR>>8;
  U0LCR = 0x03;         /* DLAB = 0  */
  


  VICIntSelect |= 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | UART_INT0; /* UART0 Interrupt */
  VICIntEnable |= 1 << UART_INT0;   /* Enable UART0 Interrupt */
 
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
             
 
						
}

void UART0_Tx(char ch1)  /* Write character to Serial Port    */  
{ 
  while (!(U0LSR & 0x20));
  U0THR = ch1;                
}

char UART0_Rx(void)    /* Read character from Serial Port   */
{                     
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

void UART0_Str1(unsigned char n)
{
 	unsigned char j;   
    for(j=0;j<n;j++)
    {
        UART0_Tx(buf[j]);
    }   
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int k=0;
  if(n==0)
  {
    UART0_Tx('0');
		return;
  }
  else
  {
     while(n>0)
	 {
	   a[k++]=(n%10)+48;
	   n=n/10;
	 }
	 --k;
	 for(;k>=0;k--)
	 {
	   UART0_Tx(a[k]);
	 }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}


								
