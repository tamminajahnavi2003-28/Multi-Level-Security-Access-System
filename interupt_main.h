//interupt_main.h

#include "types.h"

u32 inputPad(void);
void handleMenu(void);
void eint0_isr(void) __irq;
void enable_eint0(void);
