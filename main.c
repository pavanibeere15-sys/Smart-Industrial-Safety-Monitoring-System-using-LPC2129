#include"header.h"
#define temp_thre 40
int main()
{
    unsigned int temperature_value=0,PIR,FLAME;
    float temperature=0.0;
        char a[50];
    adc_init();
    lcd_init();
    uart0_init(9600);

    // LED pins P0.17, P0.18, P0.19
    IODIR0|= (7 << 17);
    IOSET0 = 7 << 17;
	IODIR0 &= ~(1 << 30);   // PIR P0.30 as input
IODIR0 &= ~(1 << 5);    // Flame P0.5 as input

    while(1)
    {

                        temperature_value = adc_read(1);


        temperature = ((temperature_value * 3.3) / 1023)*100;

                if(((IOPIN0>>30)&1))
                PIR=1;
                else
                PIR=0;

if(((IOPIN0>>5)&1)==0)
FLAME=1;
else
FLAME=0;

                                        if((temperature>=temp_thre)||(FLAME==1))
                                        {
                                        //danger
//                                      uart0_string_tx("\r\nTemparature:");
//                                      uart0_float(temperature);
//                                      uart0_string_tx("C\r\n");
                                        sprintf(a,"\r\nTemperature : %.2fC",temperature);
                                        uart0_string_tx(a);
                                                        //uart0_string_tx("\r\n");
                                        if(PIR==1)
                                        uart0_string_tx("\nWORKER : Yes\r\n");
                                        else
                                        uart0_string_tx("\nWORKER : No\r\n");

                                        if(FLAME==1)
                                        uart0_string_tx("FLAME : Yes\r\n");
                                        else
                                        uart0_string_tx("FLAME : No\r\n");

                                        uart0_string_tx("STATUS : Danger\r\n");

                                        uart0_string_tx("RED LED : On\r\n");
lcd_cmd(0x01);
lcd_float(temperature);
lcd_data('C');
lcd_cmd(0xc0);
lcd_string("STATUS : DANGER");
IOSET0=7<<17;
IOCLR0=1<<19;

                                        }


                                        else if(PIR==1)
                                        {
                                        //Warning
//                                      uart0_string_tx("\r\nTemparature:");
//                                      uart0_float(temperature);
//                                      uart0_string_tx("C\r\n");
                                        sprintf(a,"\r\nTemperature : %.2fC",temperature);
                                        uart0_string_tx(a);
                                                //uart0_string_tx("\r\n");
                                        if(PIR==1)
                                        uart0_string_tx("\nWORKER : Yes\r\n");
                                        else
                                        uart0_string_tx("\nWORKER : No\r\n");

                                        if(FLAME==1)
                                        uart0_string_tx("FLAME : Yes\r\n");
                                        else
                                        uart0_string_tx("FLAME : No\r\n");

                                        uart0_string_tx("STATUS : Warning\r\n");

                                        uart0_string_tx("YELLOW LED : On\r\n");
lcd_cmd(0x01);
lcd_float(temperature);
lcd_data('C');
lcd_cmd(0xc0);
lcd_string("STATUS : WARNING");
IOSET0=7<<17;
																				IOCLR0=1<<18;

                                        }

                                else
                                        {
                                        //Safe
//                                      uart0_string_tx("\r\nTemparature:");
//                                      uart0_float(temperature);
//                                      uart0_string_tx("C\r\n");
                                         sprintf(a,"\r\nTemperature : %.2fC",temperature);
                                        uart0_string_tx(a);
                                                //uart0_string_tx("\r\n");
                                        if(PIR==1)
                                        uart0_string_tx("\nWORKER : Yes\r\n");
                                        else
                                        uart0_string_tx("\nWORKER : No\r\n");

                                        if(FLAME==1)
                                        uart0_string_tx("FLAME : Yes\r\n");
                                        else
                                        uart0_string_tx("FLAME : No\r\n");

                                        uart0_string_tx("STATUS : Safe\r\n");

                                        uart0_string_tx("GREEN LED : On\r\n");
lcd_cmd(0x01);
lcd_float(temperature);
lcd_data('C');
lcd_cmd(0xc0);
lcd_string("STATUS :SAFE");
																				IOSET0=7<<17;
IOCLR0=1<<17;

                                        }
                                        delay_sec(1);
        }
        }
