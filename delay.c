#include<lpc21xx.h>

void delay_sec(unsigned int sec)
{
T0PR=60000-1;
T0PC=T0TC=0;
T0TCR=0x02;
T0TCR=0x01;
while(T0TC<sec);
T0TCR=0;
}
void delay_ms(unsigned int ms)
{
T0PR=15000-1;
T0PC=T0TC=0;
T0TCR=0x02;
T0TCR=0x01;
while(T0TC<ms);
T0TCR=0;
}
