

#include "hc_sr04.h"

//#define DEBUG
//#undef PDEBUG//防止这个已经被定义
//#ifdef DEBUG
//    #include "uart.h"
//	#define PDEBUG(fmt,args...) uart_printf(fmt,##args)
//#else
//	#define PDEBUG(fmt,args...)//不调试
//#endif

//外部中断4服务程序
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR && 1<<10){	 //
		EXTI->PR = 1<<10;
	}else if(EXTI->PR && 1<<11){	 //
		EXTI->PR = 1<<11;
	}else if(EXTI->PR && 1<<12){	 //
		EXTI->PR = 1<<12;
	}else if(EXTI->PR && 1<<13){	 //
		EXTI->PR = 1<<13;
	}	else if(EXTI->PR && 1<<14){	 //
		EXTI->PR = 1<<14;
	}else if(EXTI->PR && 1<<15){	 //
		EXTI->PR = 1<<15;
	}

}



void hc_sr04_init(void){

	Ex_NVIC_Config(3,10,3); 			//上升沿触发
	Ex_NVIC_Config(3,11,3); 			//下降沿触发
	Ex_NVIC_Config(3,12,3); 			//下降沿触发
 	Ex_NVIC_Config(3,13,3); 			//下降沿触发
	Ex_NVIC_Config(3,14,3); 			//下降沿触发
 	Ex_NVIC_Config(3,15,3); 			//下降沿触发
	nvic_set_pr(1,EXTI15_10_IRQn ,1,1);//抢占1，子优先级1，组2
}
