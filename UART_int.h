//UART_int.h
#ifndef UART_INIT_H
#define UART_INIT_H
void InitUART0 (void); /* Initialize Serial Interface       */ 
void UART0_Tx(char ch);  
char UART0_Rx(void);  
#endif