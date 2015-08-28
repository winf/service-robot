

#include "stdlib.h"
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"
#include "motor.h"
   
 int main(void){
    sys_init();	 //配置系统时钟72M(包括clock, PLL and Flash configuration)
	delay_init();//初始化延时
	uart1_init(72,115200);
	motor_init();
	MOTOR1_FORWARD;
	MOTOR2_FORWARD;
	MOTOR3_BACK;
	MOTOR4_BACK;
	MOTOR1_SPEED(40);
	MOTOR2_SPEED(40);
	MOTOR3_SPEED(40);
	MOTOR4_SPEED(40);
	while(1){
	};

	return 0;
 }



