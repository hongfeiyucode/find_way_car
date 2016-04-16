#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	 
	{
		BEEP=!BEEP; 
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY2==0)	  
	{	 
		LED0=!LED0; 			 
	}		 
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0)	 
	{
		LED1=!LED1;
	}		 
	EXTI->PR=1<<3;  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY0==0)	 
	{		
		LED0=!LED0;	
		LED1=!LED1;		
	}		 
	EXTI->PR=1<<4;  //清除LINE4上的中断标志位  
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_E,2,FTIR); 		//下降沿触发
	Ex_NVIC_Config(GPIO_E,3,FTIR); 		//下降沿触发
	Ex_NVIC_Config(GPIO_E,4,FTIR); 		//下降沿触发
 	Ex_NVIC_Config(GPIO_A,0,RTIR); 	 	//上升沿触发 
	MY_NVIC_Init(3,2,EXTI2_IRQn,2);		//抢占3，子优先级2，组2
	MY_NVIC_Init(2,2,EXTI3_IRQn,2);		//抢占2，子优先级2，组2	   
	MY_NVIC_Init(1,2,EXTI4_IRQn,2);		//抢占1，子优先级2，组2	   
	MY_NVIC_Init(0,2,EXTI0_IRQn,2);		//抢占0，子优先级2，组2	   
}












