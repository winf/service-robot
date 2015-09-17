

#include "steering.h"
#include "timer.h"
#include "delay.h"


static int init[22];

void Steering_Init(void){
	int i;
	TIM2_PWM_Init(20000,71);
	TIM3_PWM_Init(20000,71);
	TIM5_PWM_Init(20000,71);
	TIM1_PWM_Init(20000,71);
	TIM8_PWM_Init(20000,71);
	TIM4_PWM_Init(20000,71);
	for(i=0; i<22; i++)
		init[i]=90;
	Steering_Move(init);
}


void Steering_Move(const int	*p){

	STEERING_1(p[0]);
	STEERING_2(p[1]);
	STEERING_3(p[2]);
	STEERING_4(p[3]);
	STEERING_5(p[4]);
	STEERING_6(p[5]);
	STEERING_7(p[6]);
	STEERING_8(p[7]);
	STEERING_9(p[8]);
	STEERING_10(p[9]);
	STEERING_11(p[10]);
	STEERING_12(p[11]);
	STEERING_13(p[12]);
	STEERING_14(p[13]);
	STEERING_15(p[14]);
	STEERING_16(p[15]);
	STEERING_17(p[16]);
	STEERING_18(p[17]);
	STEERING_19(p[18]);
	STEERING_20(p[19]);
	STEERING_21(p[20]);
	STEERING_22(p[21]);
}


void steering_set(const unsigned char *param){
	unsigned dec;
	dec=param[1];
	dec=dec<<8|param[2];

	switch(param[0]){
	case 1:STEERING_1(dec);break;
	case 2:STEERING_2(dec);break;
	case 3:STEERING_3(dec);break;
	case 4:STEERING_4(dec);break;
	case 5:STEERING_5(dec);break;
	case 6:STEERING_6(dec);break;
	case 7:STEERING_7(dec);break;
	case 8:STEERING_8(dec);break;
	case 9:STEERING_9(dec);break;
	case 10:STEERING_10(dec);break;
	case 11:STEERING_11(dec);break;
	case 12:STEERING_12(dec);break;
	case 13:STEERING_13(dec);break;
	case 14:STEERING_14(dec);break;
	case 15:STEERING_15(dec);break;
	case 16:STEERING_16(dec);break;
	case 17:STEERING_17(dec);break;
	case 18:STEERING_18(dec);break;
	case 19:STEERING_19(dec);break;
	case 20:STEERING_20(dec);break;
	case 21:STEERING_21(dec);break;
	case 22:STEERING_22(dec);break;
	default:;break;
	}
}




