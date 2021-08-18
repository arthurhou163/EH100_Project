/*
  �༭�� �
  ����˵��: ����������STM32F429 ��CH450 ͨ�ţ����ڶ�ȡ����
  �������: Keil uVision 5.23 
  Ӳ������:  STM32F429IGT6
  ��    ��: 2020.11.12
*/

#include "sys.h"
#include "delay.h"
#include "ch450i2c.h"

/** I2C ���߽ӿ� */
#define I2C_PORT GPIOF
#define SDA_Pin	GPIO_PIN_0
#define SCL_Pin GPIO_PIN_1
#define D_INT   GPIO_PIN_2   //CH450 ��STM32���ӵ��ж���

#define FAILURE 0
#define SUCCESS 1

//����SDA�ź���Ϊ����ģʽ
void SDA_Input_Mode()
{
	GPIO_InitTypeDef GPIO_Initure;

	
	__HAL_RCC_GPIOF_CLK_ENABLE();			   //����GPIOBʱ��
  GPIO_Initure.Pin=SDA_Pin;            //SDA
  GPIO_Initure.Mode=GPIO_MODE_INPUT;     //��������
  GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;   //Speed_2MHz
  HAL_GPIO_Init(I2C_PORT,&GPIO_Initure); 	
	
}

//����SDA�ź���Ϊ���ģʽ
void SDA_Output_Mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	  __HAL_RCC_GPIOF_CLK_ENABLE();			   //����GPIOBʱ��
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
//��ʱ����
void delay1(unsigned int n)
{
	unsigned int i;
	for ( i=0;i<n;++i);
}  */

//I2C��������
void I2CStart(void)
{
	SDA_Output(1);delay_us(100);//delay1(500); ��С100ns. �ڴ�������ʱ100us.
	SCL_Output(1);delay_us(100);//delay1(500);
	SDA_Output(0);delay_us(100);//delay1(500);
	SCL_Output(0);delay_us(100);//delay1(500);
}

//I2C����ֹͣ
void I2CStop(void)
{
	SCL_Output(0); delay_us(100);//delay1(500); ��С100ns. �ڴ�������ʱ100us.
	SDA_Output(0); delay_us(100);//delay1(500);
	SCL_Output(1); delay_us(100);//delay1(500);
	SDA_Output(1); delay_us(100);//delay1(500);

}

//�ȴ�Ӧ��
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

//����Ӧ��λ
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

//ͨ��I2C���߷���һ���ֽ�����
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

//��I2C���߽���һ���ֽ�����
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

//I2C���߳�ʼ��
void i2c_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
   __HAL_RCC_GPIOF_CLK_ENABLE();			//ʹ��GPIOFʱ��
	
	GPIO_InitStructure.Pin = SDA_Pin | SCL_Pin;
  	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;  //2MHz
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;	 // **

  	HAL_GPIO_Init(I2C_PORT, &GPIO_InitStructure);
	
}
//  ����������ɺ��д��2020.11.12
// ch450Key_init()����ʵ�ֶ�CH450�������ĳ�ʼ��
//
void  ch450Key_init()
{
	  i2c_init();
	  I2CStart();   //�����ź�
	  I2CSendByte(0x48);//ϵͳ�������� 0x48
	  I2CWaitAck();//�ȴ�Ӧ��
		I2CSendByte(0x02);//����������
	  I2CWaitAck();//�ȴ�Ӧ��
	  I2CStop();   //���ֹͣ�ź�
	
}
// ����CH450��������״̬
void  ch450Key_Sleep()
{
	  I2CStart();   //�����ź�
	  I2CSendByte(0x48);//ϵͳ�������� 0x48
	  I2CWaitAck();//�ȴ�Ӧ��
		I2CSendByte(0x80);//ch450 ��������
	  I2CWaitAck();//�ȴ�Ӧ��
	  I2CStop();   //���ֹͣ�ź�	
}
//���������ж�ʱ��ȡch450_ReadKey()�˺�������ð���ֵ
char ch450_ReadKey()
{
	 unsigned char data;
	 I2CStart();   //�����ź� 
	 I2CSendByte(0x4F);   //���Ͷ���������0x4F
	 I2CWaitAck();//�ȴ�Ӧ��
	 data=I2CReceiveByte();
	 I2CSendNotAck();  //������Ӧ��
	 I2CStop();   //���ֹͣ�ź�
	 return data;  //���ذ���ֵ
}