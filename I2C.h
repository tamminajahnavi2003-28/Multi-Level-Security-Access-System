//I2C.h
#ifndef I2C_H
#define I2C_H
#include "types.h"
void Init_I2C(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(u8 data);
u8 I2C_nack(void);
u8 I2C_mack(void);
void I2C_restart(void);
#endif
