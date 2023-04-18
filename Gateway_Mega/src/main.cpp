#include "Arduino.h"
#include "lcd_i2c.h"

#include "input.h"
#include "pin.h"

#define SERIAL_DEBUG_BAUD       9600

#define EXCECUTING_CYCLE        50        //50ms

unsigned long time_cur = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  CLCD_Init(0x27, 2, 16);
  CLCD_ClearBuffer();
  CLCD_PrintStringBuffer(0, 0, "123");
  IN_Init();

  time_cur = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= time_cur + EXCECUTING_CYCLE){
    time_cur = millis();
    // IN_GetVol();
    // Serial.println(IN_GetWaterVolume_l());
    CLCD_DisplayScreen();
  }
}
