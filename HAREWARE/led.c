



#include "led.h"


void led_init(void)
{
    RCC->APB2ENR|=1<<3;//PE时钟
	GPIOE->CRL&=0XFFFFFF00;//PC0,1推挽输出;
	GPIOE->CRL|=0X00000033;
	LED0=1;
	LED1=1;
}






















