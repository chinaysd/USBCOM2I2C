#include "h/INIT.H"

#include "H/SC93F833X_C.H"
unsigned char count_250us_time,count_level;
unsigned int count_1ms_time;
extern unsigned int motro_count0,motro_count1,auto_close_heat_cnt,auto_close_mass_cnt;
extern unsigned char up_flag,down_flag,auto_close_heat,auto_close_mass;

unsigned char u8IICdata;

void GPIO_INIT(void)
{
	IO_IIC_INT_PIN = 1;				//P21 IIC INT脚，1=当前无数据
    IO_BACK_LIGHT_PIN = 0;          //关闭背光
    IO_LED0_PIN = 1;                //关闭功能指示LED
    IO_LED1_PIN = 1;                //关闭功能指示LED
    P2CON |= (1 << 1) | (1 << 4) | (1 << 6) | (1 << 7);	   //设置P21 P24 P26 P27为输出
    P1CON = 0xFF;                  //设置功能指示LED驱动脚
    P1 = 0xFF;                     //关闭功能指示LED
    P1CON &= ~0X30;
    P1PH  |= 0X30;
}


void iic_init(void)
{
    OTCON = 0x80; //0b10000000; //SSMOD=10 TWI mode
    SSCON1 = 0x45;//0b01011010; //Add=5A
    SSCON0 = 0x88;//0b10001000; //Enable TWI
    IE1 |=0x01;//0b00000001;   //Enable ESSI INT
}

void iic_interrput() interrupt 7
{
    //软件清TWIF标志
    if( (SSCON0&0x07) == 0x02 )
	{
		if( 0x45 != SSDAT )
		{
			u8IICdata = SSDAT;
            IO_LED0_PIN = (0x01&u8IICdata)?1:0;
            IO_LED1_PIN = (0x02&u8IICdata)?1:0;
            IO_LED2_PIN = (0x04&u8IICdata)?1:0;
            IO_LED3_PIN = (0x08&u8IICdata)?1:0;
            IO_LED4_PIN = (0x10&u8IICdata)?1:0;
            IO_LED5_PIN = (0x20&u8IICdata)?1:0;
            
            IO_BACK_LIGHT_PIN = (0x40&u8IICdata)?0:1;
		}
	}
    else if( (SSCON0&0x07) == 0x03 )	//发送数据状态
	{
		IO_IIC_INT_PIN = 1;
	}
		
	SSCON0 &= 0xbf;//0b10111111; //TWIF = 0;
}

void Timer0_Init(void)
{ 
	//TMCON = 0X07;    //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys
	//T0设置
	//TMOD = 0x44;     //0001 0001  ;Timer0和Timer1设置工作方式1
	TL0 = (65536 - 605)%256;    //溢出时间：时钟为Fsys，则6000*（1/Fsys）=250us;
	TH0 = (65536 - 605)/256;
	TR0 = 0;
	ET0 = 1;//定时器0允许
	TR0 = 1;//打开定时器0
	//T2设置
	T2MOD=0x00;
	T2CON=0x00;	 //设置为16位重载寄存器
	RCAP2H=(65536-1000)/256;     //溢出时间：时钟为Fsys，则12000*（1/Fsys）=0.5ms;
	RCAP2L=(65536-1000)%256;
	TR2 = 0;
	ET2 = 1;//定时器2允许
	TR2 = 1;//打开定时器2	
}

void TIMER1_INIT(void)
{
  	//TMCON = 0X07;    //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys
    //T1设置
	//TMOD = 0x44;
	TL1 = (65536 - 6060)%256;   //溢出时间：时钟为Fsys，则24000*（1/Fsys）=1ms;
	TH1 = (65536 - 6060)/256;
	TR1 = 0;
	ET1 = 1;//定时器1允许
	TR1 = 1;//打开定时器1   
}

void timer1() interrupt 3
{
    TL1 = (65536 - 6060)%256;
	TH1 = (65536 - 6060)/256;
}

void timer0() interrupt 1
{
    TL0 = (65536 - 605)%256;
	TH0 = (65536 - 605)/256;     //100us

    count_250us_time++;
	if(count_250us_time > 100)
	{
	  count_250us_time = 0;
	}
	
}

void Timer2Int(void) interrupt 5
{		
	TF2 = 0;   //溢出清零
//    P02=~P02;
//    P25 = ~P25;
}


