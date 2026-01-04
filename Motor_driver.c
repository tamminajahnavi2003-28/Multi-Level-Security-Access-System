#include<LPC21xx.h>
void Init_Motor(void)
{
    IODIR0 |= (1 << 21) | (1 << 22)|(1<<15) ; // Set pins as output
    IOSET0=1<<15;
}
void Motor_Open(void)
{
    IOSET0 = (1 << 21); // IN1 = 1
    IOCLR0 = (1 << 22); // IN2 = 0
    IOSET0 = (1 << 15); // Enable ON
}

void Motor_Close(void)
{
    IOCLR0 = (1 << 21); // IN1 = 0
    IOSET0 = (1 << 22); // IN2 = 1
    IOSET0 = (1 << 15); // Enable ON
}

void Motor_Stop(void)
{
    IOSET0 = (1 << 21) | (1 << 22)| (1<<15); // Disable all
}
