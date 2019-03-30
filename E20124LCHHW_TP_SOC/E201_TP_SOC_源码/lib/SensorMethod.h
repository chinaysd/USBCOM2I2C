//*************************************************************************************************
//  Copyright (c) 	深圳市赛元微电子有限公司
//	文件名称	:  SensorMethod.h
//	作者		: 
//	模块功能	:  触控算法头文件
// 	版本	    :
// 	更改记录	:
//	注意事项	:    
//************************************************************************************************
#ifndef	_SENSORMETHOD_C_H
#define	_SENSORMETHOD_C_H

//外部变量
extern	unsigned	char	xdata	SOCAPI_TouchKeyStatus;			//API?ó?ú×′ì?￡obit7-ò???é¨?èíê3é±ê??								
extern 	unsigned 	char	xdata	ConfirmTouchCnt;							
extern 	unsigned 	int		xdata 	RawData[];			 				
extern 	unsigned 	int		xdata	BaseLine[];	
extern	unsigned  	int	 	xdata  	FilterData[];					 
extern	unsigned 	int 	xdata 	CurrentSensorKey;		 				
extern 	unsigned	char  	xdata 	RestAreaCnt[]; 					 
extern 	unsigned	char  	xdata 	TouchCnt[];
extern 	unsigned	char  	xdata 	NoTouchCnt[];  			  
extern  unsigned	char 	xdata 	CurrentChannel[];			 
extern  unsigned    char    xdata   LowFingerDataCnt[]; 
extern 				int     xdata 	DifferAccum[];
extern  unsigned	char  	xdata	FloatAreaCnt[]; 
extern 				char	xdata	SetNoiseThreshold;	
extern  unsigned 	char	xdata	MultipleDealTpye;
extern  unsigned 	char    xdata   ICHG_RawData_Ratio;

//外部调用函数
extern	void  TouchKeyInit(void);									//触摸按键初始化
extern	void  TouchKeyRestart(void);								//启动下一轮触摸扫描
extern	unsigned long int  TouchKeyScan(void);					    	//触摸按键数据处理				

#endif 
