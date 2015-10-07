

#include "steering.h"
#include "timer.h"
#include "delay.h"
#include "stmflash.h"
#include "uart.h"


#define STEERING_DATA_ADDR  0X0807F800
#define STEERING_INIT_MARK  0X55AA
//默认初始化角度
static int default_init[22]={90,112,64,150,255,
						66,90,240,294,61,
						90,90,90,90,90,
						90,90,90,90,90,
						90,90};

static struct steering_type{
	int mark;
	int init[22];
}steering_data;

void Steering_Init(void){
	STMFLASH_Read(STEERING_DATA_ADDR, (u16*)(&steering_data), sizeof(struct steering_type));
	TIM2_PWM_Init(20000,71);
	TIM3_PWM_Init(20000,71);
	TIM5_PWM_Init(20000,71);
	TIM1_PWM_Init(20000,71);
	TIM8_PWM_Init(20000,71);
	TIM4_PWM_Init(20000,71);
	if(STEERING_INIT_MARK==steering_data.mark)
		Steering_Move(steering_data.init);
	else
		Steering_Move(default_init);
}


//设置22个舵机角度
void Steering_Move(const int	*p){

	STEERING_1(p[0]);
	STEERING_2(p[1]);
	STEERING_3(p[2]);
	STEERING_4(p[3]);
	STEERING_5(p[4]);
	STEERING_6(p[5]);
	STEERING_7(p[6]);
	STEERING_8(p[7]);
	STEERING_9(p[8]);
	STEERING_10(p[9]);
	STEERING_11(p[10]);
	STEERING_12(p[11]);
	STEERING_13(p[12]);
	STEERING_14(p[13]);
	STEERING_15(p[14]);
	STEERING_16(p[15]);
	STEERING_17(p[16]);
	STEERING_18(p[17]);
	STEERING_19(p[18]);
	STEERING_20(p[19]);
	STEERING_21(p[20]);
	STEERING_22(p[21]);
}


//设置舵机角度
//param[0]:舵机标号,param[1]:舵机角度高八位,param[2]:舵机角度低八位
void steering_set(const unsigned char *param){
	unsigned dec;
	dec=param[1];
	dec=dec<<8|param[2];

	switch(param[0]){
	case 1:STEERING_1(dec);break;
	case 2:STEERING_2(dec);break;
	case 3:STEERING_3(dec);break;
	case 4:STEERING_4(dec);break;
	case 5:STEERING_5(dec);break;
	case 6:STEERING_6(dec);break;
	case 7:STEERING_7(dec);break;
	case 8:STEERING_8(dec);break;
	case 9:STEERING_9(dec);break;
	case 10:STEERING_10(dec);break;
	case 11:STEERING_11(dec);break;
	case 12:STEERING_12(dec);break;
	case 13:STEERING_13(dec);break;
	case 14:STEERING_14(dec);break;
	case 15:STEERING_15(dec);break;
	case 16:STEERING_16(dec);break;
	case 17:STEERING_17(dec);break;
	case 18:STEERING_18(dec);break;
	case 19:STEERING_19(dec);break;
	case 20:STEERING_20(dec);break;
	case 21:STEERING_21(dec);break;
	case 22:STEERING_22(dec);break;
	default:;break;
	}
}


//获取22个舵机角度
void steering_get(int *p){
	p[0]=GET_STEERING_1();
	p[1]=GET_STEERING_2();
	p[2]=GET_STEERING_3();
	p[3]=GET_STEERING_4();
	p[4]=GET_STEERING_5();
	p[5]=GET_STEERING_6();
	p[6]=GET_STEERING_7();
	p[7]=GET_STEERING_8();
	p[8]=GET_STEERING_9();
	p[9]=GET_STEERING_10();
	p[10]=GET_STEERING_11();
	p[11]=GET_STEERING_12();
	p[12]=GET_STEERING_13();
	p[13]=GET_STEERING_14();
	p[14]=GET_STEERING_15();
	p[15]=GET_STEERING_16();
	p[16]=GET_STEERING_17();
	p[17]=GET_STEERING_18();
	p[18]=GET_STEERING_19();
	p[19]=GET_STEERING_20();
	p[20]=GET_STEERING_21();
	p[21]=GET_STEERING_22();

}

//设置22个舵机初始位置
void steering_set_init(void){
	steering_data.mark=STEERING_INIT_MARK;//标志以设置初始位置
	steering_get(steering_data.init);
	STMFLASH_Write(STEERING_DATA_ADDR, (u16*)(&steering_data), sizeof(struct steering_type));
}

//打印舵机角度
void steering_show(void){
	int i;
	int data[22];

	steering_get(data);
	uart_printf("\r\n");
	for(i=0 ;i<22 ;i++)
		uart_printf("%d:%d\r\n", i+1, data[i]);
}




