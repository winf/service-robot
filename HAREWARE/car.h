/*
 * car.h
 *
 *  Created on: 2015-8-28
 *      Author: hello
 */

#ifndef CAR_H_
#define CAR_H_


#include "motor.h"



void car_init(void);
void car_forward(void);
void car_right(void);
void car_left(void);
void car_back(void);
void car_stop(void);
void car_standby(void);
void car_resume(void);
void car_set(const unsigned char *param);
void car_circle(int dir);
void CAR_SET_SPEED(int *sp);

#endif /* CAR_H_ */
