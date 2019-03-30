//*************************************************************************************************
//  Copyright (c) 	深圳市赛元微电子有限公司
//	文件名称	:  S_TouchKeyCFG.c
//	作者		: 
//	模块功能	:  SC91F844触控键配置文件
// 	版本		:
// 	更改记录	:
//	注意事项	:  用户需要配置的文件在S_TouchKeyCFG.h中
//  库版本标记	: 
//************************************************************************************************
#include "lib\S_TouchKeyCFG.h"

//*************************************************************************************
//		844 寄存器定义
//*************************************************************************************
/*PSW*/
sfr 	TK_PSW	    = 	0xD0;	//程序状态字
sbit 	TK_CY		= 	TK_PSW^7;	//进位  

//===========================================================================
//全局变量定义
unsigned	char	xdata		SOCAPI_TouchKeyStatus;					//API接口状态：bit7-一轮扫描完成标志  1:完成 	0：未完成
																	    //			   bit6-通道触摸计数溢出标志 1:溢出	 0:未溢出
//===============================================================================
//全局变量声明：该区域不可修改
unsigned 	int 	xdata		RawData [SOCAPI_SET_TOUCHKEY_TOTAL];			
unsigned 	int		xdata		BaseLine[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned    int	 	xdata		FilterData[SOCAPI_SET_TOUCHKEY_TOTAL];												
unsigned	char    xdata		RestAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 			
unsigned	char    xdata		TouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];				
unsigned	char    xdata		NoTouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];  			
unsigned	char	xdata		CurrentChannel[SOCAPI_SET_TOUCHKEY_TOTAL];						     
unsigned    char    xdata 	    LowFingerDataCnt[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned	char    xdata		FloatAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL];  	
int                 xdata 	    DifferAccum[SOCAPI_SET_TOUCHKEY_TOTAL]; 
char	            xdata		SetNoiseThreshold;
unsigned 	char	xdata		ConfirmTouchCnt;
unsigned 	char	xdata		MultipleDealTpye = 0; 

//自定义变量
unsigned 	int 	xdata  	    UpdateBaseLNum; 						// 单键长按计数器
unsigned 	int 	xdata  	    MultipleLNum;						// 多按键干扰计数

//外部变量接口
extern 	unsigned	char	data		CurrentChannelMax;		//当前选中的keysensor的个数
extern  bit  bMultiple;	//多按键标志	
extern 	bit  GetIsNeedUpdateBaseline(void);
extern  void SetNeedUpdateBaseline(void);
extern  unsigned long int SensorKeyFlag(void);
extern  void MultipleDeal(unsigned char CycleCnt);

/***************弹簧库独有***************/
#define		SOCAPI_SET_CS_FUNCTION						1		//0:表示不进行CS测试,1: 表示进行CS测试,默认0
#define		SOCAPI_INHIBITION_ZONE					    8		//抑制区间%，设置范围5-10，默认7,即（7*10）%=70% ，连水时加大该参数,对讲机设置小
#define		SOCAPI_MAX_KEY_MUTIPLE						300		//多少次干扰更新基线，默认300*5=1500
#define		SOCAPI_MAX_KEY_NUM_INVALID					3		//强制更新基线按键限制个数，默认3
/****************************************/

#define	  	AppType			     			0
#define	  	IsDoubleKey			 			1
#define	  	AirSeparationDistance	 	    2
#define   	CONFIRMTOUCHCNT        	        3
#define   	INIT_AUTO_UPDATE_TIME	 	    4
#define   	SET_KEY_CONTI_TIME     	        5  
#define   	SET_SYNC_UPDATE 		 		6
#define   	SET_UPDATE_SPEED 		 		7	
#define   	AUTO_UPDATE_TIME	     	    8
#define	  	FilteredKValue		 			9
#define	  	SET_ANTIJAM		     			10
#define	  	BAUD		             		11
#define	  	DwellTime		         		12
#define   	SaveTime					    13
#define   	NOISE                  	        16

#define   	SET_TOUCH_FREQ		 			0
#define	  	SET_RESOLUTION		 			1
#define   	SET_GAIN_CFG			 		2
#define   	SCANTIME				 		3
#define   	SET_ICHA				 		4
#define   	FINGER_THRESHOLD_H	 		    6
#define   	FINGER_THRESHOLD_L	 		    7

//**********************************************************************************	
// 								函数接口调用部分								  //
//**********************************************************************************
/**************************************************
*函数名称：unsigned int SetOneKeyPushResetTime(void) 
*函数功能：按键最长的输出时间
*入口参数：void
*出口参数：unsigned int SOCAPI_SET_KEY_CONTI_TIME
*备注	 ：这个返回值的设置， 是根据有多长时间启动TouchKeyRestart（）一次
例如10ms 启动一次， 那SOCAPI_SET_KEY_CONTI_TIME*10ms，超过时间后此按键无效。
**************************************************/
unsigned int SetOneKeyPushResetTime(void)   
{	  
	return  TKCFG[SET_KEY_CONTI_TIME];
}
/**************************************************
*函数名称：unsignedint  GetBaselineUpdateThreshold(void)
*函数功能：更新速度 
*入口参数：void
*出口参数：unsigned  int 
*备注	 ：
**************************************************/
unsigned int  GetBaselineUpdateThreshold(void)
{
	return TKCFG[SET_UPDATE_SPEED]; 
}

/**************************************************
*函数名称：unsigned char GetInitAutoUpdateTime(void)
*函数功能：初始化自动校准次数
*入口参数：void
*出口参数：unsigned  char 
*备注	 ：
**************************************************/
unsigned char GetInitAutoUpdateTime(void)
{
	return  TKCFG[INIT_AUTO_UPDATE_TIME];
}
/**************************************************
*函数名称：unsigned char GetCsFunction(void)
*函数功能：进行CS 测试
*入口参数：void
*出口参数：char SOCAPI_SET_CS_FUNCTION
*备注	 ：
**************************************************/
unsigned char GetCsFunction(void)
{
	return SOCAPI_SET_CS_FUNCTION; 
}
/**************************************************
*函数名称：int  GetCurrFingerValue(unsigned char i)
*函数功能：获取当前的finger 值
*入口参数：unsigned char
*出口参数：int 
*备注	 ：
**************************************************/
unsigned int   GetCurrFingerValue(unsigned char i)
{ 
	return	TKChannelCfg[i][FINGER_THRESHOLD_H]*256+TKChannelCfg[i][FINGER_THRESHOLD_L] ;
}

/**************************************************
*函数名称：unsigned char  GetScanTimeValue(unsigned char i)
*函数功能：获取当前通道的扫描时间
*入口参数：unsigned char
*出口参数：unsigned char 
*备注	 ：
**************************************************/
unsigned char  GetScanTimeValue(unsigned char i)
{ 
	return TKChannelCfg[i][SCANTIME];
}
/**************************************************
*函数名称：unsigned char IsDoubleKeyOrSlideKey(void)
*函数功能：检测是否是弹簧滑条或者双键
*入口参数：void
*出口参数：unsigned char 
*备注	 ：
**************************************************/
unsigned char IsDoubleKeyOrSlideKey(void)
{
    return TKCFG[IsDoubleKey];
}
/**************************************************
*函数名称：unsigned char  GetBaseLineAdjustValue(unsigned char i)
*函数功能：获取当前通道的基线调整
j
*入口参数：unsigned char
*出口参数：unsigned char 
*备注	 ：
**************************************************/
unsigned char  GetBaseLineAdjustValue(unsigned char i)
{	
    return TKChannelCfg[i][SET_ICHA]; 
}
/**************************************************
*函数名称：unsigned char GetUpConfirmCnt(void)
*函数功能：检测按键弹起次数
*入口参数：void
*出口参数：返回按键弹起确认次数 
*备注	 ：
**************************************************/
unsigned char GetUpConfirmCnt(void)
{
	return ConfirmTouchCnt>>1;
}
/**************************************************
*函数名称：unsigned char GetTKYzCnt(void)
*函数功能：获取按键抑制确认次数
*入口参数：void
*出口参数：返回抑制次数 
*备注	 ：
**************************************************/

unsigned char GetTKYzCnt(void)
{
	return (ConfirmTouchCnt/3);
}

/**************************************************
*函数名称：int GetTKYzThreshold(unsigned char i)
*函数功能：获取按键抑制区间
*入口参数：unsigned char i
*出口参数：返回抑制区间
*备注	 ：
**************************************************/
unsigned int GetTKYzThreshold(unsigned char i)
{	
	unsigned int SetFingerThresholdtmp; 
	
	SetFingerThresholdtmp = GetCurrFingerValue(i); 
    SetFingerThresholdtmp = SetFingerThresholdtmp*SOCAPI_INHIBITION_ZONE/10;

	return SetFingerThresholdtmp;
}
/**************************************************
*函数名称：void CurrentSensorChoose(void)
*函数功能：当前通道选择
*入口参数：void
*出口参数：void
*备注	 ：
**************************************************/
void CurrentSensorChoose(void)
{
	unsigned char  	i = 0;
	unsigned char  	Ctk_Channel_mark = 0;
	unsigned long int	CurrentSensorKey = 0 ; 
	
	CurrentSensorKey = SOCAPI_SET_TOUCHKEY_CHANNEL; 
		
	for(i=0;i<23;i++)
	{
		CurrentSensorKey=CurrentSensorKey>>1;
		if(TK_CY)
		{
			CurrentChannel[Ctk_Channel_mark] = i;						//选择触摸当前的通道
			Ctk_Channel_mark++;
			if(Ctk_Channel_mark >= SOCAPI_SET_TOUCHKEY_TOTAL)
				break;
		}		
	}
	CurrentChannelMax = Ctk_Channel_mark;							//当前选择的按键数 
}

/**************************************************
*函数名称：unsigned char  GetCfgMsg(unsigned char i)
*函数功能：获取Touch KEY 配置信息
*入口参数：void
*出口参数：int 
*备注	 ：
**************************************************/
unsigned char  GetCfgMsg(unsigned char i)
{
	switch(i)
	{ 
		 case 0:  return TKChannelCfg[0][SET_TOUCH_FREQ];
		 case 1:  return TKChannelCfg[0][SET_RESOLUTION];
		 case 2:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 3:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 4:  return TKCFG[SET_ANTIJAM];
		 default:return 0; 	 	
	}
}

/**************************************************
*函数名称：void CurrentSensorChoose(void)
*函数功能：初始化TK寄存器
*入口参数：void
*出口参数：void
*备注	 ：
**************************************************/
void TouchKeyCFGInit(void)
{
	ConfirmTouchCnt = TKCFG[CONFIRMTOUCHCNT];
	SetNoiseThreshold = TKCFG[NOISE];
	CurrentSensorChoose(); 
	UpdateBaseLNum = 0; 
}

/**************************************************
*函数名称：unsigned int TouchKeyScan(void)
*函数功能：检测按键接口
*入口参数：void
*出口参数：按键通道， 返回的是一个int , 通道数
*备注	 ：1,  调用触控库检测函数SensorKeyFlag()
		   2,  分析得出16个通道，哪个通道有按下，按下bit 位设置为1，否则为0
		   3,  检测是否需要立即更新baseline:  大于MAX_KEY_RESET_BASELINE 个按键按下时立即更新baseline
		   4,  双键或者单键按下时， 时间大于SetOneKeyPushResetTime()结果时更新baseline 
**************************************************/
unsigned long int TouchKeyScan(void)
{
	unsigned char t;
    unsigned char MultipleCnt = 0;//按键计数
	unsigned long int Keyvalue = 0; 
	unsigned long int KeyData = 0; 	
	
	if(GetIsNeedUpdateBaseline() == 0)				//检测是否需要更新baseline 
	{
		Keyvalue = SensorKeyFlag();					//Sensor判断, 这里如果bMultiple = 1 表示中间有干扰	 //分析按键，得出标准的16通道bit 位                     							   
		for(t=0;t<CurrentChannelMax;t++)
		{
			Keyvalue = Keyvalue>>1;
			if(TK_CY)
			{
				KeyData |= ((unsigned long int)0x01 << (CurrentChannel[t]));              
				MultipleCnt++;							
			}
		}                
		if(MultipleCnt >= 2) 	 									//进入多按键处理
		{			
			bMultiple = 1;			
			if(MultipleCnt >= SOCAPI_MAX_KEY_NUM_INVALID)
			{
				SetNeedUpdateBaseline(); 							// 立即更新baseline ,例如亚克力板盖上去
			}
			else
			{					
				if(IsDoubleKeyOrSlideKey())
				{
					bMultiple = 0;
				} 				 
			}			
		}			

		if(bMultiple == 0)							//进入按键判断
		{		
			if(KeyData != 0x0)					    //单个按键达到多长时间就update baseline ,松手检测
			{			
				UpdateBaseLNum++; 
			}
			else	
			{
				UpdateBaseLNum = 0; 	
			} 
		}	
		else
		{   
		    //考虑基线更新		
			MultipleLNum++; 
			KeyData = 0x00;
		}

		if(UpdateBaseLNum > SetOneKeyPushResetTime())	  //按键超出最长输出时间更新基线
		{
 			SetNeedUpdateBaseline(); 
			UpdateBaseLNum = 0;
		}
				
		if(MultipleLNum >SOCAPI_MAX_KEY_MUTIPLE)		  //干扰计数大于最大计数更新基线
 		{
			SetNeedUpdateBaseline(); 
			MultipleDealTpye = 1; 
			MultipleLNum = 0;
		}  
	}			
	else
	{
		MultipleDeal(TKCFG[AUTO_UPDATE_TIME]);										//基线复位处理
	}  
	
	return KeyData;
}





