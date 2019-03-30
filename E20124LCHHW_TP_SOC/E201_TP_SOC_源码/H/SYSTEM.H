#ifndef _system_h_
#define _system_h_

#include "h\SC93F833X_C.h"
#include "h\INIT.H"
#include "h\UART.H"
#include "lib\SensorMethod.h"
#include "h\key.h"

/*****************宏定义*****************************/
typedef unsigned char INT8U;
typedef unsigned int  INT16U;
typedef unsigned char u8;
typedef unsigned int  u16;
#define Fsys   12000000
#define BaudRate 9600
/*****************全局变量***************************/
extern INT16U Key_Buf,MyKey_Buf_Data,KeyDebunce=0;
extern INT8U count_250us_time = 0,auto_close_mass,auto_close_heat;
extern INT16U auto_close_mass_cnt = 0,auto_close_heat_cnt = 0,count_1ms_time = 0,count_level;
/*****************系统函数***************************/
void system_init(void);
void system_handle(void);

/***************IO口，定时器*************************/
extern void GPIO_INIT(void);
extern void Timer0_Init(void);
extern void TIMER1_INIT(void);
/****************************************************/


#endif