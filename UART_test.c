//UART_test.c
#include "uart.h"
#include "types.h"
u32 val;
int main(){
    Init_UART();
    while(1){
        char ch=UART_RX();
        UART_TX(ch);
    }
    val=UART_rxu32();
    while(1);
}