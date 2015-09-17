#include "timer.h"




//TIM4 CH1,2,3,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<0; 	//TIM4时钟使能
	RCC->APB2ENR|=1<<2|1<<3;    	//使能PORTB,A时钟

	GPIOA->CRH&=0X0FFFFFFF;	//PA15输出
	GPIOA->CRH|=0XB0000000;	//复用功能输出

	GPIOB->CRL&=0XFFFF0FFF;	//PB3输出
	GPIOB->CRL|=0X0000B000;	//复用功能输出
	GPIOB->CRH&=0XFFFF00FF;	//PB10,11输出
	GPIOB->CRH|=0X0000BB00;	//复用功能输出



	TIM2->ARR=arr;			//设定计数器自动重装值
	TIM2->PSC=psc;			//预分频器分频设置

	TIM2->CCMR1|=7<<4 | 7<<12;  	//CH1和CH2 PWM2模式
	TIM2->CCMR1|=1<<3 | 1<<11; 		//CH1和CH2 预装载使能
	TIM2->CCMR2|=7<<4 | 7<<12;  	//CH3和CH4 PWM2模式
	TIM2->CCMR2|=1<<3 | 1<<11; 		//CH3和CH4 预装载使能
	AFIO->MAPR&= ~(3<<8); //清除MAPR的[9:8]
	AFIO->MAPR|=3<<8;      //完全重映像,CH1/ETR/PA15,CH2/PB3,CH3/PB10,CH4/PB11)

	TIM2->CCER|=3<<12|3<<8|3<<4|3<<0;   	//OC1,,2,3,4 低电平有效 OC1,2,3,4 输出使能

	TIM2->CR1=0x0080;   	//ARPE使能
	TIM2->CR1|=0x01;    	//使能定时器4
}

//TIM4 CH1,2,3,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<2; 	//TIM4时钟使能
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟
 	  	
	GPIOB->CRL&=0X00FFFFFF;	//PB6,7输出
	GPIOB->CRL|=0XBB000000;	//复用功能输出
	GPIOB->CRH&=0XFFFFFF00;	//PB8,9输出
	GPIOB->CRH|=0X000000BB;	//复用功能输出
 
	TIM4->ARR=arr;			//设定计数器自动重装值
	TIM4->PSC=psc;			//预分频器分频设置
	
	TIM4->CCMR1|=7<<4 | 7<<12;  	//CH1和CH2 PWM2模式
	TIM4->CCMR1|=1<<3 | 1<<11; 		//CH1和CH2 预装载使能
	TIM4->CCMR2|=7<<4 | 7<<12;  	//CH3和CH4 PWM2模式
	TIM4->CCMR2|=1<<3 | 1<<11; 		//CH3和CH4 预装载使能

	TIM4->CCER|=3<<12|3<<8|3<<4|3<<0;   	//OC1,,2,3,4 低电平有效 OC1,2,3,4 输出使能

	TIM4->CR1=0x0080;   	//ARPE使能
	TIM4->CR1|=0x01;    	//使能定时器4
}

//TIM3 CH1,2,3,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<1; 	//TIM3时钟使能
	RCC->APB2ENR|=1<<2|1<<3;    	//使能PORTA,B时钟

	GPIOA->CRL&=0X00FFFFFF;	//PA6,7输出
	GPIOA->CRL|=0XBB000000;	//复用功能输出
	GPIOB->CRL&=0XFFFFFF00;	//PB0,1输出
	GPIOB->CRL|=0X000000BB;	//复用功能输出

	TIM3->ARR=arr;			//设定计数器自动重装值
	TIM3->PSC=psc;			//预分频器分频设置

	TIM3->CCMR1|=7<<4 | 7<<12;  	//CH1和CH2 PWM2模式
	TIM3->CCMR1|=1<<3 | 1<<11; 		//CH1和CH2 预装载使能
	TIM3->CCMR2|=7<<4 | 7<<12;  	//CH3和CH4 PWM2模式
	TIM3->CCMR2|=1<<3 | 1<<11; 		//CH3和CH4 预装载使能

	TIM3->CCER|=3<<12|3<<8|3<<4|3<<0;   	//OC1,,2,3,4 低电平有效 OC1,2,3,4 输出使能

	TIM3->CR1=0x0080;   	//ARPE使能
	TIM3->CR1|=0x01;    	//使能定时器3
}

//TIM5 CH1,2,3,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM5_PWM_Init(u16 arr,u16 psc)
{
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<3; 	//TIM5时钟使能
	RCC->APB2ENR|=1<<2;    	//使能PORTA时钟

	GPIOA->CRL&=0XFFFF0000;	//PA0,1,2,3输出
	GPIOA->CRL|=0X0000BBBB;	//复用功能输出

	TIM5->ARR=arr;			//设定计数器自动重装值
	TIM5->PSC=psc;			//预分频器分频设置

	TIM5->CCMR1|=7<<4 | 7<<12;  	//CH1和CH2 PWM2模式
	TIM5->CCMR1|=1<<3 | 1<<11; 		//CH1和CH2 预装载使能
	TIM5->CCMR2|=7<<4 | 7<<12;  	//CH3和CH4 PWM2模式
	TIM5->CCMR2|=1<<3 | 1<<11; 		//CH3和CH4 预装载使能

	TIM5->CCER|=3<<12|3<<8|3<<4|3<<0;   	//OC1,,2,3,4 低电平有效 OC1,2,3,4 输出使能

	TIM5->CR1=0x0080;   	//ARPE使能
	TIM5->CR1|=0x01;    	//使能定时器5
}

//TIM1 CH1,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)
{
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<2|1<<11;    	//TIM1时钟使能,使能PORTA时钟

	GPIOA->CRH&=0XFFFF0FF0;	//PA8,11输出
	GPIOA->CRH|=0X0000B00B;	//复用功能输出

	TIM1->ARR=arr;			//设定计数器自动重装值
	TIM1->PSC=psc;			//预分频器分频设置

	TIM1->CCMR1|=7<<4;  	//CH1PWM2模式
	TIM1->CCMR1|=1<<3; 		//CH1预装载使能
	TIM1->CCMR2|=7<<12;  	//CH4 PWM2模式
	TIM1->CCMR2|=1<<11; 		//CH4 预装载使能

	TIM1->CCER|=3<<12|3<<0;   	//OC1,,4 低电平有效 OC1,4 输出使能
	TIM1->BDTR|=1<<15;//主输出使能

	TIM1->CR1=0x0080;   	//ARPE使能
	TIM1->CR1|=0x01;    	//使能定时器5
}

//TIM8 CH1,2,3,4 PWM输出设置
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM8_PWM_Init(u16 arr,u16 psc)
{
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<4|1<<13;    	//TIM8时钟使能,使能PORTC时钟

	GPIOC->CRL&=0X00FFFFFF;	//PC6,7输出
	GPIOC->CRL|=0XBB000000;	//复用功能输出
	GPIOC->CRH&=0XFFFFFF00;	//PC8,9输出
	GPIOC->CRH|=0X000000BB;	//复用功能输出

	TIM8->ARR=arr;			//设定计数器自动重装值
	TIM8->PSC=psc;			//预分频器分频设置

	TIM8->CCMR1|=7<<4 | 7<<12;  	//CH1和CH2 PWM2模式
	TIM8->CCMR1|=1<<3 | 1<<11; 		//CH1和CH2 预装载使能
	TIM8->CCMR2|=7<<4 | 7<<12;  	//CH3和CH4 PWM2模式
	TIM8->CCMR2|=1<<3 | 1<<11; 		//CH3和CH4 预装载使能

	TIM8->CCER|=0x3<<12|0x3<<8|0x3<<4|0x3<<0;   	//OC1,,2,3,4 低电平有效 OC1,2,3,4 输出使能
	TIM8->BDTR|=1<<15;//主输出使能

	TIM8->CR1=0x0080;   	//ARPE使能
	TIM8->CR1|=0x01;    	//使能定时器8
}


