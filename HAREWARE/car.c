/*
 * car.c
 *
 *  Created on: 2015-8-28
 *      Author: hello
 */

#include "car.h"
#include "uart.h"


void car_forward(void){

	MOTOR1_FORWARD;
	MOTOR2_FORWARD;
	MOTOR3_FORWARD;
	MOTOR4_FORWARD;

}


void car_back(void){

	MOTOR1_BACK;
	MOTOR2_BACK;
	MOTOR3_BACK;
	MOTOR4_BACK;

}

void car_left(void){

	MOTOR1_FORWARD;
	MOTOR2_BACK;
	MOTOR3_BACK;
	MOTOR4_FORWARD;

}

void car_right(void){

	MOTOR1_BACK;
	MOTOR2_FORWARD;
	MOTOR3_FORWARD;
	MOTOR4_BACK;

}

void car_stop(void){

	MOTOR1_STOP;
	MOTOR2_STOP;
	MOTOR3_STOP;
	MOTOR4_STOP;

}

void car_standby(void){
	MOTOR1_EN(0);
	MOTOR2_EN(0);
	MOTOR3_EN(0);
	MOTOR4_EN(0);
}


void car_resume(void){
	MOTOR1_EN(1);
	MOTOR2_EN(1);
	MOTOR3_EN(1);
	MOTOR4_EN(1);
}

void car_circle(int dir){
	if(dir){
		MOTOR1_FORWARD;
		MOTOR2_FORWARD;
		MOTOR3_BACK;
		MOTOR4_BACK;

	}else{
		MOTOR1_BACK;
		MOTOR2_BACK;
		MOTOR3_FORWARD;
		MOTOR4_FORWARD;

	}

}


void car_set(const unsigned char *param){

	int i;

	uart_printf("\r\nparam\r\n");
	for(i=0;i < 8; i++){
		uart_printf("%c",param[i]);
	}
	uart_printf("\r\n");
	switch(param[0]){
	case 'F': MOTOR1_FORWARD;
	break;
	case 'B': MOTOR1_BACK;
	break;
	case 'S': MOTOR1_STOP;
	break;
	}

	switch(param[1]){
	case 'F': MOTOR2_FORWARD;
	break;
	case 'B': MOTOR2_BACK;
	break;
	case 'S': MOTOR2_STOP;
	break;
	}
	switch(param[2]){
	case 'F': MOTOR3_FORWARD;
	break;
	case 'B': MOTOR3_BACK;
	break;
	case 'S': MOTOR3_STOP;
	break;
	}

	switch(param[3]){
	case 'F': MOTOR4_FORWARD;
	break;
	case 'B': MOTOR4_BACK;
	break;
	case 'S': MOTOR4_STOP;
	break;
	}

	MOTOR1_SPEED(param[4]);
	MOTOR2_SPEED(param[5]);
	MOTOR3_SPEED(param[6]);
	MOTOR4_SPEED(param[7]);
}



