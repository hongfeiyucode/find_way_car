#include "sys.h"
#include "usart3.h"	  
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	   
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//串口3初始化代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/5/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
//无
////////////////////////////////////////////////////////////////////////////////// 	


//串口发送缓存区 	
__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节

//USART3_RX_BYTE存放串口接收到的数据
u8 USART3_RX_BYTE=0xFF;   	 
void USART3_IRQHandler(void)
{
	if(USART3->SR&(1<<5))//接收到数据
	{	 
		USART3_RX_BYTE=USART3->DR; 			 
	}  				 											 
}   
//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void usart3_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV,OVER8设置为0
	mantissa=temp;				 	//得到整数部分
	fraction=(temp-mantissa)*16; 	//得到小数部分,OVER8设置为0	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<1;   			//使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  			//使能串口3时钟 
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PB10,PB11,复用功能,上拉输出
 	GPIO_AF_Set(GPIOB,10,7);		//PB10,AF7
	GPIO_AF_Set(GPIOB,11,7);		//PB11,AF7  	   
	//波特率设置
 	USART3->BRR=mantissa; 			// 波特率设置	 
	USART3->CR1|=1<<3;  			//串口发送使能  
	USART3->CR1|=1<<2;  			//串口接收使能
	USART3->CR1|=1<<5;    			//接收缓冲区非空中断使能	
	USART3->CR1|=1<<13;  			//串口使能  
	MY_NVIC_Init(0,0,USART3_IRQn,2);//组2，优先级0,0,最高优先级 
	TIM7_Int_Init(100-1,8400-1);	//10ms中断一次
	TIM7->CR1&=~(1<<0);				//关闭定时器7
}

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
		while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
		USART3->DR=USART3_TX_BUF[j];  
	}
}



































