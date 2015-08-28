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


#define MOTOR1_EN(x)	      PFout(4)=(x)
#define MOTOR2_EN(x)       PFout(5)=(x)
#define MOTOR3_EN(x)       PEout(4)=(x)
#define MOTOR4_EN(x)	      PEout(5)=(x)

#define MOTOR1_IN1       PFout(0)
#define MOTOR1_IN2       PFout(2)
#define MOTOR2_IN2       PFout(1)
#define MOTOR2_IN1       PFout(3)
#define MOTOR3_IN1       PEout(0)
#define MOTOR3_IN2       PEout(2)
#define MOTOR4_IN2       PEout(1)
#define MOTOR4_IN1       PEout(3)

#define MOTOR1_FORWARD  do{\
								MOTOR1_IN1=1;\
								MOTOR1_IN2=0;\
							}while(0)
#define MOTOR1_BACK  do{\
								MOTOR1_IN1=0;\
								MOTOR1_IN2=1;\
							}while(0)

#define MOTOR1_STOP  do{\
								MOTOR1_IN1=0;\
								MOTOR1_IN2=0;\
							}while(0)

#define MOTOR2_FORWARD  do{\
								MOTOR2_IN1=1;\
								MOTOR2_IN2=0;\
							}while(0)
#define MOTOR2_BACK  do{\
								MOTOR2_IN1=0;\
								MOTOR2_IN2=1;\
							}while(0)

#define MOTOR2_STOP  do{\
								MOTOR2_IN1=0;\
								MOTOR2_IN2=0;\
							}while(0)

#define MOTOR3_FORWARD  do{\
								MOTOR3_IN1=1;\
								MOTOR3_IN2=0;\
							}while(0)

#define MOTOR3_BACK  do{\
								MOTOR3_IN1=0;\
								MOTOR3_IN2=1;\
							}while(0)

#define MOTOR3_STOP  do{\
								MOTOR3_IN1=0;\
								MOTOR3_IN2=0;\
							}while(0)

#define MOTOR4_FORWARD  do{\
								MOTOR4_IN1=1;\
								MOTOR4_IN2=0;\
							}while(0)
#define MOTOR4_BACK  do{\
								MOTOR4_IN1=0;\
								MOTOR4_IN2=1;\
							}while(0)

#define MOTOR4_STOP  do{\
								MOTOR4_IN1=0;\
								MOTOR4_IN2=0;\
							}while(0)


void motor_init(void);

#endif /* MOTOR_H_ */
