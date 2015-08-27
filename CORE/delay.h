

#ifndef _DELAY_H
#define _DELAY_H
 #include "sys.h"

 //系统参数，必须配置
 #define F_CPU      8//外部晶振频率，单位MHz,非整数时会自动取整数部分
 #define SYS_CLK    72//系统时钟，单位MHz


 void delay_init(void);//函数：初始化
 void delay_us(u32 us);//函数：微秒延迟
 void delay_ms(u16 ms);//函数：毫秒延迟

#endif
