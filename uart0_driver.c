#include<lpc21xx.h>
#include"header.h"
void uart0_init(unsigned int baud)
{
unsigned int result=0,pclk;
if(VPBDIV==0)
pclk=15000000;
else if(VPBDIV==1)
pclk=60000000;
else if(VPBDIV==2)
pclk=30000000;
result=pclk/16*(baud);
PINSEL0|=0x05;
U0LCR=0x83;
U0DLL=result&0xFF;
U0DLM=(result>>8)&0xFF;
U0LCR=0x03;
}
 
 void uart0_tx(unsigned char data)
 {
 U0THR=data; while(((U0LSR>>5)&1)==0);
 }
 
 unsigned char uart0_rx(void)
 {
 while((U0LSR&1)==0);
 return U0RBR;
 }
 
 void uart0_string_tx(char *ptr)
 {
 while(*ptr)
 {
 uart0_tx(*ptr);
	 ptr++;
 }
 }
 
 void uart0_rx_string(char*str,int len)
 {
 int i;
	 for(i=0;i<len;i++)
	 {
		 while(U0LSR&1);
	 str[i]=U0RBR;
		 if(str[i]=='\r')
			 break;
	 }
	 str[i]='\0';
 }
void uart0_integer(int num)
{
int a[10],i;
if(num==0)
{
uart0_tx('0');
}
if(num<0)
{
num=-num;
uart0_tx('-');
}
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
{
uart0_tx(a[i]);
}
}

void uart0_float(int f)
{
int num;
if(f==0)
f=0.0;
if(f<0)
{
f=-f;
lcd_data('-');
}
num=f;
lcd_integer(num);
lcd_data('.');
num=(f-num)*1000000;
lcd_integer(num);
}
