//I2C_eeprom.h

#include "types.h"
#define AT24C256 0x50
void EEPROMInit(void);
void I2C_eeprom_bytewrite(u8 SlaveAddr, u8 wBuffAddr, u8 data);

u8 I2C_eeprom_byteread(u8 SlaveAddr, u8 ReadBuffAddr);

void I2C_eeprom_pagewrite(u8 SlaveAddr, u8 wBuffAddr, s8 *p, u8 nbytes);

void I2C_eeprom_seqread(u8 SlaveAddr, u8 rBuffSAddr, s8 *p, u8 nbytes);
