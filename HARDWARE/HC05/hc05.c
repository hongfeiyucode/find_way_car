#include "delay.h" 			 
#include "usart.h" 			 
#include "usart3.h" 			 
#include "hc05.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ATK-HC05蓝牙模块驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/10/26
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
//********************************************************************************
//无修改信息							  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化ATK-HC05模块
//返回值:0,成功;1,失败.
u8 HC05_Init(void)
{
	u8 retry=10,t;	  		 
	u8 temp=1;
	RCC->AHB1ENR|=1<<2;//使能PORTC时钟 
	RCC->AHB1ENR|=1<<5;//使能PORTF时钟 
	GPIO_Set(GPIOC,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PC0 输入 上拉
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF6 输出 高电平
 	usart3_init(42,9600);//初始化串口3为:9600,波特率.
	while(retry--)
	{
		HC05_KEY=1;					//KEY置高,进入AT模式
		delay_ms(10);
		u3_printf("AT\r\n");		//发送AT测试指令
		HC05_KEY=0;					//KEY拉低,退出AT模式
	}		    
	if(retry==0)temp=1;	//检测失败
	return temp;	 
}	 









