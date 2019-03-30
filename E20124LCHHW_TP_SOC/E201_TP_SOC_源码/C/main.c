#include "H/SC93F833X_C.H"
#include "lib/SensorMethod.h"
#include "h/UART.H"
#include "h/INIT.H"


unsigned long Key_Buf,KeyDebunce,MyKey_Buf_Data;

unsigned char	u8KeyValue = 0;
#define TK0_VALUE  	0x20
#define TK1_VALUE  	0x10
#define TK2_VALUE  	0x08
#define TK3_VALUE  	0x04
#define TK4_VALUE 	0x02
#define TK13_VALUE 	0x01

void main()
{
	GPIO_INIT();
    Timer0_Init();
	iic_init();

    TouchKeyInit(); // 触控按键初始化
	EA = 1;
	
	while(1)
	{
		WDTCON|=0x10;
		if(SOCAPI_TouchKeyStatus&0x80) // 重要步骤 2: 触摸键扫描一轮标志，是否调用 TouchKeyScan() 一定要根据此标志位置起后
		{
			SOCAPI_TouchKeyStatus &= 0x7f;// 重要步骤 3:  清除标志位， 需要外部清除。
			MyKey_Buf_Data = TouchKeyScan();// 按键数据处理函数
			switch(MyKey_Buf_Data)
			{
				case 0X0001:                //TK0
					if( TK0_VALUE != u8KeyValue )	
					{	
						u8KeyValue = TK0_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
				case 0X0002:                //TK1
					if( TK1_VALUE != u8KeyValue )	
					{
						u8KeyValue = TK1_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
				case 0X0004:                //TK2
					if( TK2_VALUE != u8KeyValue )
					{
						u8KeyValue = TK2_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
				case 0X0008:                //TK3
					if( TK3_VALUE != u8KeyValue )
					{
						u8KeyValue = TK3_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
						
				case 0X0010:                //TK4
					if( TK4_VALUE != u8KeyValue )
					{
						u8KeyValue = TK4_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
				case 0X2000:                //TK13
					if( TK13_VALUE != u8KeyValue )
					{
						u8KeyValue = TK13_VALUE;					//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
				default:
					if( 0 != u8KeyValue )
					{
						u8KeyValue = 0;							//按键变化，向主控发送
						SSDAT = u8KeyValue;
						IO_IIC_INT_PIN = 0;
					}
					break;
			}
			TouchKeyRestart();// 启动下一轮转换
		}	   
	}	
}


