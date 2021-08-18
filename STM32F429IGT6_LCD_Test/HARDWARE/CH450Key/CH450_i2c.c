/*
  编辑： 侯工
  程序说明: 本程序用于STM32F429 与CH450 通信，用于读取按键
  软件环境: Keil uVision 5.23 
  硬件环境:  STM32F429IGT6
  日    期: 2020.11.12
*/

#include "sys.h"
#include "delay.h"
#include "ch450i2c.h"

/** I2C 总线接口 */
#define I2C_PORT GPIOF
#define SDA_Pin	GPIO_PIN_0
#define SCL_Pin GPIO_PIN_1
#define D_INT   GPIO_PIN_2   //CH450 向STM32连接的中断线

#define FAILURE 0
#define SUCCESS 1

//配置SDA信号线为输入模式
void SDA_Input_Mode()
{
	GPIO_InitTypeDef GPIO_Initure;

	
	__HAL_RCC_GPIOF_CLK_ENABLE();			   //开启GPIOB时钟
  GPIO_Initure.Pin=SDA_Pin;            //SDA
  GPIO_Initure.Mode=GPIO_MODE_INPUT;     //输入下拉
  GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;   //Speed_2MHz
  HAL_GPIO_Init(I2C_PORT,&GPIO_Initure); 	
	
}

//配置SDA信号线为输出模式
void SDA_Output_Mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	  __HAL_RCC_GPIOF_CLK_ENABLE();			   //开启GPIOB时钟
	  GPIO_InitStructure.Pin = SDA_Pin;
  	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;

  	HAL_GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}

//  GPIO_PIN_RESET = 0,
  
void SDA_Output( uint16_t val )
{
	if ( val ) {

		HAL_GPIO_WritePin(I2C_PORT, SDA_Pin, GPIO_PIN_SET);
	} else {

		HAL_GPIO_WritePin(I2C_PORT, SDA_Pin, GPIO_PIN_RESET);
	}
}

//
void SCL_Output( uint16_t val )
{
	if ( val ) {
		HAL_GPIO_WritePin(I2C_PORT,SCL_Pin, GPIO_PIN_SET);		
	} else {
		HAL_GPIO_WritePin(I2C_PORT, SCL_Pin, GPIO_PIN_RESET);		
	}
}

//
uint8_t SDA_Input()
{
	return  HAL_GPIO_ReadPin(I2C_PORT, SDA_Pin);
}
/*
//延时程序
void delay1(unsigned int n)
{
	unsigned int i;
	for ( i=0;i<n;++i);
}  */

//I2C总线启动
void I2CStart(void)
{
	SDA_Output(1);delay_us(100);//delay1(500); 最小100ns. 在此我们延时100us.
	SCL_Output(1);delay_us(100);//delay1(500);
	SDA_Output(0);delay_us(100);//delay1(500);
	SCL_Output(0);delay_us(100);//delay1(500);
}

//I2C总线停止
void I2CStop(void)
{
	SCL_Output(0); delay_us(100);//delay1(500); 最小100ns. 在此我们延时100us.
	SDA_Output(0); delay_us(100);//delay1(500);
	SCL_Output(1); delay_us(100);//delay1(500);
	SDA_Output(1); delay_us(100);//delay1(500);

}

//等待应答
unsigned char I2CWaitAck(void)
{
	unsigned short cErrTime = 5;
	SDA_Input_Mode(); 
	delay_us(100);//delay1(500);
	SCL_Output(1);delay_us(100);//delay1(500);
	while(SDA_Input())
	{
		cErrTime--;
		delay_us(100);//delay1(500);
		if (0 == cErrTime)
		{
			SDA_Output_Mode();
			I2CStop();
			return FAILURE;
		}
	}
	SDA_Output_Mode();
	SCL_Output(0);delay_us(100);//delay1(500); 
	return SUCCESS;
}

//发送应答位
void I2CSendAck(void)
{
	SDA_Output(0);delay_us(100);//delay1(500);
	delay_us(100);//delay1(500);
	SCL_Output(1); delay_us(100);//delay1(500);
	SCL_Output(0); delay_us(100);//delay1(500);

}

//
void I2CSendNotAck(void)
{
	SDA_Output(1);
	delay_us(100);//delay1(500);
	SCL_Output(1); delay_us(100);//delay1(500);
	SCL_Output(0); delay_us(100);//delay1(500);

}

//通过I2C总线发送一个字节数据
void I2CSendByte(unsigned char cSendByte)
{
	unsigned char  i = 8;
	while (i--)
	{
		SCL_Output(0);delay_us(100);//delay1(500); 
		SDA_Output(cSendByte & 0x80);delay_us(100);// delay1(500);
		cSendByte += cSendByte;
		delay_us(100);//delay1(500); 
		SCL_Output(1);delay_us(100);//delay1(500); 
	}
	SCL_Output(0);delay_us(100);//delay1(500); 
}

//从I2C总线接收一个字节数据
unsigned char I2CReceiveByte(void)
{
	unsigned char i = 8;
	unsigned char cR_Byte = 0;
	SDA_Input_Mode(); 
	while (i--)
	{
		cR_Byte += cR_Byte;
		SCL_Output(0);delay_us(100);//delay1(500); 
		delay_us(100);//delay1(500); 
		SCL_Output(1);delay_us(100);//delay1(500); 
		cR_Byte |=  SDA_Input(); 
	}
	SCL_Output(0);delay_us(100);//delay1(500); 
	SDA_Output_Mode();
	return cR_Byte;
}

//I2C总线初始化
void i2c_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
   __HAL_RCC_GPIOF_CLK_ENABLE();			//使能GPIOF时钟
	
	GPIO_InitStructure.Pin = SDA_Pin | SCL_Pin;
  	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;  //2MHz
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;	 // **

  	HAL_GPIO_Init(I2C_PORT, &GPIO_InitStructure);
	
}
//  这个函数是由侯工编写，2020.11.12
// ch450Key_init()函数实现对CH450按键读的初始化
//
void  ch450Key_init()
{
	  i2c_init();
	  I2CStart();   //启动信号
	  I2CSendByte(0x48);//系统设置命令 0x48
	  I2CWaitAck();//等待应答
		I2CSendByte(0x02);//允许按键输入
	  I2CWaitAck();//等待应答
	  I2CStop();   //输出停止信号
	
}
// 设置CH450进入休眠状态
void  ch450Key_Sleep()
{
	  I2CStart();   //启动信号
	  I2CSendByte(0x48);//系统设置命令 0x48
	  I2CWaitAck();//等待应答
		I2CSendByte(0x80);//ch450 进入休眠
	  I2CWaitAck();//等待应答
	  I2CStop();   //输出停止信号	
}
//发生按键中断时读取ch450_ReadKey()此函数来获得按键值
char ch450_ReadKey()
{
	 unsigned char data;
	 I2CStart();   //启动信号 
	 I2CSendByte(0x4F);   //发送读按键命令0x4F
	 I2CWaitAck();//等待应答
	 data=I2CReceiveByte();
	 I2CSendNotAck();  //发出无应答
	 I2CStop();   //输出停止信号
	 return data;  //返回按键值
}