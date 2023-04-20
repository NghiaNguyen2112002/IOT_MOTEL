#include "uart.h"

SoftwareSerial espSerial(3, 4);


void UART_Init(uint8_t pin_art_tx, uint8_t pin_uart_rx){
    espSerial.begin(9600);
}

void UART_SendMsg(String msg){
    Serial.println(msg);
    espSerial.print(msg);
}

bool UART_IsReceivedMsg(void){
    return espSerial.available();
}

String UART_GetMsg(void){
    String str = ""; 
    if(espSerial.available()) {
        str =  espSerial.readString();
        Serial.println(str);
    }

    return str;
}