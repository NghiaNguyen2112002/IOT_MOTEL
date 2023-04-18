#include "input.h"

static uint8_t Request_data_pzem[] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};
SoftwareSerial pzemSerial(PIN_PZEM_RX, PIN_PZEM_TX);
PzemData pzemData;

unsigned long pulse_counter;

void IncreaseFre_ISR(void){
  pulse_counter++;
}

void ReadPzem(void){
  uint8_t timeout;
  uint8_t response[28];

  pzemSerial.write(Request_data_pzem, sizeof(Request_data_pzem));

  for(timeout = 0; timeout < 100 && !pzemSerial.available(); timeout++);

  pzemSerial.readBytes(response, 25);

  // for(int i = 0; i < 25; i++)Serial.print(response[i], HEX); Serial.println(" ");
}

//=================HIGH LEVEL FUNCTION=================//
void IN_Init(void){
  pinMode(PIN_FLOWMETER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_FLOWMETER), IncreaseFre_ISR, RISING);
  pzemSerial.begin(9600);
  pulse_counter = 0;
}

float IN_GetWaterVolume_l(void){
  float volume_l = (float)(pulse_counter / 60.0) / FACTOR_K_YF_S201;
  pulse_counter = 0;
  return volume_l;
}


float IN_GetVol(void){
  // ReadPzem();
}

float IN_GetCur(void){

}

float IN_GetPow(void){

}

float IN_GetEner(void){

}

float IN_GetFre(void);
float IN_GetPF(void);