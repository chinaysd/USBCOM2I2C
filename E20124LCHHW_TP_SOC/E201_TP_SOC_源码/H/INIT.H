#ifndef _init_h_
#define _init_h_



/*********IO 模式*****************************************************/
//#define   IO_LED_FOOT_LIGHT_MODE    P0CON = 0X07;//设置P00为强推挽IO
//#define   IO_RED_LIGHT_MODE         P2CON = 0X2F;//设置P25为强推挽IO
//#define   IO_MOTOR_ONE_MODE         P0CON = 0X07;//设置P01为强推挽IO
//#define   IO_MOTOR_TWO_MODE         P0CON = 0X07;//设置P02为强推挽IO


/*********************************************************************/

/*********IO 宏定义***************************************************/
#define   IO_IIC_INT_PIN            P21

#define   IO_BACK_LIGHT_PIN         P24
#define   IO_LED0_PIN               P26
#define   IO_LED1_PIN               P27
#define   IO_LED2_PIN               P15
#define   IO_LED3_PIN               P14
#define   IO_LED4_PIN               P13
#define   IO_LED5_PIN               P12


/*********************************************************************/

/*********IO 处理*****************************************************/

/*********************************************************************/

void GPIO_INIT(void);
void Timer0_Init(void);
void TIMER1_INIT(void);
void iic_init(void);
     
#endif

