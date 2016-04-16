#include "timer.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
//V1.1 20140504
//新增TIM14_PWM_Init函数,用于PWM输出
//V1.2 20140504
//新增TIM5_CH1_Cap_Init函数,用于输入捕获
//V1.3 20141026
//新增TIM7_Int_Init函数
////////////////////////////////////////////////////////////////////////////////// 	 


//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		LED1=!LED1;			    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为42M
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值 
	TIM3->PSC=psc;  	//预分频器	  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);	//抢占1，子优先级3，组2									 
}

//TIM10 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM10_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<17; 	//TIM10时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	GPIO_Set(GPIOF,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,6,3);	//PF6,AF3 
	
	TIM10->ARR=arr;			//设定计数器自动重装值 
	TIM10->PSC=psc;			//预分频器不分频 
	TIM10->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM10->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM10->CCER|=1<<0;   	//OC1 输出使能	
	TIM10->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM10->CR1|=1<<7;   	//ARPE使能 
	TIM10->CR1|=1<<0;    	//使能定时器10 		
	TIM10->CCR1 = arr;
}  

//TIM11 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM11_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<18; 	//TIM11时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	GPIO_Set(GPIOF,PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,7,3);	//PF7,AF3 
	
	TIM11->ARR=arr;			//设定计数器自动重装值 
	TIM11->PSC=psc;			//预分频器不分频 
	TIM11->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM11->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM11->CCER|=1<<0;   	//OC1 输出使能	
	TIM11->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM11->CR1|=1<<7;   	//ARPE使能 
	TIM11->CR1|=1<<0;    	//使能定时器11 											  
	TIM11->CCR1 = arr;
}  

//TIM13 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM13_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<7; 	//TIM13时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,8,9);	//PF8,AF9 
	
	TIM13->ARR=arr;			//设定计数器自动重装值 
	TIM13->PSC=psc;			//预分频器不分频 
	TIM13->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM13->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM13->CCER|=1<<0;   	//OC1 输出使能	
	TIM13->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM13->CR1|=1<<7;   	//ARPE使能 
	TIM13->CR1|=1<<0;    	//使能定时器13 											  
	TIM13->CCR1 = arr;
}  

//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<8; 	//TIM14时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	GPIO_Set(GPIOF,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,9,9);	//PF9,AF9 
	
	TIM14->ARR=arr;			//设定计数器自动重装值 
	TIM14->PSC=psc;			//预分频器不分频 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM14->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM14->CCER|=1<<0;   	//OC1 输出使能	
	TIM14->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM14->CR1|=1<<7;   	//ARPE使能 
	TIM14->CR1|=1<<0;    	//使能定时器14 											  
	TIM14->CCR1 = arr;
}  

//定时器2通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<3;   	//TIM5 时钟使能 
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN0,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,下拉
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	  
 	TIM5->ARR=arr;  		//设定计数器自动重装值   
	TIM5->PSC=psc;  		//预分频器 

	TIM5->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM5->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM5->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 

	TIM5->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM5->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM5->EGR=1<<0;			//软件控制产生更新事件,使写入PSC的值立即生效,否则将会要等到定时器溢出才会生效!
	TIM5->DIER|=1<<1;   	//允许捕获1中断				
	TIM5->DIER|=1<<0;   	//允许更新中断	
	TIM5->CR1|=0x01;    	//使能定时器2
	MY_NVIC_Init(2,0,TIM5_IRQn,2);//抢占2，子优先级0，组2	   
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM5->SR;
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//获取当前的捕获值.
	 			TIM5->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM5->CR1&=~(1<<0)		;    	//使能定时器2
	 			TIM5->CNT=0;					//计数器清空
	 			TIM5->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
				TIM5->CR1|=0x01;    			//使能定时器2
			}		    
		}			     	    					   
 	}
	TIM5->SR=0;//清除中断标志位   
}

extern vu16 USART3_RX_STA;
//定时器7中断服务程序		    
void TIM7_IRQHandler(void)
{ 	  		    
	if(TIM7->SR&0X01)//是更新中断
	{	 			   
		TIM7->SR&=~(1<<0);		//清除中断标志位		   
		TIM7->CR1&=~(1<<0);		//关闭定时器7	  
	}	      											 
} 
//通用定时器7中断初始化
//这里时钟选择为APB1的2倍，而APB1为42M
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz 
void TIM7_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<5;	//TIM7时钟使能    
 	TIM7->ARR=arr;  	//设定计数器自动重装值 
	TIM7->PSC=psc;  	//预分频器	  
	TIM7->CNT=0;  		//计数器清零	  
	TIM7->DIER|=1<<0;   //允许更新中断	  
	TIM7->CR1|=0x01;    //使能定时器7
  	MY_NVIC_Init(0,1,TIM7_IRQn,2);	//抢占0，子优先级1，组2									 
} 












