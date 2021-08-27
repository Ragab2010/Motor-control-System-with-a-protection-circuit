/*
 * UART.h
 *
 * Created: 16/09/2019 6:01:57 PM
 *  Author: hraw865
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <math.h>

void uart_initialise(void);
void uart_transmit(uint8_t* byte_array, uint32_t byte_array_length);
void uart_transmit_byte(uint8_t byte);
void uart_convert_ASCII(uint32_t data);
uint8_t UART_recieveByte(void);
void UART_sendString(const uint8_t *Str);
void UART_receiveString(uint8_t *Str);

#endif /* UART_H_ */