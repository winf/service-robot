

#include "stdlib.h"
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"
#include "motor.h"
#include "car.h"

void cmd_handle(void){
	unsigned char cmd;
	unsigned char cmd_param[8];
	int i;

	cmd = uart1_receive();
	uart1_send_char(cmd);
	switch(cmd){
	case 'f'://前进
		car_forward();
		break;
	case 'b'://后退
		car_back();
		break;
	case 'l'://向左移动
		car_left();
		break;
	case 'r'://向右移动
		car_right();
		break;
	case 's'://制动
		car_stop();
		break;
	case 'i'://初始化
		car_init();
		break;
	case 'y'://待机
		car_standby();
		break;
	case 't'://设置参数
		for(i=0;i<8;i++){
			cmd_param[i]=uart1_receive();
		}
		car_set(cmd_param);
		for(i=0;i<8;i++){
			uart1_send_char(cmd_param[i]);
		}
		break;
	case 'e'://恢复
		car_resume();
		break;
	default:;
	}
}
   
 int main(void){
    sys_init();	 //配置系统时钟72M(包括clock, PLL and Flash configuration)
	delay_init();//初始化延时
	uart2_init(72,9600);
	uart1_init(72,9600);
//	motor_init();
//	MOTOR1_FORWARD;
//	MOTOR2_FORWARD;
//	MOTOR3_BACK;
//	MOTOR4_BACK;
//	MOTOR1_SPEED(40);
//	MOTOR2_SPEED(40);
//	MOTOR3_SPEED(40);
//	MOTOR4_SPEED(40);
	uart1_send_char('o');
	while(1){
		cmd_handle();

	};

	return 0;
 }



