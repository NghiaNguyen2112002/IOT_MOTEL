#include "input.h"

static uint8_t Request_data_pzem[] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};

uint8_t response_pzem[28];
uint32_t time_read_pzem = 0;
PzemData pzemData;

uint8_t BUTTON_PIN[NO_OF_BUTTONS] = { PIN_BT0 };
bool Flag_for_button_press[NO_OF_BUTTONS];
uint16_t Counter_button_press[NO_OF_BUTTONS];

uint32_t pulse_counter;

void IncreaseFre_ISR(void){
  pulse_counter++;
}

void ReadPzem(void){
  uint8_t timeout;

  Serial1.write(Request_data_pzem, sizeof(Request_data_pzem));

  for(timeout = 0; timeout < 100 && !Serial1.available(); timeout++);

  Serial1.readBytes(response_pzem, 25);

  for(int i = 0; i < 25; i++) {
    Serial.print(response_pzem[i], HEX); Serial.print(" ");
  }
  Serial.println("");
}

bool IsTimeRead(void){
  if (millis() - time_read_pzem >= TIME_READ_PZEM){
    time_read_pzem = millis();
    return true;
  }

  return false;
}

//=================HIGH LEVEL FUNCTION=================//
void IN_Init(void){
  pinMode(PIN_FLOWMETER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_FLOWMETER), IncreaseFre_ISR, RISING);
  Serial1.begin(9600);
  pulse_counter = 0;
  time_read_pzem = millis();
}

void IN_ReadButton(void){
  for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
    if (digitalRead(BUTTON_PIN[i]) == BUTTON_IS_PRESSED) {
      if (Counter_button_press[i] < MAX_COUNTER) {
        Counter_button_press[i]++;
      }
    } else {
      Flag_for_button_press[i] = (Counter_button_press[i] > 0) && (Counter_button_press[i] < 10);
      Counter_button_press[i] = 0;
    }
  }
}

bool IN_IsPressed(uint8_t index){
  if(index >= NO_OF_BUTTONS) return 0;

  return Flag_for_button_press[index];
}
bool IN_IsPressed_ms(uint8_t index, uint16_t duration){
	if(index >= NO_OF_BUTTONS) return 0;

	//button is read every 50ms -> counter += 1 every 50ms if button is held
	return Counter_button_press[index] >= (duration / 50);
}

float IN_GetWaterVolume_l(void){  
  float volume_l = (float)(pulse_counter / 60.0) / FACTOR_K_YF_S201;
  pulse_counter = 0;
  return volume_l;
}


float IN_GetVol(void){
  if(IsTimeRead()) ReadPzem();
  
  return (float) ((response_pzem[INDEX_PZEM_VOL_H]<<8 + response_pzem[INDEX_PZEM_VOL_L]) * SCALE_V);
}

float IN_GetCur(void){
  if(IsTimeRead()) ReadPzem();

  return (float) (((response_pzem[INDEX_PZEM_AMP1_H]<<8 + response_pzem[INDEX_PZEM_AMP1_L]) << 24)
                    | (response_pzem[INDEX_PZEM_AMP_H]<<8 + response_pzem[INDEX_PZEM_AMP_L])) * SCALE_A;
}

float IN_GetPow(void){
  if(IsTimeRead()) ReadPzem();

  return (float) (((response_pzem[INDEX_PZEM_POW1_H]<<8 + response_pzem[INDEX_PZEM_POW1_L]) << 24)
                    | (response_pzem[INDEX_PZEM_POW_H]<<8 + response_pzem[INDEX_PZEM_POW_L])) * SCALE_P;
}

float IN_GetEner(void){
  if(IsTimeRead()) ReadPzem();

  return (float) (((response_pzem[INDEX_PZEM_ENE1_H]<<8 + response_pzem[INDEX_PZEM_ENE1_L]) << 24)
                    | (response_pzem[INDEX_PZEM_ENE_H]<<8 + response_pzem[INDEX_PZEM_ENE_L])) * SCALE_E;
}

float IN_GetFre(void){
  if(IsTimeRead()) ReadPzem();

  return (float) ((response_pzem[INDEX_PZEM_FRE_H]<<8 + response_pzem[INDEX_PZEM_FRE_L]) * SCALE_F);
}

float IN_GetPF(void){
  if(IsTimeRead()) ReadPzem();

  return (float) ((response_pzem[INDEX_PZEM_PF_H]<<8 + response_pzem[INDEX_PZEM_PF_L]) * SCALE_PF);
}