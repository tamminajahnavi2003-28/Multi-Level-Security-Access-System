//Lcd.h
#ifndef LCD_H
#define LCD_H
void WriteLCD(unsigned char);
void CmdLCD(unsigned char cmd);
void CharLCD(unsigned char asciiVal);
void InitLCD(void);
void StrLCD(char*p);
void U32LCD(unsigned int num);
void S32LCD(int num);
void F32LCD(float fNUm,unsigned char nDP);
void BuildCGRAM(unsigned char *p,unsigned char nBytes);
#endif

