/*
 * hwbz.c
 *
 *  Created on: 2015-9-16
 *      Author: hello
 */

#include "hwbz.h"
#include "uart.h"
#include "car.h"
#include "delay.h"

void hwbz_init(void){
    RCC->APB2ENR|=1<<8;//PG时钟使能
	GPIOG->CRH&=0XFFFFFF00;//P
	GPIOG->CRH|=0X00000088;
	GPIOG->CRL=0X88888888;//上拉输入
	GPIOG->ODR|=0X3FF;

	Ex_NVIC_Config(6,0,1); 			//下降沿触发,PG0
	Ex_NVIC_Config(6,1,1); 			//下降沿触发,PG1
	Ex_NVIC_Config(6,2,1); 			//下降沿触发
 	Ex_NVIC_Config(6,3,1); 			//下降沿触发
	Ex_NVIC_Config(6,4,1); 			//下降沿触发
	Ex_NVIC_Config(6,5,1); 			//下降沿触发
 	Ex_NVIC_Config(6,6,1); 			//下降沿触发
	Ex_NVIC_Config(6,7,1); 			//下降沿触发
 	Ex_NVIC_Config(6,8,1); 			//下降沿触发
	Ex_NVIC_Config(6,9,1); 			//下降沿触发
	nvic_set_pr(2,EXTI0_IRQn ,0,1);//抢占1，子优先级1，组2
	nvic_set_pr(2,EXTI1_IRQn ,0,1);//抢占1，子优先级1，组2
	nvic_set_pr(2,EXTI2_IRQn ,0,1);//抢占1，子优先级1，组2
	nvic_set_pr(2,EXTI3_IRQn ,0,1);//抢占1，子优先级1，组2
	nvic_set_pr(2,EXTI4_IRQn ,0,1);//抢占1，子优先级1，组2
	nvic_set_pr(2,EXTI9_5_IRQn ,0,1);//抢占1，子优先级1，组2
}//外部中断0服务程序
void EXTI0_IRQHandler(void){
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位
	delay_us(10);//消抖
	if(0==PGin(0)){
		car_stop();
		uart_printf("hwbz_0");
	}
}
//外部中断2服务程序
void EXTI1_IRQHandler(void){
	EXTI->PR=1<<1;  //清除LINE2上的中断标志位
	if(0==PGin(1)){
		car_stop();
		uart_printf("hwbz_1");
	}
}
//外部中断2服务程序
void EXTI2_IRQHandler(void){
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位
	delay_us(10);//消抖
	if(0==PGin(2)){
		car_stop();
		uart_printf("hwbz_2");
	}
}
//外部中断3服务程序
void EXTI3_IRQHandler(void){

	EXTI->PR=1<<3;  //清除LINE3上的中断标志位
	if(0==PGin(3)){
		car_stop();
		uart_printf("hwbz_3");
	}
}
//外部中断4服务程序
void EXTI4_IRQHandler(void){
	EXTI->PR=1<<4;  //清除LINE4上的中断标志位
	delay_us(10);//消抖
	if(0==PGin(4)){
		car_stop();
		uart_printf("hwbz_4");
	}
}

//外部中断4服务程序
void EXTI9_5_IRQHandler(void){
	delay_us(10);//消抖
	EXTI->PR=1<<9|1<<8|1<<7|1<<6|1<<5;
	if(0==PGin(5)){	 //
		uart_printf("hwbz_5");
		car_stop();
	}
	if(0==PGin(6)){	 //
		uart_printf("hwbz_6");
		car_stop();
	}
	if(0==PGin(7)){	 //
		uart_printf("hwbz_7");
		car_stop();
	}
	if(0==PGin(8)){	 //
		uart_printf("hwbz_8");
		car_stop();
	}
	if(0==PGin(9)){	 //
		uart_printf("hwbz_9");
		car_stop();
	}

}




