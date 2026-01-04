//UART_int.h
#include <LPC21xx.H>  /* LPC21xx definitions         */
#include <string.h>

#define UART_INT_ENABLE 1
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))
#define UART_INT 6

#define TEMT (1<<6)
#define RDR  (1<<0)
   

volatile char buff[14]="";
char dummy;
unsigned char i=0,ch;
volatile unsigned char r_flag=0;

// void UART0_isr(void) __irq
// {
//   if((U0IIR & 0x04)) //check if receive interrupt
//   {
// 		ch = U0RBR;	/* Read to Clear Receive Interrupt */
// 		if(ch != 0x0d)
// 			buff[i++] = ch; 
// 		else
// 		{
// 			buff[i] = '\0';
// 			i=0;
// 			r_flag = 1;
// 		}
//   }
//   else
//   {
//       dummy=U0IIR; //Read to Clear transmit interrupt
  
//   }
//    VICVectAddr = 0; /* dummy write */
// }
// void UART0_isr(void) __irq
// {
//     while (U0LSR & 0x01)  // While data available in RX FIFO
//     {
//         ch = U0RBR;  // Read byte
//         if (ch != 0x0D)
//             buff[i++] = ch;
//         else {
//             buff[i] = '\0';
//             i = 0;
//             r_flag = 1;
//         }
//     }

//     VICVectAddr = 0; // Acknowledge interrupt
// }
void UART0_isr(void) __irq{

  while(U0LSR & 0X01){
    ch=U0RBR;
    if(ch!=0x0D){
      buff[i++]=ch;
    }
    else{
      buff[i]='\0';
      i=0;
      r_flag=1;
    }
  }
  VICVectAddr=0;

}

void InitUART0(void)
{
    PINSEL0 = 0x00000005; // Enable RxD0 and TxD0
    U0LCR = 0x83;         // 8N1, DLAB=1
    U0DLL = DIVISOR;
    U0DLM = DIVISOR >> 8;
    U0LCR = 0x03;         // DLAB=0
    U0FCR = 0x07;         // Enable FIFO

    VICIntSelect = 0;     // All IRQ
    VICVectAddr0 = (unsigned)UART0_isr;
    VICVectCntl0 = 0x20 | UART_INT;  // Enable slot 0 for UART0
    VICIntEnable = 1 << UART_INT;    // Enable UART0 interrupt

    U0IER = 0x01;          // Only enable RX interrupt
}

void UART0_Tx(char ch)  /* Write character to Serial Port    */  
{ 
  while (!(U0LSR & TEMT));
  U0THR = ch;                
}

char UART0_Rx()    /* Read character from Serial Port   */
{                     
  while (!(U0LSR & RDR));
  return (U0RBR);
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_Tx('0');
	return;
  }
  else   
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART0_Tx(a[i]);
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

void  DelayS(unsigned int  dly)
{  unsigned int  i;

   for(; dly>0; dly--) 
      for(i=1200000; i>0; i--);
}

								
// int main()
// {
//   InitUART0();
//   i=0;r_flag=0;
//   while(1)
//   {
		
// 		while(r_flag == 1);
// 		UART0_Str(buff);
// 		UART0_Str("\n\r");
// 		UART0_Float(245.21);
// 		UART0_Str("\n\r");
// 		DelayS(1);
//   }
// }

