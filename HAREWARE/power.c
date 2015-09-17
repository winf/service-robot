

#include "power.h"

void power_init(void){

    RCC->APB2ENR|=1<<8;//PG时钟使能

	GPIOG->CRH&=0X00FFFFFF;//PF0~5推挽输出;
	GPIOG->CRH|=0X33000000;
	POWER_5V=0;
	POWER_12V=0;
}

void power_set(const unsigned char *param){
	if('e'== param[0]) POWER_5V=0;
	else if('d' == param[0]) POWER_5V=1;

	if('e'== param[1]) POWER_12V=0;
	else if('d' == param[1]) POWER_12V=1;
}
