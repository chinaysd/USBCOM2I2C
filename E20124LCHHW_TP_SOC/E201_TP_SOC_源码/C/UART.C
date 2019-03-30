#include "h\UART.h"
#include "H/SC93F833X_C.H"

void uart_init(void)
{
	OPINX=0xC1;
	
//	OPREG=0xA8;//6M
	OPREG=0x98;//12M	
	OPINX=0xC2;
	OPREG=0x00;
	
	WDTCON=0x10;
	
	P1CON=0xFF;
	
	P1CON|=1<<3;
	P13=1;
	P1CON&=~(1<<2);
	P12=1;
	
	//使用定时器1
	SCON=0x50;
	PCON|=0x80;
	T2CON&=~0x30;
	TMCON|=0x02;
	TMOD&=0x0f;
	TMOD|=0x20;
	TH1=256-Fsys/BaudRate/16/2*2;
	TR1=0;
	TR1=1;
	EUART=0;
}

void UART_TX_byte(unsigned char DATA)
{
   TI = 0;
   SBUF = DATA;
   while(!TI);
}


