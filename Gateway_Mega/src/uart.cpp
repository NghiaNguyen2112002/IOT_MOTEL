#include "uart.h"

void UART_Init(uint8_t pin_art_tx, uint8_t pin_uart_rx){
    Serial1.begin(9600);
}

void UART_SendMsg(String msg){
    Serial.println(msg);
    Serial1.print(msg);
}

bool UART_IsReceivedMsg(void){
    return Serial1.available();
}

String UART_GetMsg(void){
    String str = ""; 
    if(Serial1.available()) {
        str =  Serial1.readString();
        Serial.println(str);
    }

    return str;
}