/*
 * car.c
 *
 *  Created on: 2015-8-28
 *      Author: hello
 */

#include "car.h"


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


void car_set(const unsigned char *param){

	car_standby();

	switch(param[0]){
	case 'F': MOTOR1_FORWARD;
	case 'B': MOTOR1_BACK;
	case 'S': MOTOR1_STOP;
	}

	switch(param[1]){
	case 'F': MOTOR2_FORWARD;
	case 'B': MOTOR2_BACK;
	case 'S': MOTOR2_STOP;
	}
	switch(param[2]){
	case 'F': MOTOR3_FORWARD;
	case 'B': MOTOR3_BACK;
	case 'S': MOTOR3_STOP;
	}

	switch(param[3]){
	case 'F': MOTOR4_FORWARD;
	case 'B': MOTOR4_BACK;
	case 'S': MOTOR4_STOP;
	}

	MOTOR1_SPEED(param[4]);
	MOTOR2_SPEED(param[5]);
	MOTOR3_SPEED(param[6]);
	MOTOR4_SPEED(param[7]);
	car_resume();
}



