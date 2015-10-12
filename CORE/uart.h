

#ifndef _UART_H
#define _UART_H

#include "sys.h"
#include "stdio.h"

#define USART_REC_MAX  			1//55*1024  	//定义最大接收字节数 200



extern u8 uart1_buf[USART_REC_MAX];//接收缓存区
extern u16 uart1_cnt;//接收到的字节数

 void uart1_init(u32 pclk2,u32 bound);//初始化串口一
 void uart2_init(u32 clk,u32 bound);//串口二初始化
 void uart3_init(u32 clk,u32 bound);//初始化串口一
 void uart1_send_char(u8 data);//发送一个字节
 void uart2_send_char(u8 data);//发送一个字节
 void uart3_send_char(u8 data);//发送一个字节
 void uart2_send_str(const char *p); //发送字符串
 u8 uart1_receive(void);//接收一个字符
 u8 uart2_receive(void);//接收一个字符
 u8 uart3_receive(void);//接收一个字符
 void uart_printf(char *str,...);


#endif
