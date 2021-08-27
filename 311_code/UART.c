/*
 * UART.c
 *
 * Created: 16/09/2019 6:01:43 PM
 *  Author: hraw865
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"

void uart_initialise(void) 
{

	UCSRA = 0;
	UCSRB = (1 << RXEN)|(1<<TXEN);
	UCSRC= (1 << URSEL)| (1 << UCSZ1)|(1<<UCSZ0);
	
	// Setting baud rate of 9600
	UBRRH =	0;
	UBRRL = 51; 
	
}

// transmits the data in ASCII
void uart_convert_ASCII(uint32_t data) {

	if(data == 0) {
		uart_transmit_byte(48);
		return;
	}

	uint32_t temp, i;
	// This equation gets the number length
	uint32_t numLen= floor(log10(data)) + 1;
	uint32_t numReverse[numLen];

	temp = data;

	for (i = numLen; i > 0; i--){
		numReverse[i - 1] = (temp % 10) + 48;
		temp = temp / 10;
	}

	for (i = 0; i < numLen; i++){
		uart_transmit_byte(numReverse[i]);
	}
	uart_transmit_byte(13);
	uart_transmit_byte(10);
}

// This function transmits a single byte via the UART
void uart_transmit_byte(uint8_t byte)
{
	
	// Wait for the UART data register empty flag
	while ((UCSRA & 0x20) == 0) {	
		;
	}
	// Put the byte to be sent into the data register  
	UDR = byte;
	
}
uint8_t UART_recieve_Byte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(!(UCSRA &(1<<RXC))){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}


// This function transmits an array of bytes via the UART
void uart_transmit(uint8_t* byte_array, uint32_t byte_array_length)
{
	
	// Loop through each byte
	for (uint32_t i = 0; i < byte_array_length; i++){
		
		//Transmit it via the UART
		uart_transmit_byte(byte_array[i]);
		//uart_transmit_byte(32);
	}
	//uart_transmit_byte(10);
	
}
void UART_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		uart_transmit_byte(Str[i]);
		i++;
	}
	
}

void UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_recieve_Byte();
	while((Str[i-1] != '\n') && (Str[i] != '\r'))
	{
		i++;
		Str[i] = UART_recieve_Byte();
	}
	Str[--i] = '\0';


}

