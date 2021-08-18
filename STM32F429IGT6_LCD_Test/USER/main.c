//////////////////////////////////////////////////////////////////////////////////	 
//�����������ڶ���ϣ��EH100���ػ�
//����Ӳ������Ƭ��STM32F429IGT6,����ԭ��Apollo STM32F4/F7������,��Ƶ180MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 FSMC
//�޸���Arthur_hou (��) ��ϵ��ʽ��dlhou@163.com
//�޸����ڣ�2020.11.9
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com

//All rights reserved
/****************************************************************************************************
//��ģ�����ֱ�Ӳ�������ԭ��Apollo STM32F4/F7������TFTLCD��ۣ������ֶ�����
//STM32����������ָTFTLCD��������ڲ����ӵ�STM32����
//=========================================��Դ����================================================//
//     LCDģ��             TFTLCD�������        STM32��������
//      VDD       --->         5V/3.3              DC5V/3.3V          //��Դ
//      GND       --->          GND                  GND              //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ16λ��������
//     LCDģ��             TFTLCD�������        STM32��������
//      DB0       --->          D0                   PD14        -|   
//      DB1       --->          D1                   PD15         |  
//      DB2       --->          D2                   PD0          | 
//      DB3       --->          D3                   PD1          | 
//      DB4       --->          D4                   PE7          |
//      DB5       --->          D5                   PE8          |
//      DB6       --->          D6                   PE9          |
//      DB7       --->          D7                   PE10         |
//���ʹ��8λģʽ���������������û��ʹ��                         |===>Һ����16λ���������ź�
//      DB8       --->          D8                   PE11         |
//      DB9       --->          D9                   PE12         |
//      DB10      --->          D10                  PE13         |
//      DB11      --->          D11                  PE14         |
//      DB12      --->          D12                  PE15         |
//      DB13      --->          D13                  PD8          |
//      DB14      --->          D14                  PD9          |
//      DB15      --->          D15                  PD10        -|
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 				     TFTLCD�������        STM32�������� 
//       WR       --->          WR                   PD5             //Һ����д���ݿ����ź�
//       RD       --->          RD                   PD4             //Һ���������ݿ����ź�
//       RS       --->          RS                   PD13            //Һ��������/��������ź�
//       RST      --->          RST                ��λ����          //Һ������λ�����ź�
//       CS       --->          CS                   PD7             //Һ����Ƭѡ�����ź�
//       BL       --->          BL                   PB5             //Һ������������ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��             TFTLCD�������        STM32�������� 
//      PEN       --->          PEN                  PH7             //�����������ж��ź�
//      MISO      --->          MISO                 PG3             //������SPI���߶��ź�
//      MOSI      --->          MOSI                 PI3             //������SPI����д�ź�
//      T_CS      --->          TCS                  PI8             //������Ƭѡ�����ź�
//      CLK       --->          CLK                  PH6             //������SPI����ʱ���ź�
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/		
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "sdram.h"
#include "eh100.h"

 
 
void LCD_Test();
void Get_Analogs(ANALOG Analogs);                //��ȡ5·�¶ȼ�8·ģ����	
void DealwithAnalogs(ANALOG analog);	
void Get_Temperatures(ANALOG Analogs);       //��ȡ5���ڵ��¶�

char Date;
int main(void)
{	
   HAL_Init();                     //��ʼ��HAL��   
   Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
   delay_init(180);                //��ʼ����ʱ����
	 SDRAM_Init();                   //��ʼ��SDRAM
	 LCD_Init();	                   //Һ������ʼ��
/*	 KEY_Init();                     //������ʼ��
	 SD_Init();                      // SD����ʼ��
	 USART_Init();                   // ����1�ʹ���2��ʼ�������ʶ�Ϊ115200
	 NETWORK_Init();                 //����˿ڳ�ʼ��
	 DS1302_Init();                  //ʱ���ʼ��
//	 RTC_Init();                     //ʱ���ʼ�� 
	 Temperatur1_5_Init();            // 5·�¶Ƚ׽ڵ��ʼ��
	 ANALOG1_8_Init();                // 8·ģ������ʼ��
	 DraughtFan_Init();               //�����ʼ��
	 SWITCH1_5_Init();                //5·��������ʼ��
	 Alarm_Init();                    //1·������ʼ��
	 RELAY24_Init();                  //24·�̵�����ʼ��
	 NVIC_Init();                     //��ʼ���ж�����
	*/
	 while(1)
	 {  
		  int KEY_NUM=0;               //����ֵ
		  int LCD_Place=0x0000;        //�˵����λ��   
      Get_Time(Time);              //��ȡʱ��		 
		 // KEY_NUM=KEY_SCAN();          //��ȡ��ֵ
		  if(KEY_NUM��=0)              //����а���
      {
				  switch(KEY_NUM)
					{	
						case 0:
							break;
						case 1:
							break;
						case 2:
							break;
						case 3:
							break;	
					}						
      }				//
      //��ʼ����ϵͳ����
      Get_Time(Time);              //��ȡʱ��		
			//��������б仯����д��ˮ���������ݽ�SD��
			if(Date!=Time.day)
			{
				  USART_Read();                 //��ȡˮ�����ֵ
				  SD_Write_Meters();            //��SD��д��ˮ�����ֵ
			}
			Get_Analogs(Analogs);          //��ȡ5·�¶ȼ�8·ģ����
			DealwithAnalogs(Analogs);     //��5·�¶ȼ�8·ģ�������д���
			ReportData(Time,analogs);     //ÿ1���ӽ��ɼ�����ģ�������͵���λ��������(����ͨ��)
			SD_Write_Analogs(Time,analogs);       //ÿ1���ӽ��ɼ�����ģ��������SD����

			if(alarmNum!=0)            //�б����¼�
			{
				   switch(alarmNum)
					 {
						 case alarmNum&0x01:
							 DealwithEvent(alarmNum&0x01);        //�����¼�1
						   ReportEvent(Time,ALARM1);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM1);        //��¼�¼���SD��
							 alarmNum^0x01;    //�����λ������¼�1��־λ
							break;
						case alarmNum&0x02:
							 DealwithEvent(alarmNum&0x02);    //�����¼�2
						   ReportEvent(Time,ALARM2);     //�㱨�¼�1����λ��������(����ͨ��)							
							 SD_Write(Time,ALARM2); 	
							 alarmNum^0x02;    //�����λ������¼�2��־λ						
							break;
						case alarmNum&0x04:
								 DealwithEvent(alarmNum&0x04);        //�����¼�3
						   ReportEvent(Time,ALARM3);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM3);        //��¼�¼���SD��
							  alarmNum^0x04;    //�����λ������¼�3��־λ				 							
							break;
						case alarmNum&0x08:
									 DealwithEvent(alarmNum&0x08);        //�����¼�4
						   ReportEvent(Time,ALARM4);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM4);        //��¼�¼���SD��
							  alarmNum^0x08;    //�����λ������¼�1��־λ									
							break;
						case alarmNum&0x10:						
							 DealwithEvent(alarmNum&0x10);        //�����¼�5
						   ReportEvent(Time,ALARM5);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM5);        //��¼�¼���SD��
							 alarmNum^0x10;    //�����λ������¼�1��־λ					
							break;		
						case alarmNum&0x20:						
							 DealwithEvent(alarmNum&0x20);        //�����¼�6
						   ReportEvent(Time,ALARM6);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM6);        //��¼�¼���SD��
							 alarmNum^0x20;    //�����λ������¼�1��־λ						
							break;
						case alarmNum&0x40:						
							 DealwithEvent(alarmNum&0x40);        //�����¼�7
						   ReportEvent(Time,ALARM7);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM7);        //��¼�¼���SD��
							 alarmNum^0x40;    //�����λ������¼�1��־λ					
							break;
						case alarmNum&0x80:						
							 DealwithEvent(alarmNum&0x80);        //�����¼�8
						   ReportEvent(Time,ALARM8);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM1);        //��¼�¼���SD��
							 alarmNum^0x01;    //�����λ������¼�1��־λ					
							break;
						case alarmNum&0x100:						
							 DealwithEvent(alarmNum&0x100);        //�����¼�9
						   ReportEvent(Time,ALARM9);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write(Time,ALARM9);        //��¼�¼���SD��
							 alarmNum^0x100;    //�����λ������¼�1��־λ					
							break;		
						case alarmNum&0x200:						
							 DealwithEvent(alarmNum&0x200);        //�����¼�10, ����
						   ReportEvent(Time,ALARM10);     //�㱨�¼�1����λ��������(����ͨ��)
							 SD_Write_Fodder(Time,ALARM10,fodderWeight);        //��¼����������SD��
    					 alarmNum^0x200;    //�����λ������¼�1��־λ						
							break;						
					}						
				
			}
			delay_ms(5000);  //��ʱ5����
			HAL_GPIO_TogglePin(GPIOF,GPIO_Pin_11); //ÿ5����LED0״̬��תһ��
	}
}
void LCD_Test()
{
			main_test(); 		//����������
			Test_Read();     //��ID����ɫֵ����
			Test_Color();  		//��ˢ��������
			Test_FillRec();		//GUI���λ�ͼ����
			Test_Circle(); 		//GUI��Բ����
			Test_Triangle();    //GUI�����λ�ͼ����
			English_Font_test();//Ӣ������ʾ������
			Chinese_Font_test();//��������ʾ������
			Pic_test();			//ͼƬ��ʾʾ������
  		Rotate_Test();   //��ת��ʾ����
		//����������������߲���Ҫ�������ܣ���ע�͵����津����������
			//Touch_Test();		//��������д����  
	
}
void Get_Analogs(ANALOG Analogs)                //��ȡ5·�¶ȼ�8·ģ����
{
	 Get_Temperatures(Analogs);       //��ȡ5���ڵ��¶�
	// Get_Analog8(Analogs);           //��ȡ5·�¶ȼ�8·ģ����
}

void DealwithAnalogs(Analog analog)     //��5·�¶ȼ�8·ģ�������д���
{
	
}

void Get_Temperatures(ANALOG Analogs)       //��ȡ5���ڵ��¶�
{
}