#include "h\system.h"

void system_init(void)
{
  GPIO_INIT();
  TouchKeyInit();//步骤一
  uart_init();
  Timer0_Init();
  TIMER1_INIT();
  EA = 1; //打开总中断
}

void system_handle(void)
{   
    if(SOCAPI_TouchKeyStatus&0x80)//骤 重要步骤  2: 用 触摸键扫描一轮标志，是否调用  TouchKeyScan() 一定要根据此标志位置起后
	{ 
		SOCAPI_TouchKeyStatus &=0x7F;  // 重要步骤  3:  清除标志位， 需要外部清除。
		Key_Buf = TouchKeyScan();
		TouchKeyRestart();  //启动下一轮转换
	} 
//	KeyFunction();

   
}

