#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "lcd_i2c.h"
#include "uart.h"
#include "input.h"
#include "screen_lcd.h"
#include "global.h"


//==================MODE FSM LCD DISPLAY==================//
#define INIT						0
#define READY_DISPLAY               1
#define DISPLAY_VOL_CUR             2
#define DISPLAY_POW_ENER            3
#define DISPLAY_FRE_PF              4
#define DISPLAY_WATER               5
#define DISPLAY_CONFIG_WF           6
#define DISPLAY_CONNECT_WF          7

//==================MODE FSM SYSTEM CONTROL==================//
// #define INIT                        0
#define SYS_CONNECT_WF              1
#define SYS_CONFIG_WF               2
#define SYS_PROCESS_DATA            3 

//==================TIME==================//
#define TIME_SCREEN						500                 //5000 ms
#define TIME_READ_DATA					1000                //10 000ms

//==================MSG FROM ESP==================//
#define CONFIG_WF_SUCCESS				"CONFIG_SUCCESS"
#define CONNECT_WF_SUCCESS				"CONNECT_SUCCESS"
#define DISCONNECT_WF					"DISCONNECT"


//==================CMD TO ESP==================//
#define CMD_CONNECT_WF					"CONNECT"
#define CMD_CONFIG_WF					"CONFIG"
#define CMD_TRANSMIT                    "TRANSMIT"

void FSM_Init(void);
void FSM_LcdDisplay(void);
void FSM_SystemControl(void);
void FSM_DataTransfer(void);

#endif /* INC_FSM_H_ */
