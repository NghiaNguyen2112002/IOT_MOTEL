#ifndef INC_UART_H_
#define INC_UART_H_

#include "Arduino.h"
#include "SoftwareSerial.h"

void UART_Init(uint8_t pin_art_tx, uint8_t pin_uart_rx);
void UART_SendMsg(char* msg, uint8_t size);
bool UART_IsReceivedMsg(void);
uint8_t* UART_GetMsg(void);

#endif /* INC_UART_H_ */
