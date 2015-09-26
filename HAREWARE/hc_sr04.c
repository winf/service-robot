

#include "hc_sr04.h"
#include "delay.h"

//#define DEBUG
//#undef PDEBUG//防止这个已经被定义
//#ifdef DEBUG
//    #include "uart.h"
//	#define PDEBUG(fmt,args...) uart_printf(fmt,##args)
//#else
//	#define PDEBUG(fmt,args...)//不调试
//#endif

#define START_TIMER 	do{\
							TIM7->CNT=0;\
							TIM7->CR1|=0x01; \
						}while(0)

#define STOP_TIMER 	do{\
							TIM7->CR1 &= ~0x01; \
						}while(0)
#define TIMER_CNT		TIM7->CNT

static void TIM7_Init(u16 arr,u16 psc);







void hc_sr04_init(void){

    RCC->APB2ENR|=1<<5;//PD时钟
	GPIOD->CRH&=0X000000FF;//PD10--15上拉输入;
	GPIOD->CRH|=0X88888800;
	GPIOD->ODR |= 0X3F<<10;

	GPIOD->CRL&=0XFF000000;//PD0--5推挽输出;
	GPIOD->CRL|=0X00333333;
	GPIOD->ODR &= ~(0X3F);


	TIM7_Init(0XFFFF,71);//72M,频率为1M,即计数器每加一为1us
}


//通用定时器6中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器6!
static void TIM7_Init(u16 arr,u16 psc){
	RCC->APB1ENR|=1<<5;	//TIM7时钟使能
 	TIM7->ARR=arr;  	//设定计数器自动重装值//刚好1ms
	TIM7->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟
//	TIM7->DIER|=1<<0;   //允许更新中断
//	TIM7->CR1|=0x01;    //使能定时器3
//	nvic_set_pr(2,TIM7_IRQn,1,1);//抢占1，子优先级1，组2
}


//返回值距离,单位毫米
unsigned int hc_sr04_measure(volatile unsigned long  *TRIG, volatile unsigned long  *ECHO){
	unsigned i=0;

	*TRIG=1;//控制端置高
	delay_us(10);//延时12us
	*TRIG=0;//控制端置低
	TIMER_CNT=0;
	while(!(*ECHO)){//等待输入端高电平到来
	 i++;
	 if(i>10000) goto END;//超时直接结束
	}
	START_TIMER;//开timer
	while((*ECHO)){//等待输入端低电平
		if(TIMER_CNT >27000 ) break;//超出测量范围，跳出测量
	 }
	STOP_TIMER;//关timer
	END:;
	return TIMER_CNT*340/2/1000;
}



