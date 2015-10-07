

#include "stdlib.h"
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"
#include "motor.h"
#include "car.h"
#include "steering.h"
#include "hwbz.h"
#include "power.h"


#define CMD_FORWARD  		'f'
#define CMD_BACK     		'b'
#define CMD_LEFT     		'l'
#define CMD_RIGHT    		'r'
#define CMD_STOP     		's'
#define CMD_INIT     		'i'
#define CMD_STANDBY  		'y'
#define CMD_CIRCLE1 			'c'
#define CMD_CIRCLE2			'd'
#define CMD_MOTOR_SET		't'
#define CMD_RESUME  			'e'
#define CMD_POWER_SET		'p'
#define CMD_STEER_SET		'g'
#define CMD_STEER_SHOW		'w'
#define CMD_STEER_SET_INIT	'n'

void cmd_handle(void){
	unsigned char cmd;
	unsigned char cmd_param[8];
	int i;

	cmd = uart1_receive();
	uart1_send_char(cmd);
	uart2_send_char('O');
	uart3_send_char('K');
	switch(cmd){
	case CMD_FORWARD://前进
		car_forward();
		break;
	case CMD_BACK ://后退
		car_back();
		break;
	case CMD_LEFT://向左移动
		car_left();
		break;
	case CMD_RIGHT://向右移动
		car_right();
		break;
	case CMD_STOP://制动
		car_stop();
		break;
	case CMD_INIT://初始化
		car_init();
		break;
	case CMD_STANDBY://待机
		car_standby();
		break;
	case  CMD_CIRCLE1://转
		car_circle(1);
		break;
	case  CMD_CIRCLE2://反转
		car_circle(0);
		break;
	case CMD_MOTOR_SET://设置参数
		for(i=0;i<8;i++){
			cmd_param[i]=uart1_receive();
		}
		car_set(cmd_param);
		for(i=0;i<8;i++){
			uart1_send_char(cmd_param[i]);
		}
		break;
	case CMD_RESUME://恢复
		car_resume();
		break;
	case CMD_POWER_SET:
		for(i=0;i<2;i++){
			cmd_param[i]=uart1_receive();
		}
		power_set(cmd_param);
		for(i=0;i<2;i++){
			uart1_send_char(cmd_param[i]);
		}
		break;
	case CMD_STEER_SET:
		for(i=0;i<3;i++){
			cmd_param[i]=uart1_receive();
		}
		steering_set(cmd_param);
		for(i=0;i<3;i++){
			uart1_send_char(cmd_param[i]);
		}
		break;
	case CMD_STEER_SHOW:
		steering_show();
		break;
	case CMD_STEER_SET_INIT:
			steering_set_init();
			break;
	default:break;
	}
}
   
 int main(void){
    sys_init();	 //配置系统时钟72M(包括clock, PLL and Flash configuration)
	delay_init();//初始化延时
	uart1_init(72,9600);
	uart2_init(36,9600);//时钟为最高时钟的一半
	uart3_init(36,9600);//时钟为最高时钟的一半
	led_init();
	car_init();
	jtag_set(2);//禁止JTAG,释放PB3,PA15
	Steering_Init();
	uart_printf("ok\r\n");
	hwbz_init();
	power_init();
	while(1){
		cmd_handle();
	};

	return 0;
 }



