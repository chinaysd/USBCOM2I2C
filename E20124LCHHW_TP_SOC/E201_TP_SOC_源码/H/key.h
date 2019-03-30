#ifndef _key_h_
#define _key_h_

/*
	key indicator
*/
typedef enum{
	KEY1_LED = 0XFE,
	KEY2_LED = 0XFD,
	KEY3_LED = 0XFB,
	KEY4_LED = 0XF7,
	KEY5_LED = 0XEF,
	KEY6_LED = 0XDF,
	BACKLIGHT_LED = 0XBF		// backlight
}KEY_LED_STA_t;


void KeyFunction(void);



#endif