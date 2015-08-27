

#include "delay.h"


static u8  us_each=0;//us延时倍乘数
static u16 ms_each=0;//ms延时倍乘数


//systick时钟固定为HCLK(AHB时钟)1/8
//sysclk：系统时钟



#ifdef OS_CRITICAL_METHOD //如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.

//systick时钟固定为HCLK(AHB时钟)1/8
//sysclk：系统时钟

void delay_init(void)//函数：初始化
{
   u32 reload;
   SysTick->CTRL&=~(1<<2);//使用外部时钟源
   us_each=SYS_CLK/(u8)F_CPU;//SYS_CLK为系统时钟，F_CPU为晶振频率，代表每个us所用系统时钟
   reload = SYS_CLK/8;//得到每微秒的计数单位
   reload *= 1000000/OS_TICKS_PER_SEC;//得到系统溢出时间
   ms_each = 1000/OS_TICKS_PER_SEC;//得到每ms要延时计数次数
   SysTick->CTRL |= 1<<1;//开启SYSTICK中断
   SysTick->LOAD = reload;//每1/OS_TICKS_PER_SEC秒中断一次
   SysTick->CTRL |= 1<<0;//开启SYSTICK
}
//systick中断服务函数，系统心跳
void SysTick_Handler(void)
{
 OSIntEnter();//进入中断
 OSTimeTick();//调用ucos的时钟服务程序
 OSIntExit();//触发任务切换软中断
}


void delay_us(u32 us)//函数：微秒延迟
{
    u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload = SysTick->LOAD;//LOAD的值
	ticks = us * us_each;//需要的节拍数
	OSSchedLock();//阻止ucos调度，防止打断us延时
	told = SysTick->VAL;//刚进入时的计数器值
	while(1){
	   tnow = SysTick->VAL;
	   if( tnow != told){
	      if( tnow < told) tcnt += told-tnow;//SYSTICK是一个递减的计数器
		  else tcnt += reload - tnow + told;
		  told = tnow;
		  if(tcnt >= ticks) break;//时间超过或等于要延迟的时间，则退出
	   }
	}
	OSSchedUnlock();//开启ucos任务调度
}


//在72M条件下，ms<=1864
void delay_ms(u16 ms)//函数：毫秒延迟
{
   if(OSRunning == TRUE){
   	  if(ms >= ms_each)//延时的时间大于ucos的最少时间周期
	    OSTimeDly(ms / ms_each);
	  ms %= ms_each;//ucos已经无法提供这么小的延时了，采用普通延时
   }
   delay_us((u32)(ms*1000));//普通延时
}
#else

void delay_init(void)//函数：初始化
{
   SysTick->CTRL&=~(1<<2);//使用外部时钟源
   us_each=SYS_CLK/(u8)F_CPU;//SYS_CLK为系统时钟，F_CPU为晶振频率，代表每个us所用系统时钟
   ms_each=(u16)us_each*1000;//代表每个ms需要的系统时钟数
}


void delay_us(u32 us)//函数：微秒延迟
{
    u32 temp;
	SysTick->LOAD=us*us_each;//时间加载
	SysTick->VAL=0x00;//清空计数器
	SysTick->CTRL|=1<<0;//开始倒数
	do
	{
	 temp=SysTick->CTRL;
	}while((temp&(1<<0))&&!(temp&(1<<16)));//等待时间到达（SysTick->CTRL第16位硬件置1）,(temp&(1<<0))防止意外锁死,
	SysTick->CTRL&=~(1<<0);//关闭计数器
	SysTick->VAL=0x00;//清空计数器
}


//在72M条件下，ms<=1864
void delay_ms(u16 ms)//函数：毫秒延迟
{
    u32 temp;
	SysTick->LOAD=(u32)ms*ms_each;//时间加载
	SysTick->VAL=0x00;//清空计数器
	SysTick->CTRL|=1<<0;//开始倒数
	do
	{
	 temp=SysTick->CTRL;
	}while((temp&(1<<0))&&!(temp&(1<<16)));//等待时间到达,(temp&(1<<0))防止意外锁死
	SysTick->CTRL&=~(1<<0);//关闭计数器
	SysTick->VAL=0x00;//清空计数器
}
#endif



