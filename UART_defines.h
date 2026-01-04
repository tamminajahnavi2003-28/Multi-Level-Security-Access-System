//UART_defines.h
#define FOSC 1200000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD)) // WE get 9664

//UXLCR defines

#define WORDLEN_8BIT 3
#define DLAB_BIT 7

//UXLSR defines 

#define TEMT_BIT 6
#define RDR_BIT 0
#define TXD 1
#define RXD 1
