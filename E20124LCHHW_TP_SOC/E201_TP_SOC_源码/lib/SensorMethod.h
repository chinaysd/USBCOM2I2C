//*************************************************************************************************
//  Copyright (c) 	��������Ԫ΢�������޹�˾
//	�ļ�����	:  SensorMethod.h
//	����		: 
//	ģ�鹦��	:  �����㷨ͷ�ļ�
// 	�汾	    :
// 	���ļ�¼	:
//	ע������	:    
//************************************************************************************************
#ifndef	_SENSORMETHOD_C_H
#define	_SENSORMETHOD_C_H

//�ⲿ����
extern	unsigned	char	xdata	SOCAPI_TouchKeyStatus;			//API?��?�����䨬?��obit7-��???����?������3������??								
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

//�ⲿ���ú���
extern	void  TouchKeyInit(void);									//����������ʼ��
extern	void  TouchKeyRestart(void);								//������һ�ִ���ɨ��
extern	unsigned long int  TouchKeyScan(void);					    	//�����������ݴ���				

#endif 
