/*
 * motor.c
 *
 *  Created on: 2015-8-27
 *      Author: hello
 */

#include "motor.h"
#include "timer.h"


void motor_init(void){

    RCC->APB2ENR|=1<<6|1<<7;//PE,PF时钟使能

	GPIOF->CRL&=0XFF000000;//PF0~5推挽输出;
	GPIOF->CRL|=0X00333333;
	GPIOE->CRL&=0XFF000000;//PF0~5推挽输出;
	GPIOE->CRL|=0X00333333;

	TIM4_PWM_Init(100,71);
	MOTOR1_SPEED(80);
	MOTOR2_SPEED(80);
	MOTOR3_SPEED(80);
	MOTOR4_SPEED(80);

	MOTOR1_FORWARD;
	MOTOR2_FORWARD;
	MOTOR3_FORWARD;
	MOTOR4_FORWARD;

	MOTOR1_EN(1);
	MOTOR2_EN(1);
	MOTOR3_EN(1);
	MOTOR4_EN(1);
}
