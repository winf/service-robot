

#include "stdlib.h"
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"
#include "motor.h"
   
 int main(void){
	 u8 char_buf;
    sys_init();	 //配置系统时钟72M(包括clock, PLL and Flash configuration)
	delay_init();//初始化延时
	uart1_init(72,115200);
	motor_init();
	while(1){
	};

	return 0;
 }



