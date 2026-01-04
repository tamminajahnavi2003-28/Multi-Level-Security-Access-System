//UART_int.h
#ifndef UART_INIT_H
#define UART_INIT_H


void InitUART1(void); /* Initialize Serial Interface       */ 
void UART1_Tx(char ch);  
char UART1_Rx(void);  
void UART1_isr(void) __irq;
#endif
