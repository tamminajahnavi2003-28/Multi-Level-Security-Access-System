//Uart_Rfid.c
#include <LPC21xx.h>  /* LPC21xx definitions         */
#include <string.h>
#include <stdlib.h>

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))
#define UART_INT1 7

#define TEMT (1<<6)
#define RDR  (1<<0)
   

volatile char buff[14]="";
char dummy;
volatile unsigned char i=0,ch;
volatile unsigned char r_flag=0;

void UART1_isr(void) __irq
{
  if((U1IIR & 0x04)) //check if receive interrupt
  {
		ch = U1RBR;	/* Read to Clear Receive Interrupt */
		if(ch != 0x03){
		//r_flag=1;
			buff[i++] = ch; 
			}
		else
		{
			buff[i] = '\0';
			i=0;
			r_flag = 1;
		}
  }
  else
  {
      dummy=U1IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; /* dummy write */
}

void InitUART1(void)
{
    PINSEL0 |= 0x00050000; // Enable RxD1 and TxD1
    U1LCR = 0x83;         // 8N1, DLAB=1
    U1DLL = DIVISOR;
    U1DLM = DIVISOR >> 8;
    U1LCR = 0x03;         // DLAB=0
   // U0FCR = 0x07;         // Enable FIFO

    VICIntSelect |= 0;     // All IRQ
    VICVectAddr1 = (unsigned)UART1_isr; 
    VICVectCntl1 = 0x20 | UART_INT1;  // Enable slot 0 for UART0
    VICIntEnable |= 1 << UART_INT1;    // Enable UART0 interrupt
    U1IER = 0x01;          // Only enable RX interrupt
}

void UART1_Tx(char ch)  /* Write character to Serial Port    */  
{ 
  while (!(U1LSR & TEMT));
  U0THR = ch;                
}

char UART1_Rx()    /* Read character from Serial Port   */
{                     
  while (!(U1LSR & RDR));
  return (U1RBR);
}
