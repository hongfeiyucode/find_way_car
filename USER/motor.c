

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//直流电机 驱动代码	   
//wlx
//创建日期:2016/1/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) wlx 2016-2026
//All rights reserved
//********************************************************************************
//说明
//V1.0 20160116
//驱动两个直流电机前后运转
////////////////////////////////////////////////////////////////////////////////// 	 

#define MOTOR_LEFT_L 0  
#define MOTOR_LEFT_H 1   

#define MOTOR_RIGHT_L 2  
#define MOTOR_RIGHT_H 3  

#include "sys.h"
#include "timer.h"
#include "motor.h"

u32 g_timer_arr = 500-1;   //设定计数器自动重装值 

TIM_TypeDef * PWM_BASE[4] = {	TIM10, TIM11, TIM13, TIM14};

void pwm_start(u32 pwm)
{
	PWM_BASE[pwm]->CCR1 = 100;
}

void pwm_s(u32 pwm,u32 a)
{
	PWM_BASE[pwm]->CCR1 = a;
}

void pwm_stop(u32 pwm)
{
	PWM_BASE[pwm]->CCR1 = g_timer_arr;
}

void l_motor_forward()
{
	pwm_start(MOTOR_LEFT_H);
	pwm_stop(MOTOR_LEFT_L);
}

void l_motor_backward()
{
	pwm_start(MOTOR_LEFT_L);
	pwm_stop(MOTOR_LEFT_H);
}

void l_motor_stop()
{
	pwm_stop(MOTOR_LEFT_H);
	pwm_stop(MOTOR_LEFT_L);
}

void r_motor_forward()
{
	pwm_start(MOTOR_RIGHT_H);
	pwm_stop(MOTOR_RIGHT_L);
}

void r_motor_backward()
{
	pwm_start(MOTOR_RIGHT_L);
	pwm_stop(MOTOR_RIGHT_H);
}

void r_motor_stop()
{
	pwm_stop(MOTOR_RIGHT_H);
	pwm_stop(MOTOR_RIGHT_L);
}

void car_forward()
{
	l_motor_forward();
	r_motor_forward();
}

void car_backward()
{
	l_motor_backward();
	r_motor_backward();
}

void car_left()
{
	l_motor_stop();
	r_motor_forward();
}

void car_right()
{
	l_motor_forward();
	r_motor_stop();
}

void car_stop()
{
	l_motor_stop();
	r_motor_stop();
}

void pwm_init()
{
	TIM10_PWM_Init(g_timer_arr,84-1);	//1Mhz的计数频率,2Khz的PWM.     
	TIM11_PWM_Init(g_timer_arr,84-1);	//1Mhz的计数频率,2Khz的PWM.     
	TIM13_PWM_Init(g_timer_arr,84-1);	//1Mhz的计数频率,2Khz的PWM.     
	TIM14_PWM_Init(g_timer_arr,84-1);	//1Mhz的计数频率,2Khz的PWM.     
}

void l_motor_s(u32 a)
{
	pwm_s(MOTOR_LEFT_H,a);
	pwm_stop(MOTOR_LEFT_L);
}

void r_motor_s(u32 a)
{
	pwm_s(MOTOR_RIGHT_H,a);
	pwm_stop(MOTOR_RIGHT_L);
}

void car_left_s(u32 a)
{
	l_motor_s(a);
	r_motor_forward();
}

void car_right_s(u32 a)
{
	l_motor_forward();
	r_motor_s(a);
}

void car_left_back(u32 a)
{
	l_motor_backward();
	r_motor_forward();
}

void car_right_back(u32 a)
{
	l_motor_forward();
	r_motor_backward();
}