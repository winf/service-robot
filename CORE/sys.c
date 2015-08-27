
#include "sys.h"
#include "uart.h"

void sys_init(void)	//系统初始化
{
 rcc_init();//复位并配置向量表
 RCC->CR|=1<<16;//外部高速时钟HSEON使能
 while(!(RCC->CR&(1<<17)));//等待外部时钟就绪
 RCC->CFGR|=1<<10|(PLL-2)<<18|1<<16;//PLLSRC ON,设倍频,HSE作为PLL输入时钟,APB1时钟为HCLK2分频
 FLASH->ACR|=0x32;//FLASH两个延时周期 ,工作在72MHz必须有2个等待周期

 RCC->CR|=1<<24;//PLLON
 while(!(RCC->CR&(1<<25)));//等待pll锁定
 RCC->CFGR|=1<<1;//PLL作为系统时钟
 while(!(RCC->CFGR&(1<<3)));//等待pll作为系统时钟设置成功
// nvic_set_group(2);//设置中断分组为2
}

void rcc_init(void)//复位所有时钟
{
 RCC->APB1RSTR=0X00000000;//复位结束
 RCC->APB2RSTR=0X00000000;

 RCC->AHBENR=0X00000014;//睡眠模式闪存和SRAM时钟使能，其他关闭
 RCC->APB1ENR=0X00000000;//外设时钟关闭
 RCC->APB2ENR=0X00000000;
 RCC->CR|=1<<0;//使能内部高速时钟
 
 RCC->CFGR&=0XF8FF0000;//复位SW[1：0]等
 RCC->CR&=~(1<<16|1<<18|1<<19|1<<24); //复位HSEON,PLLON,CSSON
 RCC->CFGR&=0XFF80FFFF;//复位PLLSRC等
#ifdef VECT_TAB_RAM
 SCB->VTOR=NVIC_VectTab_RAM|(0x0&(u32)0x1fffff80);					 //设置向量表偏移地址
#else
 SCB->VTOR=NVIC_VectTab_FLASH|(0x0&(u32)0x1fffff80);					 //设置向量表偏移地址
#endif
}



//进入待机模式
void sys_standby(void)
{
 SCB->SCR|=1<<2;//使能SLEEPDEEP位（SYS->CTRL）
 RCC->APB1ENR|=1<<28;//使能电源时钟
 PWR->CSR|=1<<8;//设置WKUP用于唤醒
 PWR->CR|=1<<1|1<<2;//PDDS置位，清除wake-up标志
 WFI_SET;//执行WFI指令
}

void jtag_set(u8 mode)//设置jtag模式
{
 u32 temp;
 temp=mode;
 temp<<=24;
 RCC->APB2ENR|=1<<0;//开启辅助时钟
 AFIO->MAPR&=~(1<<24|1<<25|1<<26);//清除MAPR[26：24]
 AFIO->MAPR|=temp;//设置jtag模式
}

void nvic_set_group(u8 group)//设置中断分组
{
 u32 temp,temp1; 
 temp1=(~group)&0x07;  // 设为中断分组 ，取后三位
 temp1<<=8;      
 temp=SCB->AIRCR;        //读取先前分区
 temp&=0X0000F8FF;       //清空先前分组
 temp|=0X05FA0000;     	 //写入钥匙
 temp|=temp1;              
 SCB->AIRCR=temp;		  //设置分组
}


 //group:中断所分的组，interrupt：中断号，priority1：抢占优先级，priority2子优先级
void nvic_set_pr(u8 group,u8 interrupt,u8 priority1,u8 priority2 )//设置中断的优先级
{
 u32 temp; 
 if(interrupt<32) NVIC->ISER[0]|=1<<interrupt;//开中断
 else  NVIC->ISER[1]|=1<<(interrupt-32);
 temp=priority1<<(4-group);                	//抢占优先级为
 temp|=priority2&(0x0f>>group);      		//响应优先级为
 temp&=0xf;//取低四位
 NVIC->IP[interrupt/4]|=temp<<((interrupt%4)*8+4);//四个一组，每个八位，只用高四位,设置中断的优先级
}

//因为这里默认放置的第一个变量值放置在r0寄存器,两句汇编之间用\n\t分隔
void MSR_MSP( u32 addr)
{
	 asm(
	 "msr msp,r0\n\t"
	 "bx r14"
	);
}


