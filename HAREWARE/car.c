/*
 * car.c
 *
 *  Created on: 2015-8-28
 *      Author: hello
 */

#include "car.h"
#include "uart.h"
#include "delay.h"

static int speed[4]={30,30,30,30};
static int speed_low[40]={10,10,10,10};

void CAR_SET_SPEED(int *sp){
	MOTOR1_SPEED(sp[0]);
	MOTOR2_SPEED(sp[0]);
	MOTOR3_SPEED(sp[0]);
	MOTOR4_SPEED(sp[0]);
}

void car_init(void){
	motor_init();
	CAR_SET_SPEED(speed);
}

void car_forward(void){
	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
	MOTOR1_FORWARD;
	MOTOR2_FORWARD;
	MOTOR3_FORWARD;
	MOTOR4_FORWARD;
	delay_ms(500);
	CAR_SET_SPEED(speed);//回复原始速度

}


void car_back(void){

	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
	MOTOR1_BACK;
	MOTOR2_BACK;
	MOTOR3_BACK;
	MOTOR4_BACK;
	delay_ms(500);
	CAR_SET_SPEED(speed);//回复原始速度
}

void car_left(void){
	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
	MOTOR1_FORWARD;
	MOTOR2_BACK;
	MOTOR3_BACK;
	MOTOR4_FORWARD;
	delay_ms(500);
	CAR_SET_SPEED(speed);//回复原始速度
}

void car_right(void){
	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
	MOTOR1_BACK;
	MOTOR2_FORWARD;
	MOTOR3_FORWARD;
	MOTOR4_BACK;
	delay_ms(500);
	CAR_SET_SPEED(speed);//回复原始速度
}

void car_stop(void){

	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
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
	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
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
	delay_ms(500);
	CAR_SET_SPEED(speed);//回复原始速度
}


void car_set(const unsigned char *param){


	CAR_SET_SPEED(speed_low);//减速,电机换向
	delay_ms(500);
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

	speed[0]=param[4];
	speed[1]=param[5];
	speed[2]=param[6];
	speed[3]=param[7];
	delay_ms(500);
	CAR_SET_SPEED(speed);
}



