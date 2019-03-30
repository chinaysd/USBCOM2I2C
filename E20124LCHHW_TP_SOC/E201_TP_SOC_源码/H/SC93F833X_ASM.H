/*--------------------------------------------------------------------------
SC93F833x_ASM.H

ASM Header file for SC93F833x microcontroller.
Copyright (c) 2017 Shenzhen SinOne Chip Electronic CO., Ltd.
All rights reserved.
深圳市赛元微电子有限公司
版本号:  V1.0    
日期:  2017.08.14

--------------------------------------------------------------------------*/
#ifndef _SC93F833x_ASM_H_
#define _SC93F833x_ASM_H_

/* ------------------- 字节寄存器-------------------- */
/*CPU*/
ACC	    EQU 0xE0	//累加器Ａ
B       EQU 0xF0	//通用寄存器B		
PSW	    EQU 0xD0	//程序状态字		
DPH	    EQU 0x83	//数据指针高8位		
DPL	    EQU 0x82	//数据指针低8位		
SP      EQU 0x81	//堆栈指针	
DPL1    EQU 0x84	//DPTR1数据指针1低位		
DPH1    EQU 0x85	//DPTR1数据指针1高位	
DPS     EQU 0x86 //DPTR选择寄存器		

                       
/*system*/             
PCON    EQU 0x87	//电源管理控制寄存器
                       
/*interrupt*/          
IP	    EQU 0xB8	//中断优先权控制寄存器
IE	    EQU 0xA8	//中断控制寄存器
IP1     EQU 0XB9 //中断优先级控制寄存器1
IE1     EQU 0XA9 //中断控制寄存器1
                       
/*PORT*/  
P5PH	  EQU 0xDA	//P5口模式控制寄存器0		
P5CON  	EQU 0xD9	//P5口模式控制寄存器1		
P5	    EQU 0xD8	//P5口数据寄存器             
P2PH	  EQU 0xA2	//P2口模式控制寄存器0		
P2CON  	EQU 0xA1	//P2口模式控制寄存器1		
P2	    EQU 0xA0	//P2口数据寄存器
P1PH    EQU 0x92	//P1口模式控制寄存器0		
P1CON	  EQU 0x91	//P1口模式控制寄存器1	
P1	    EQU 0x90	//P1口数据寄存器
P0PH	  EQU 0x9B	//P0口模式控制寄存器1		
P0CON  	EQU 0x9A	//P0口模式控制寄存器1		
P0 	    EQU 0x80	//P0口数据寄存器
IOHCON  EQU 0x97
                       
/*TIMER*/              
TMCON   EQU 0x8E	//定时器频率控制寄存器
TH1	    EQU 0x8D	//定时器1高8位
TH0	    EQU 0x8C	//定时器0高8位
TL1	    EQU 0x8B	//定时器1低8位
TL0	    EQU 0x8A	//定时器0低8位
TMOD	  EQU 0x89	//定时器工作模式寄存器
TCON	  EQU 0x88	//定时器控制寄存器
T2CON   EQU 0XC8 //定时器2控制寄存器
T2MOD   EQU 0XC9 //定时器2工作模式寄存器
RCAP2L  EQU 0XCA //定时器2重载/捕捉低8位
RCAP2H  EQU 0XCB //定时器2重载/捕捉高8位
TL2     EQU 0XCC //定时器2低8位
TH2     EQU 0XCD //定时器2高8位
                       
/*ADC*/                
ADCCFG0 EQU 0xAB	//P1口ADC功能配置寄存器/参考电压
ADCCFG1 EQU 0xAC	//P1口ADC功能配置寄存器/参考电压
ADCCON  EQU 0XAD //ADC控制寄存器
ADCVL	EQU 0xAE	  //ADC 结果寄存器
ADCVH	EQU 0xAF	  //ADC 结果寄存器
                       
/*PWM*/                
PWMCFG	EQU 0xD1	//PWM设置寄存器
PWMCON	EQU 0xD2	//PWM控制寄存器
PWMPRD	EQU 0xD3	//PWM周期设置寄存器
PWMDTYA	EQU 0xD4	//PWM高电平设置寄存器
PWMDTY0	EQU 0xD5	//PWM高电平设置寄存器
PWMDTY1	EQU 0XD6	//PWM高电平设置寄存器
PWMDTY2	EQU 0XD7	//PWM高电平设置寄存器
                      
/*WatchDog*/          
BTMCON  EQU 0XCE //低频定时器控制寄存器
WDTCON  EQU 0xCF	//WDT控制寄存器
                                              
/*LCD*/
OTCON   EQU 0X8F	//LCD电压输出控制寄存器
P0VO    EQU 0X9C //P2 LCD Bais 输出寄存器

/*INT*/
INT0F   EQU 0XBA //INT0 下降沿中断控制寄存器
INT0R   EQU 0XBB //INT0 上降沿中断控制寄存器
INT1F   EQU 0XBC //INT1 下降沿中断控制寄存器
INT1R   EQU 0XBD //INT1 上降沿中断控制寄存器
INT2F   EQU 0XC6 //INT2 下降沿中断控制寄存器
INT2R   EQU 0XC7 //INT2 上降沿中断控制寄存器

/*PGA*/
PGACFG  EQU 0XBE //PGA设置寄存器
PGACON  EQU 0XBF //PGA控制寄存器

/*IAP */
IAPCTL	EQU 0xF6	//IAP控制寄存器
IAPDAT	EQU 0xF5	//IAP数据寄存器
IAPADE  EQU 0xF4 //IAP扩展地址寄存器
IAPADH	EQU 0xF3	//IAP写入地址高位寄存器
IAPADL	EQU 0xF2	//IAP写入地址低8位寄存器
IAPKEY	EQU 0xF1	//IAP保护寄存器

/*UART*/
SCON    EQU 0X98  	//串口控制寄存器
SBUF    EQU 0X99  	//串口数据缓存寄存器

/*SPI*/
SSCON0  EQU 0X9D   //SPI控制寄存器
SSCON1  EQU 0X9E   //SPI状态寄存器
SSCON2  EQU 0X95    //SPI状态寄存器
SSDAT   EQU 0X9F   //SPI数据寄存器

MXAX    EQU 0XEA 
TA      EQU 0XEB 
OPINX   EQU 0XFE 
OPREG   EQU 0XFF 
EXADH   EQU 0XF7

/*temperature sensor*/
TSCFG   EQU 0XAA

/* ------------------- 位寄存器-------------------- */
/*PSW*/
CY	EQU  PSW .7	//标志位		0:加法运算最高位无进位，或者减法运算最高位无借位时		1:加法运算最高位有进位，或者减法运算最高位有借位时
AC	EQU  PSW .6	//进位辅助标志位	0:无借位、进位		1:加法运算时在bit3位有进位，或减法运算在bit3位有借位时
F0	EQU  PSW .5	//用户标志位
RS1	EQU  PSW .4	//工作寄存器组选择位
RS0 EQU  PSW .3	//工作寄存器组选择位
OV	EQU  PSW .2	//溢出标志位
F1	EQU  PSW .1	//溢出标志位
P	  EQU  PSW .0	//奇偶标志位		0:ACC中1的个数为偶数（包括0个）		1:ACC中1的个数为奇数

/*T2CON*/
TF2	  EQU  T2CON .7
EXF2	EQU  T2CON .6
RCLK	EQU  T2CON .5
TCLK	EQU  T2CON .4
EXEN2	EQU  T2CON .3
TR2	  EQU  T2CON .2
T2    EQU  T2CON .1
CP	  EQU  T2CON .0

/*IP*/
IPADC	  EQU  IP .6		//ADC中断优先控制位	0:设定 ADC的中断优先权是 “低”		1:设定 ADC的中断优先权是 “高”
IPT2	  EQU  IP .5		//PWM中断优先控制位	0:设定 PWM的中断优先权是 “低”		1:设定 PWM 的中断优先权是 “高”
IPUART	EQU  IP .4		//SIF中断优先控制位	0:设定 SIF的中断优先权是 “低”		1:设定 SIF的中断优先权是 “高”
IPT1	  EQU  IP .3		//Timer1中断优先控制位	0:设定 Timer 1的中断优先权是 “低”	1:设定 Timer 1的中断优先权是 “高”
IPINT1	EQU  IP .2		//32K Base Timer中断优先控制位		0:设定 32K的中断优先权是 “低”		1:设定 32K的中断优先权是 “高”
IPT0	  EQU  IP .1		//Timer0中断优先控制位	0:设定 Timer 0的中断优先权是 “低”	1:设定 Timer 0的中断优先权是 “高”
IPINT0	EQU  IP .0

/*IE*/
EA	  EQU  IE .7		//中断使能的总控制	0:关闭所有的中断	1:打开所有的中断
EADC	EQU  IE .6		//ADC中断使能控制	0:关闭ADC中断		1:打开ADC中断
ET2 	EQU  IE .5		//PWM中断使能控制	0:关闭PWM中断		1:打开PWM中断
EUART EQU  IE .4		//UART中断使能控制	0:关闭SIF中断		1:打开SIF中断
ET1 	EQU  IE .3		//Timer1中断使能控制	0:关闭TIMER1中断	1:打开TIMER1中断
EINT1	EQU  IE .2		//32K Base Timer中断使能控制	0:关闭32K中断		1:打开32K中断	
ET0	  EQU  IE .1		//Timer0中断使能控制	0:关闭TIMER0中断	1:打开TIMER0中断
EINT0	EQU  IE .0		//TouchKey的中断使能控制	0:关闭TouchKey中断  1:打开TouchKey中断

/*TCON*/
TF1 EQU  TCON .7	//T1溢出中断请求标志位	T1产生溢出，发生中断时，硬件将TF1置为“1”，申请中断，CPU响应时，硬件清“0”。
TR1	EQU  TCON .6	//定时器T1的运行控制位	0:Timer1禁止计数		1:Timer1开始计数
TF0	EQU  TCON .5	//T0溢出中断请求标志位	T0产生溢出，发生中断时，硬件将TF0置为“1”，申请中断，CPU响应时，硬件清“0”。
TR0	EQU  TCON .4	//定时器T0的运行控制位	0:Timer0禁止计数		1:Timer0开始计数

/*SCON*/
SM0	EQU  SCON .7
SM1	EQU  SCON .6
SM2	EQU  SCON .5
REN	EQU  SCON .4
TB8 EQU  SCON .3
RB8 EQU  SCON .2
TI	EQU  SCON .1
RI	EQU  SCON .0

/******************* P0 ******************
*SC93F8333封装未引出的管脚：无
*SC93F8332封装未引出的管脚：P06/P07
*SC93F8331封装未引出的管脚：P02/P03/P04/P06/P07
******************************************/
P07	EQU  P0 .7
P06 EQU  P0 .6
P05	EQU  P0 .5
P04 EQU  P0 .4
P03	EQU  P0 .3
P02 EQU  P0 .2
P01	EQU  P0 .1
P00 EQU  P0 .0

/******************* P1 ******************
*SC93F8333封装未引出的管脚：P10
*SC93F8332封装未引出的管脚：P10/P16/P17
*SC93F8331封装未引出的管脚：P10/P16/P17
******************************************/
P17	EQU  P1 .7
P16	EQU  P1 .6
P15 EQU  P1 .5
P14	EQU  P1 .4
P13 EQU  P1 .3
P12	EQU  P1 .2
P11	EQU  P1 .1


/******************* P2 ******************
*SC93F8333封装未引出的管脚：无
*SC93F8332封装未引出的管脚：P22/P23
*SC93F8331封装未引出的管脚：P22/P23/P27
******************************************/
P27 EQU  P2 .7
P26	EQU  P2 .6
P25 EQU  P2 .5
P24	EQU  P2 .4
P23	EQU  P2 .3
P22	EQU  P2 .2
P21	EQU  P2 .1
P20	EQU  P2 .0

/******************* P5 ******************
*SC93F8333封装未引出的管脚：无
*SC93F8332封装未引出的管脚：P50/P51
*SC93F8331封装未引出的管脚：P50/P51
******************************************/
P52	EQU  P5 .2
P51	EQU  P5 .1
P50	EQU  P5 .0

/****************************************************************************
*注意：封装未引出的管脚，需设置为强推挽输出模式
*IC选型：请根据所使用的IC型号,在初始化完IO口后，调用相对应的未引出管脚的IO口配置
*
*****************************************************************************/
SC93F8333_IO_Init  MACRO  IO                     //SC93F8333_IO_Init未引出管脚的IO口配置
									 ORL P1CON,#0X01
                   ENDM
SC93F8332_IO_Init  MACRO  IO                     //SC93F8332未引出管脚的IO口配置
                   ORL P0CON,#0XC0
									 ORL P1CON,#0XC1
									 ORL P2CON,#0X0C
									 ORL P5CON,#0X03
                   ENDM
SC93F8331_IO_Init  MACRO  IO                     //SC93F8331未引出管脚的IO口配置
                   ORL P0CON,#0XDC
									 ORL P1CON,#0XC1
									 ORL P2CON,#0X8C
									 ORL P5CON,#0X03
                   ENDM
#endif
