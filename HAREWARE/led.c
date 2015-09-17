



#include "led.h"


void led_init(void)
{
    RCC->APB2ENR|=1<<6;//PE时钟
	GPIOE->CRL&=0XF00FFFFF;//PE5,6推挽输出;
	GPIOE->CRL|=0X03300000;
}






















