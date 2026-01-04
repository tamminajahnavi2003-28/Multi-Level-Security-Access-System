//pin_defines

#define SCLK_EN 0x00000010

#define SDA_EN  0x00000040


//clock_defines

#define FOSC 12000000

#define CCLK (FOSC*5)

#define PCLK (CCLK/4)

#define I2C_SPEED 100000

#define LOAD_VAL (PCLK/(I2C_SPEED/2))


//sfr_defines

//I2CONSET

#define AA_BIT 2

#define SI_BIT 3

#define STO_BIT 4 

#define STA_BIT 5

#define I2EN_BIT 6


//I2CONCLR

#define AAC_BIT 2

#define SIC_BIT 3

#define STAC_BIT 5

#define I2ENC_BIT 6	


