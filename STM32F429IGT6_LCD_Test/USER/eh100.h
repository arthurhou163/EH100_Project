#ifndef __EH100_H
#define __EH100_H 			   
#include <sys.h>	
//ʱ��ṹ��
typedef struct
{
  int  year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
}TIME; 

//5·�¶ȼ�8·ģ�����ṹ��
typedef struct
{
  float  temperatur1;
  float  temperatur2;
	float  temperatur3;
	float  temperatur4;
	float  temperatur5;
	float  fanSpeed;
	float  humidity;	
	float  CO2;
	float  NH3;
	float presure1;
	float presure2;
	float presure3;
}ANALOG;


#endif
