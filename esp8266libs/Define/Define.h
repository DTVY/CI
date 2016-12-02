#ifndef DEFINE_H_
#define DEFINE_H_

#include "Include.h"

#define  ul unsigned long
#define  ull unsigned long long

#define CPU_FREQ	80000000
#define JSON_MISSING_UNIT 	-3
#define JSON_TRUE 			0
#define PIN_LED_RED 		13
#define PIN_LED_GREEN 		12
#define PIN_LED_BLUE 		14
#define PIN_BUZZER 			4
#define PIN_RESET_BUTTON 	5

#define JENKINS_COLOR_SUFFIX "/api/json?tree=color"
#define JENKINS_PROJECT_PREFIX "/job/"
#define BUZZER_OFF  		LOW
#define BUZZER_ON  			HIGH

enum state_t //define const for state variables in the loop
{
	WEB_SERVER = 0,
	WEB_SERVER_INIT,
	INIT_CLIENT,
	RESET_CLIENT,
	SEND_DATA,
	RECEIVE_DATA,
	DISPLAY_DATA,
	DISPLAY_THANKS,
	UPDATE_DATA,
	CONFIG,
	NO_CONNECT,
	CONNECTED,
	RECONFIG
};

#ifdef BIG_BOARD_
//BIG BOARD
//define GPIO
#define control_deepsleep 16
#define buttonPinS  1 //D7
#define buttonPinM  13 //D10
#define buttonPinH  14 //D9
#define buttonPinR  15//D8

//define pins of LCD inputs
enum LCD_num_t {
	PIN_LCD_RS = 2, //d6
	PIN_LCD_EN = 0, //d5
	PIN_LCD_D4 = 4, //d4
	PIN_LCD_D5 = 5, //d3
	PIN_LCD_D6 = 3, //d2
	PIN_LCD_D7 = 12 //d1
};

#else
//SMALL BOARD
//define GPIO
#define control_deepsleep 16
#define buttonPinS  1 //D7
#define buttonPinM  13 //D10
#define buttonPinH  14 //D9
#define buttonPinR  15//D8

//define pins of LCD inputs
enum LCD_num_t
{
	PIN_LCD_RS = 2,
	PIN_LCD_EN = 0,
	PIN_LCD_D4 = 4,
	PIN_LCD_D5 = 5,
	PIN_LCD_D6 = 3,
	PIN_LCD_D7 = 12
};
#endif /* BIG_BOARD_ */

#define KEY "12345678"
#define LCD_DISPLAY_HOLDING 5000 //ms
#define THANKS_HOLDING 5000 //ms
#define WAITING_FOR_NEXT_PRESSING 1500 //ms
#define TIME_FOR_TURNOFF_LIGHT_LCD 15 //s
#define TIME_FOR_DEEPSLEEP  2000 //s
#define TIME_FOR_WAITING_STATE 100 //ms
#endif /* DIFINE_H_ */
