#include "fsm.h"

uint8_t mode_lcd, mode_sys;


void ReadData(void){
    // _Data.current = IN_GetCur();
    // _Data.energy = IN_GetEner();
    // _Data.frequency = IN_GetFre();
    // _Data.pf = IN_GetPF();
    // _Data.power = IN_GetPow();
    // _Data.vol = IN_GetVol();
    // _Data.water_volume = IN_GetWaterVolume_l();
}

String ConvertDataToJSONString(void){
    String str = "";
    str += "{\"ENERGY\":";
    str += String(_Data.energy);
    str += ",\"WATER\":";
    str += String(_Data.water_volume);
    str += "}";
}

uint8_t ModeSys(void){
    return mode_sys;
}

//===========================HIGH LEVEL FUNCTION===========================//
void FSM_Init(void){
    mode_lcd = INIT;
    mode_sys = INIT;
    _time_screen = 50;
}

void FSM_LcdDisplay(void){
    switch (mode_lcd) {
    case INIT:
        CLCD_PrintStringBuffer(0, 0, SCREEN_INIT_0);
        CLCD_PrintStringBuffer(1, 0, SCREEN_INIT_1);

        if(_time_screen < 5) mode_lcd = READY_DISPLAY;
        break;
    case READY_DISPLAY:
        if(ModeSys() == SYS_CONNECT_WF){
            CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
            mode_lcd = DISPLAY_CONNECT_WF;
        }
        else if(ModeSys() == SYS_CONFIG_WF){
            CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
            mode_lcd = DISPLAY_CONFIG_WF;
        }
        else if(ModeSys() == SYS_PROCESS_DATA){
            // wifi is connected => ready to transmit data
            CLCD_PrintStringBuffer(0, 0, SCREEN_VOL_CUR_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_VOL_CUR_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_VOL_CUR;
        }
        break;
    case DISPLAY_CONFIG_WF:
        if(ModeSys() == SYS_CONNECT_WF){
            CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
            mode_lcd = DISPLAY_CONNECT_WF;     
        }
        break;
    case DISPLAY_CONNECT_WF:
        // Print '.' every 500ms
        CLCD_PrintCharBuffer(1, 6 + (_counter_time_elapsed/10) % 5, '.');
        if((_counter_time_elapsed/10) % 5 == 4) CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

        if(ModeSys() == SYS_CONFIG_WF){
            CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
            mode_lcd = DISPLAY_CONFIG_WF;
        }
        else if(ModeSys() == SYS_PROCESS_DATA){
            // wifi is connected => ready to transmit data
            CLCD_PrintStringBuffer(0, 0, SCREEN_VOL_CUR_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_VOL_CUR_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_VOL_CUR;
        }
        break;
    case DISPLAY_VOL_CUR:
        CLCD_PrintFloatBuffer(0, INDEX_LCD_VOL, _Data.vol);
        CLCD_PrintFloatBuffer(1, INDEX_LCD_CUR, _Data.current);

        if(_time_screen < 5){
            CLCD_PrintStringBuffer(0, 0, SCREEN_POW_ENER_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_POW_ENER_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_POW_ENER;
        }
        else if(ModeSys() != SYS_PROCESS_DATA){
            mode_lcd = READY_DISPLAY;
        }
        break;
    case DISPLAY_POW_ENER:
        CLCD_PrintFloatBuffer(0, INDEX_LCD_POW, _Data.power);
        CLCD_PrintFloatBuffer(1, INDEX_LCD_ENE, _Data.energy);

        if(_time_screen < 5){
            CLCD_PrintStringBuffer(0, 0, SCREEN_FRE_PF_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_FRE_PF_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_FRE_PF;
        }
        else if(ModeSys() != SYS_PROCESS_DATA){
            mode_lcd = READY_DISPLAY;
        }       
        break;
    case DISPLAY_FRE_PF:
        CLCD_PrintFloatBuffer(0, INDEX_LCD_FRE, _Data.frequency);
        CLCD_PrintFloatBuffer(1, INDEX_LCD_PF, _Data.pf);

        if(_time_screen < 5){
            CLCD_PrintStringBuffer(0, 0, SCREEN_WATER_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_WATER_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_WATER;
        }
        else if(ModeSys() != SYS_PROCESS_DATA){
            mode_lcd = READY_DISPLAY;
        }             
        break;
    case DISPLAY_WATER:
        CLCD_PrintFloatBuffer(0, INDEX_LCD_WATER, _Data.water_volume);

        if(_time_screen < 5){
            CLCD_PrintStringBuffer(0, 0, SCREEN_VOL_CUR_0);
            CLCD_PrintStringBuffer(1, 0, SCREEN_VOL_CUR_1);
            _time_screen = TIME_SCREEN;
            mode_lcd = DISPLAY_VOL_CUR;
        }
        else if(ModeSys() != SYS_PROCESS_DATA){
            mode_lcd = READY_DISPLAY;
        }   
        break; 
    default:
        mode_lcd = INIT;
        break;
    }
}

void FSM_SystemControl(void){
    switch (mode_sys) {
    case INIT:
        UART_SendMsg(CMD_CONNECT_WF);
        mode_sys = SYS_CONNECT_WF;
        break;
    case SYS_CONFIG_WF:
        if(UART_GetMsg() == CONFIG_WF_SUCCESS){
            UART_SendMsg(CMD_CONNECT_WF);
            mode_sys = SYS_CONNECT_WF;
        }
        break;
    case SYS_CONNECT_WF:
        if(UART_GetMsg() == CONNECT_WF_SUCCESS){
            UART_SendMsg(CMD_TRANSMIT);
            mode_sys = SYS_PROCESS_DATA;
        }
        else if(IN_IsPressed_ms(BT0, 2000)){
            UART_SendMsg(CMD_CONFIG_WF);
            mode_sys = SYS_CONFIG_WF;
        }
        break;
    case SYS_PROCESS_DATA:
        if(_time_read_data < 5){
            ReadData();
            UART_SendMsg(ConvertDataToJSONString());
        }

        if(UART_GetMsg() == DISCONNECT_WF){
            UART_SendMsg(CMD_CONNECT_WF);
            mode_sys = SYS_CONNECT_WF;
        }
        else if(IN_IsPressed_ms(BT0, 2000)){
            UART_SendMsg(CMD_CONFIG_WF);
            mode_sys = SYS_CONFIG_WF;
        }
        break;
    default:
        break;
    }
}
