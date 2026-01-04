void delay_us(unsigned int dlyUs)
{
	dlyUs*=12;
	while(dlyUs--);
}
void delay_ms(unsigned int dlyMs)
{
	dlyMs*=12000;
	while(dlyMs--);
}
void delay_s(unsigned int dlyS)
{
	dlyS*=12000000;
	while(dlyS--);
}

