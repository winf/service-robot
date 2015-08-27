/*
 * motor.h
 *
 *  Created on: 2015-8-27
 *      Author: hello
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#include "sys.h"


#define MOTOR1_SPEED(X)	TIM4->CCR1=(X)
#define MOTOR2_SPEED(X)	TIM4->CCR2=(X)
#define MOTOR3_SPEED(X)	TIM4->CCR3=(X)
#define MOTOR4_SPEED(X)	TIM4->CCR4=(X)


#define MOTOR1_EN	       PFout(4)
#define MOTOR2_EN	       PFout(5)
#define MOTOR3_EN	       PEout(14)
#define MOTOR4_EN	       PEout(15)

#define MOTOR1_IN1       PFout(0)
#define MOTOR1_IN2       PFout(2)
#define MOTOR2_IN1       PFout(1)
#define MOTOR2_IN2       PFout(3)
#define MOTOR3_IN1       PEout(10)
#define MOTOR3_IN2       PEout(12)
#define MOTOR4_IN1       PEout(11)
#define MOTOR4_IN2       PEout(13)

#define MOTOR1_FORWARD  do{\
								MOTOR1_IN1=1;\
								MOTRO1_IN2=0;\
							}while(0)
#define MOTOR1_BACK  do{\
								MOTOR1_IN1=0;\
								MOTRO1_IN2=1;\
							}while(0)

#define MOTOR1_STOP  do{\
								MOTOR1_IN1=0;\
								MOTRO1_IN2=0;\
							}while(0)

#define MOTOR2_FORWARD  do{\
								MOTOR2_IN1=1;\
								MOTRO2_IN2=0;\
							}while(0)
#define MOTOR2_BACK  do{\
								MOTOR2_IN1=0;\
								MOTRO2_IN2=1;\
							}while(0)

#define MOTOR2_STOP  do{\
								MOTOR2_IN1=0;\
								MOTRO2_IN2=0;\
							}while(0)

#define MOTOR3_FORWARD  do{\
								MOTOR3_IN1=1;\
								MOTRO3_IN2=0;\
							}while(0)

#define MOTOR3_BACK  do{\
								MOTOR3_IN1=0;\
								MOTRO3_IN2=1;\
							}while(0)

#define MOTOR3_STOP  do{\
								MOTOR3_IN1=0;\
								MOTRO3_IN2=0;\
							}while(0)

#define MOTOR4_FORWARD  do{\
								MOTOR4_IN1=1;\
								MOTRO4_IN2=0;\
							}while(0)
#define MOTOR4_BACK  do{\
								MOTOR4_IN1=0;\
								MOTRO4_IN2=1;\
							}while(0)

#define MOTOR4_STOP  do{\
								MOTOR4_IN1=0;\
								MOTRO4_IN2=0;\
							}while(0)


void motor_init(void);

#endif /* MOTOR_H_ */
