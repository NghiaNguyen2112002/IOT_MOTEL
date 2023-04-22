#include "Arduino.h"
#include "lcd_i2c.h"

#include "input.h"
#include "pin.h"
#include "global.h"
#include "fsm.h"
#include "uart.h"

#define SERIAL_DEBUG_BAUD       9600

#define EXCECUTING_CYCLE        50        //50ms

unsigned long time_cur = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial1.begin(9600);
  CLCD_Init(0x27, 2, 16);
  
  UART_Init(PIN_ESP_TX, PIN_ESP_RX);
  
  IN_Init();
  FSM_Init();
  time_cur = millis();
  
  Serial.println("START");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(millis() >= time_cur + EXCECUTING_CYCLE){
    time_cur = millis();

    _counter_time_elapsed = (_counter_time_elapsed + 1) % 200;

    if(_time_screen >= 5) _time_screen -= 5;
    if(_time_read_data >= 5) _time_read_data -= 5;

    FSM_SystemControl();
    FSM_LcdDisplay();

    CLCD_DisplayScreen();
  }
}
