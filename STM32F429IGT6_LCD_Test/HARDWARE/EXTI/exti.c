#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "ch450i2c.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�������ɺ�༭��δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//�ⲿ�ж���������	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern char KeyNumber;   //�����洢��������
extern char NewKey;      //������ʶ���µİ�������
//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOF_CLK_ENABLE();               //����GPIOFʱ��


    
    GPIO_Initure.Pin=GPIO_PIN_2;               //PF2
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
       
    //�ж���2-PF2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
}


//�жϷ�����
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//�����жϴ����ú���
	  KeyNumber=ch450_ReadKey();
	  
}



//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //����
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            if(WK_UP==1) 
            {
				LED1=!LED1;//����LED0,LED1�������
				LED0=!LED1;
            }
            break;
        case GPIO_PIN_2:
            if(KEY1==0)  //LED1��ת
            {
                LED1=!LED1;    
            }
            break;
        case GPIO_PIN_3:
            if(KEY0==0)  //ͬʱ����LED0,LED1��ת 
            {
                LED0=!LED0;
				LED1=!LED1;
            }
            break;

        case GPIO_PIN_13:
            if(KEY2==0)  
            {
				LED0=!LED0;//����LED0��ת
            }
            break;
    }
}
