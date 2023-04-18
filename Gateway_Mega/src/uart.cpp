#include "uart.h"

SoftwareSerial espSerial(PIN_ESP_TX, PIN_ESP_RX);


void UART_Init(uint8_t pin_art_tx, uint8_t pin_uart_rx){
    espSerial.begin(9600);
}

void UART_SendMsg(char* msg, uint8_t size){
    espSerial.write(msg, size);
}

String UART_GetMsg(void){
    uint8_t timeout;
    for(timeout = 0; timeout < 100 && !espSerial.available(); timeout++);
    
    return espSerial.readString();
}