/*
 * motor.c
 *
 *  Created on: 2015-8-27
 *      Author: hello
 */

#include "motor.h"
#include "timer.h"
#include "uart.h"


static void TIM6_Init(u16 arr,u16 psc);

void motor_init(void){

    RCC->APB2ENR|=1<<6|1<<7;//PE,PF时钟使能

	GPIOF->CRL&=0XFF000000;//PF0~5推挽输出;
	GPIOF->CRL|=0X00333333;
	GPIOE->CRL&=0XFF000000;//PF0~5推挽输出;
	GPIOE->CRL|=0X00333333;

	TIM6_Init(99,71);//100us中断一次

	MOTOR1_STOP;
	MOTOR2_STOP;
	MOTOR3_STOP;
	MOTOR4_STOP;

	MOTOR1_EN(1);
	MOTOR2_EN(1);
	MOTOR3_EN(1);
	MOTOR4_EN(1);
}



//定时器6中断服务程序
#define TIM6_PWM_TOTAL 4
static int TIM6_load[4]={10,10,10,10};
static int TIM6_reset=100;
static volatile unsigned long *TIM6_PWM_PIN[4];
void TIM6_IRQHandler(void){

	static int cnt=0;
	int  i;

	if(TIM6->SR&0X0001){//溢出中断
		cnt++;
//		uart1_send_char('T');
		if(cnt==TIM6_reset){//计数到达最大值
			cnt=0;
			for(i=0 ;i<TIM6_PWM_TOTAL ;i++)
				*(TIM6_PWM_PIN[i])=1;
		}else{
			for(i=0 ;i<TIM6_PWM_TOTAL ;i++){
				if(cnt==TIM6_load[i])
					*(TIM6_PWM_PIN[i])=0;
			}
		}
	}
	TIM6->SR&=~(1<<0);//清除中断标志位
}
//通用定时器6中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器6!
static void TIM6_Init(u16 arr,u16 psc){
	RCC->APB2ENR|=1<<6|1<<7;//PE,PF时钟使能
	GPIOF->CRL&=0XFF00FFFF;//PF4,5推挽输出;
	GPIOF->CRL|=0X00330000;
	GPIOE->CRL&=0XFF00FFFF;//PF4,5推挽输出;
	GPIOE->CRL|=0X00330000;

	TIM6_PWM_PIN[0]=(volatile unsigned long  *)BITBAND(GPIOF_ODR_Addr, 4);//
	TIM6_PWM_PIN[1]=(volatile unsigned long  *)BITBAND(GPIOF_ODR_Addr, 5);//
	TIM6_PWM_PIN[2]=(volatile unsigned long  *)BITBAND(GPIOE_ODR_Addr, 4);//
	TIM6_PWM_PIN[3]=(volatile unsigned long  *)BITBAND(GPIOE_ODR_Addr, 5);//
	RCC->APB1ENR|=1<<4;	//TIM6时钟使能
 	TIM6->ARR=arr;  	//设定计数器自动重装值//刚好1ms
	TIM6->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟
	TIM6->DIER|=1<<0;   //允许更新中断
	TIM6->CR1|=0x01;    //使能定时器3
	nvic_set_group(2);
	nvic_set_pr(2,TIM6_IRQn,1,1);//抢占1，子优先级1，组2
}

void motor_set_speed(int car,int speed){
	TIM6_load[car]=speed;
}
