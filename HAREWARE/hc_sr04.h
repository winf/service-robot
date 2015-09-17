/*
 * hc_sr04.h
 *
 *  Created on: 2015-9-16
 *      Author: hello
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

#include "sys.h"


void hc_sr04_init(void);
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM) ;
#endif /* HC_SR04_H_ */
