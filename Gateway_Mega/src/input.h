#ifndef __INPUT_H__
#define __INPUT_H__

#include "Arduino.h"

#include "SoftwareSerial.h"
#include "pin.h"


//==================BUTTON===================//
#define NO_OF_BUTTONS         1
#define BUTTON_IS_PRESSED     0
#define BUTTON_IS_RELEASED    1

#define MAX_COUNTER           1000      //50s

#define BT0                   0

//===================YF_S201===================//
#define FACTOR_K_YF_S201        7.5

//===================PZEM 004T 100A V3.0===================//
#define SCALE_V                 0.1
#define SCALE_A                 0.001
#define SCALE_P                 0.1
#define SCALE_E                 1
#define SCALE_F                 0.1
#define SCALE_PF                0.01


#define INDEX_PZEM_ADDRR        0
#define INDEX_PZEM_BYTE_SUCCESS 1
#define INDEX_PZEM_NUM_B        2
#define INDEX_PZEM_VOL_H        3
#define INDEX_PZEM_VOL_L        4
#define INDEX_PZEM_AMP_H        5
#define INDEX_PZEM_AMP_L        6
#define INDEX_PZEM_AMP1_H       7
#define INDEX_PZEM_AMP1_L       8
#define INDEX_PZEM_POW_H        9
#define INDEX_PZEM_POW_L        10
#define INDEX_PZEM_POW1_H       11
#define INDEX_PZEM_POW1_L       12
#define INDEX_PZEM_ENE_H        13
#define INDEX_PZEM_ENE_L        14
#define INDEX_PZEM_ENE1_H       15
#define INDEX_PZEM_ENE1_L       16
#define INDEX_PZEM_FRE_H        17
#define INDEX_PZEM_FRE_L        18
#define INDEX_PZEM_PF_H         19
#define INDEX_PZEM_PF_L         20

#define REG_VOLTAGE             0x0000
#define REG_CURRENT_L           0x0001
#define REG_CURRENT_H           0X0002
#define REG_POWER_L             0x0003
#define REG_POWER_H             0x0004
#define REG_ENERGY_L            0x0005
#define REG_ENERGY_H            0x0006
#define REG_FREQUENCY           0x0007
#define REG_PF                  0x0008
#define REG_ALARM               0x0009

#define CMD_RHR                 0x03
#define CMD_RIR                 0X04
#define CMD_WSR                 0x06
#define CMD_CAL                 0x41
#define CMD_REST                0x42

#define WREG_ALARM_THR          0x0001
#define WREG_ADDR               0x0002

#define UPDATE_TIME             200

#define RESPONSE_SIZE           32
#define READ_TIMEOUT            100
#define TIME_READ_PZEM          2000

#define INVALID_ADDRESS         0x00

typedef struct PzemData{
    float voltage;
    float current;
    float power;
    float energy;
    float frequency;
    float pf;
    uint16_t alarm;
}PzemData;

void IN_Init(void);

void IN_ReadButton(void);
bool IN_IsPressed(uint8_t index);
bool IN_IsPressed_ms(uint8_t index, uint16_t duration);

float IN_GetWaterVolume_l(void);

float IN_GetVol(void);
float IN_GetCur(void);
float IN_GetPow(void);
float IN_GetEner(void);
float IN_GetFre(void);
float IN_GetPF(void);

#endif