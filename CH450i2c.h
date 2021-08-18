#ifndef  __I2C_H__
#define  __I2C_H__

void i2c_init(void);
//void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);
char ch450_ReadKey();
void  ch450Key_Sleep();
void  ch450Key_init();

#endif
