#include "uart.h"
#include "stdarg.h"
#include "stdio.h"

//clk 为PLK2时钟，单位MHz；bound：波特率

void uart1_init(u32 clk, u32 bound) //串口一初始化
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float) (clk * 1000000) / (bound * 16);
	mantissa = temp;		 //取整数部分
	fraction = (temp - mantissa) * 16;		 //取小数部分
	mantissa <<= 4;
	mantissa += fraction;

	RCC ->APB2ENR |= 1 << 2 | 1 << 14;		 //使能PA,usart1时钟
	RCC->APB2ENR|=0x01;//使能io复用时钟
	GPIOA ->CRH &= 0XFFFFF00F;		 //设置io口
	GPIOA ->CRH |= 0X000008B0;

	RCC ->APB2RSTR |= 1 << 14;		 //复位USART1
	RCC ->APB2RSTR &= ~(1 << 14);		 //停止复位USART1

	USART1 ->BRR = mantissa;		 //波特率设置
	USART1 ->CR1 |= 1 << 2 | 1 << 3 | 1 << 5 | 1 << 13;	//1停止位，8位数据，无校检,使能接收缓存区非空中断
	//nvic_set_group(2);
	// nvic_set_pr(2,USART1_IRQn,1,0);
}

void uart2_init(u32 clk, u32 bound)	//串口二初始化
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float) (clk * 1000000) / (bound * 16);
	mantissa = temp;		 //取整数部分
	fraction = (temp - mantissa) * 16;		 //取小数部分
	mantissa <<= 4;
	mantissa += fraction;
	RCC->APB2ENR|=0x01;//使能io复用时钟

	RCC ->APB1ENR |= 1 << 17;		 //使能PAusart2时钟
//	RCC ->APB2ENR |= 1 << 2;		 //使能PA时钟
//	GPIOA ->CRL &= 0XFFFF00FF;		 //设置io口
//	GPIOA ->CRL |= 0X00008B00;
	RCC ->APB2ENR |= 1 << 5;		 //使能PD时钟
	GPIOD ->CRL &= 0XF00FFFFF;		 //设置io口
	GPIOD ->CRL |= 0X0BB00000;
	AFIO->MAPR|=1<<3;      //完全重映像


	RCC ->APB1RSTR |= 1 << 17;		 //复位USART1
	RCC ->APB1RSTR &= ~(1 << 17);		 //停止复位USART1

	USART2 ->BRR = mantissa;		 //波特率设置
	USART2 ->CR1 |= 1 << 2 | 1 << 3 | 1 << 13;	//1停止位，8位数据，无校检
}

void uart3_init(u32 clk, u32 bound) //串口一初始化
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float) (clk * 1000000) / (bound * 16);
	mantissa = temp;		 //取整数部分
	fraction = (temp - mantissa) * 16;		 //取小数部分
	mantissa <<= 4;
	mantissa += fraction;

	RCC ->APB1ENR |= 1 << 18;		 //使能PAusart3时钟
	RCC->APB2ENR|=0x01;//使能io复用时钟

//	RCC ->APB2ENR |= 1 << 3 ;		 //使能PB,usart3时钟
//	GPIOB ->CRH &= 0XFFFF00FF;		 //设置io口
//	GPIOB ->CRH |= 0X0000BB00;
//	GPIOB->ODR |= 3<<10;

	RCC ->APB2ENR |= 1 << 5;		 //使能PD时钟
	GPIOD ->CRH &= 0XFFFFFF00;		 //设置io口
	GPIOD ->CRH |= 0X000000BB;
	AFIO->MAPR&= ~(3<<4); //清除MAPR的[9:8]
	AFIO->MAPR|=3<<4;      //完全重映像

	RCC ->APB1RSTR |= 1 << 18;		 //复位USART1
	RCC ->APB1RSTR &= ~(1 << 18);		 //停止复位USART1

	USART3 ->BRR = mantissa;		 //波特率设置
	USART3 ->CR1 |= 1 << 2 | 1 << 3 | 1 << 5 | 1 << 13;	//1停止位，8位数据，无校检,使能接收缓存区非空中断
	//nvic_set_group(2);
	// nvic_set_pr(2,USART1_IRQn,1,0);
}

void uart1_send_char(u8 data) {
	USART1 ->DR = data; //发送数据
	while (!(USART1 ->SR & 0X40))
		;	//等待数据发送完毕
}

void uart2_send_char(u8 data) {
	USART2 ->DR = data; //发送数据
	while (!(USART2 ->SR & 0X40))
		;	//等待数据发送完毕
}

void uart2_send_str(const char *p){
	while('\0' != *p){
		USART2 ->DR = *p++; //发送数据
		while (!(USART2 ->SR & 0X40))
			;	//等待数据发送完毕
	}
}

void uart3_send_char(u8 data) {
	USART3->DR = data; //发送数据
	while (!(USART3->SR & 0X40))
		;	//等待数据发送完毕
}




u8 uart1_receive(void)	//接收一个字符
{
	while (!(USART1->SR & 1 << 5))
		;	//等待接收到数据
	return USART1->DR;
}

u8 uart2_receive(void)	//接收一个字符
{
	while (!(USART2->SR & 1 << 5))
		;	//等待接收到数据
	return USART2->DR;
}
u8 uart3_receive(void)	//接收一个字符
{
	while (!(USART3 ->SR & 1 << 5))
		;	//等待接收到数据
	return USART3->DR;
}

//u8 uart1_buf[USART_REC_MAX];// __attribute__((setion(".app_ram")));//接收缓存区,最大USART_REC_MAX
//u16 uart1_cnt = 0;	//接收到的字节数
//
//void USART1_IRQHandler(void) {
//	if (USART1 ->SR & 1 << 5) {	//接收到数据
//		uart1_buf[uart1_cnt++] = USART1 ->DR; //数据存入缓存
//	}
//}

void uart_printf(char *str, ...) {
	char buf[128];
	unsigned char i = 0;
	va_list ptr;
	va_start(ptr, str);
	vsprintf(buf, str, ptr);
	while (buf[i]) {
		while (!(USART1->SR & 0X40))
			;	//等待数据发送完毕
		USART1->DR = buf[i];
		i++;
	}
	while (!(USART1->SR & 0X40))
	;	//等待数据发送完毕
}
