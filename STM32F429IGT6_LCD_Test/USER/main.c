//////////////////////////////////////////////////////////////////////////////////	 
//本程序是用于东方希望EH100环控机
//测试硬件：单片机STM32F429IGT6,正点原子Apollo STM32F4/F7开发板,主频180MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 FSMC
//修改者Arthur_hou (侯) 联系方式：dlhou@163.com
//修改日期：2020.11.9
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com

//All rights reserved
/****************************************************************************************************
//此模块可以直接插入正点原子Apollo STM32F4/F7开发板TFTLCD插槽，无需手动接线
//STM32连接引脚是指TFTLCD插槽引脚内部连接的STM32引脚
//=========================================电源接线================================================//
//     LCD模块             TFTLCD插槽引脚        STM32连接引脚
//      VDD       --->         5V/3.3              DC5V/3.3V          //电源
//      GND       --->          GND                  GND              //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为16位并口总线
//     LCD模块             TFTLCD插槽引脚        STM32连接引脚
//      DB0       --->          D0                   PD14        -|   
//      DB1       --->          D1                   PD15         |  
//      DB2       --->          D2                   PD0          | 
//      DB3       --->          D3                   PD1          | 
//      DB4       --->          D4                   PE7          |
//      DB5       --->          D5                   PE8          |
//      DB6       --->          D6                   PE9          |
//      DB7       --->          D7                   PE10         |
//如果使用8位模式，则下面的数据线没有使用                         |===>液晶屏16位并口数据信号
//      DB8       --->          D8                   PE11         |
//      DB9       --->          D9                   PE12         |
//      DB10      --->          D10                  PE13         |
//      DB11      --->          D11                  PE14         |
//      DB12      --->          D12                  PE15         |
//      DB13      --->          D13                  PD8          |
//      DB14      --->          D14                  PD9          |
//      DB15      --->          D15                  PD10        -|
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 				     TFTLCD插槽引脚        STM32连接引脚 
//       WR       --->          WR                   PD5             //液晶屏写数据控制信号
//       RD       --->          RD                   PD4             //液晶屏读数据控制信号
//       RS       --->          RS                   PD13            //液晶屏数据/命令控制信号
//       RST      --->          RST                复位引脚          //液晶屏复位控制信号
//       CS       --->          CS                   PD7             //液晶屏片选控制信号
//       BL       --->          BL                   PB5             //液晶屏背光控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块             TFTLCD插槽引脚        STM32连接引脚 
//      PEN       --->          PEN                  PH7             //触摸屏触摸中断信号
//      MISO      --->          MISO                 PG3             //触摸屏SPI总线读信号
//      MOSI      --->          MOSI                 PI3             //触摸屏SPI总线写信号
//      T_CS      --->          TCS                  PI8             //触摸屏片选控制信号
//      CLK       --->          CLK                  PH6             //触摸屏SPI总线时钟信号
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
void Get_Analogs(ANALOG Analogs);                //获取5路温度及8路模拟量	
void DealwithAnalogs(ANALOG analog);	
void Get_Temperatures(ANALOG Analogs);       //获取5个节点温度

char Date;
int main(void)
{	
   HAL_Init();                     //初始化HAL库   
   Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
   delay_init(180);                //初始化延时函数
	 SDRAM_Init();                   //初始化SDRAM
	 LCD_Init();	                   //液晶屏初始化
/*	 KEY_Init();                     //按键初始化
	 SD_Init();                      // SD卡初始化
	 USART_Init();                   // 串口1和串口2初始化，速率都为115200
	 NETWORK_Init();                 //网络端口初始化
	 DS1302_Init();                  //时间初始化
//	 RTC_Init();                     //时间初始化 
	 Temperatur1_5_Init();            // 5路温度阶节点初始化
	 ANALOG1_8_Init();                // 8路模拟量初始化
	 DraughtFan_Init();               //风机初始化
	 SWITCH1_5_Init();                //5路开关量初始化
	 Alarm_Init();                    //1路报警初始化
	 RELAY24_Init();                  //24路继电器初始化
	 NVIC_Init();                     //初始化中断向量
	*/
	 while(1)
	 {  
		  int KEY_NUM=0;               //按键值
		  int LCD_Place=0x0000;        //菜单项的位置   
      Get_Time(Time);              //获取时间		 
		 // KEY_NUM=KEY_SCAN();          //读取键值
		  if(KEY_NUM！=0)              //如果有按键
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
      //开始正常系统运行
      Get_Time(Time);              //获取时间		
			//如果日期有变化，则写入水表，电表的数据进SD卡
			if(Date!=Time.day)
			{
				  USART_Read();                 //读取水表，电表值
				  SD_Write_Meters();            //向SD卡写入水表，电表值
			}
			Get_Analogs(Analogs);          //获取5路温度及8路模拟量
			DealwithAnalogs(Analogs);     //对5路温度及8路模拟量进行处理
			ReportData(Time,analogs);     //每1分钟将采集到的模拟量传送到上位机服务器(网络通信)
			SD_Write_Analogs(Time,analogs);       //每1分钟将采集到的模拟量存入SD卡中

			if(alarmNum!=0)            //有报警事件
			{
				   switch(alarmNum)
					 {
						 case alarmNum&0x01:
							 DealwithEvent(alarmNum&0x01);        //处理事件1
						   ReportEvent(Time,ALARM1);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM1);        //记录事件到SD卡
							 alarmNum^0x01;    //清除该位，清除事件1标志位
							break;
						case alarmNum&0x02:
							 DealwithEvent(alarmNum&0x02);    //处理事件2
						   ReportEvent(Time,ALARM2);     //汇报事件1到上位机服务器(网络通信)							
							 SD_Write(Time,ALARM2); 	
							 alarmNum^0x02;    //清除该位，清除事件2标志位						
							break;
						case alarmNum&0x04:
								 DealwithEvent(alarmNum&0x04);        //处理事件3
						   ReportEvent(Time,ALARM3);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM3);        //记录事件到SD卡
							  alarmNum^0x04;    //清除该位，清除事件3标志位				 							
							break;
						case alarmNum&0x08:
									 DealwithEvent(alarmNum&0x08);        //处理事件4
						   ReportEvent(Time,ALARM4);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM4);        //记录事件到SD卡
							  alarmNum^0x08;    //清除该位，清除事件1标志位									
							break;
						case alarmNum&0x10:						
							 DealwithEvent(alarmNum&0x10);        //处理事件5
						   ReportEvent(Time,ALARM5);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM5);        //记录事件到SD卡
							 alarmNum^0x10;    //清除该位，清除事件1标志位					
							break;		
						case alarmNum&0x20:						
							 DealwithEvent(alarmNum&0x20);        //处理事件6
						   ReportEvent(Time,ALARM6);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM6);        //记录事件到SD卡
							 alarmNum^0x20;    //清除该位，清除事件1标志位						
							break;
						case alarmNum&0x40:						
							 DealwithEvent(alarmNum&0x40);        //处理事件7
						   ReportEvent(Time,ALARM7);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM7);        //记录事件到SD卡
							 alarmNum^0x40;    //清除该位，清除事件1标志位					
							break;
						case alarmNum&0x80:						
							 DealwithEvent(alarmNum&0x80);        //处理事件8
						   ReportEvent(Time,ALARM8);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM1);        //记录事件到SD卡
							 alarmNum^0x01;    //清除该位，清除事件1标志位					
							break;
						case alarmNum&0x100:						
							 DealwithEvent(alarmNum&0x100);        //处理事件9
						   ReportEvent(Time,ALARM9);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write(Time,ALARM9);        //记录事件到SD卡
							 alarmNum^0x100;    //清除该位，清除事件1标志位					
							break;		
						case alarmNum&0x200:						
							 DealwithEvent(alarmNum&0x200);        //处理事件10, 加料
						   ReportEvent(Time,ALARM10);     //汇报事件1到上位机服务器(网络通信)
							 SD_Write_Fodder(Time,ALARM10,fodderWeight);        //记录加料重量到SD卡
    					 alarmNum^0x200;    //清除该位，清除事件1标志位						
							break;						
					}						
				
			}
			delay_ms(5000);  //延时5秒钟
			HAL_GPIO_TogglePin(GPIOF,GPIO_Pin_11); //每5秒钟LED0状态翻转一次
	}
}
void LCD_Test()
{
			main_test(); 		//测试主界面
			Test_Read();     //读ID和颜色值测试
			Test_Color();  		//简单刷屏填充测试
			Test_FillRec();		//GUI矩形绘图测试
			Test_Circle(); 		//GUI画圆测试
			Test_Triangle();    //GUI三角形绘图测试
			English_Font_test();//英文字体示例测试
			Chinese_Font_test();//中文字体示例测试
			Pic_test();			//图片显示示例测试
  		Rotate_Test();   //旋转显示测试
		//如果不带触摸，或者不需要触摸功能，请注释掉下面触摸屏测试项
			//Touch_Test();		//触摸屏手写测试  
	
}
void Get_Analogs(ANALOG Analogs)                //获取5路温度及8路模拟量
{
	 Get_Temperatures(Analogs);       //获取5个节点温度
	// Get_Analog8(Analogs);           //获取5路温度及8路模拟量
}

void DealwithAnalogs(Analog analog)     //对5路温度及8路模拟量进行处理
{
	
}

void Get_Temperatures(ANALOG Analogs)       //获取5个节点温度
{
}