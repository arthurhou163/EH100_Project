#ifndef __EH100_H
#define __EH100_H 			   
#include <sys.h>	
//时间结构体
typedef struct
{
  int  year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
}TIME; 

//5路温度及8路模拟量结构体
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
