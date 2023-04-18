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


//===================YF_S201===================//
#define FACTOR_K_YF_S201        7.5

//===================PZEM 004T 100A V3.0===================//
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