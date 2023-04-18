#include "fsm.h"

uint8_t mode_lcd, mode_sys;


void FSM_Init(void){
    mode_lcd = mode_sys = INIT;
}

void FSM_SystemControl(void);
