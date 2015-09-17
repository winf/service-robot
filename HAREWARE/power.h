/*
 * power.h
 *
 *  Created on: 2015-9-15
 *      Author: hello
 */

#ifndef POWER_H_
#define POWER_H_

#include "sys.h"


#define POWER_5V   PGout(14)
#define POWER_12V  PGout(15)


void power_init(void);
void power_set(const unsigned char *param);


#endif /* POWER_H_ */
