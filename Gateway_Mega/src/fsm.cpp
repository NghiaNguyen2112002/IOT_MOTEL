#include "fsm.h"

uint8_t mode_lcd, mode_sys;


void FSM_Init(void){
    mode_lcd = mode_sys = INIT;
}

void FSM_LcdDisplay(void){
    switch (mode_lcd) {
    case INIT:
        
        break;
    case DISPLAY_CONFIG_WF:

        break;
    case DISPLAY_CONNECT_WF:

        break;
    case DISPLAY_VOL_CUR:

        break;
    case DISPLAY_POW_ENE:

        break;
    case DISPLAY_FRE_PF:

        break;
    case DISPLAY_WATER:

        break; 
    default:
        break;
    }
}

void FSM_SystemControl(void);
