#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "ch450i2c.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序由侯工编辑，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//外部中断驱动代码	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern char KeyNumber;   //用来存储按键代码
extern char NewKey;      //用来标识有新的按键加入
//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOF_CLK_ENABLE();               //开启GPIOF时钟


    
    GPIO_Initure.Pin=GPIO_PIN_2;               //PF2
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
       
    //中断线2-PF2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //使能中断线2
    
}


//中断服务函数
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//调用中断处理公用函数
	  KeyNumber=ch450_ReadKey();
	  
}



//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //消抖
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            if(WK_UP==1) 
            {
				LED1=!LED1;//控制LED0,LED1互斥点亮
				LED0=!LED1;
            }
            break;
        case GPIO_PIN_2:
            if(KEY1==0)  //LED1翻转
            {
                LED1=!LED1;    
            }
            break;
        case GPIO_PIN_3:
            if(KEY0==0)  //同时控制LED0,LED1翻转 
            {
                LED0=!LED0;
				LED1=!LED1;
            }
            break;

        case GPIO_PIN_13:
            if(KEY2==0)  
            {
				LED0=!LED0;//控制LED0翻转
            }
            break;
    }
}
