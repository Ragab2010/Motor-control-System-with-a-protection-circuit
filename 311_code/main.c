/*
 * 311_code.c
 *
 * Created: 4/09/2019 12:41:02 PM
 * Author : srinivas
 */ 
#define F_CPU 8000000UL

#include <stdio.h>
#include <avr/io.h>
#include "Double_PWM.h"
#include "JSON_PROTOCOL.h"
#include "UART.h"
#include "ADC.h"
#include "CIR_PROT.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/*gloable variable */
#define N 5
#define THRSSHOTCURRENT 300
float volt[N] ,current[N] ,power[N];
float voltrms=0 ,currentrms=0 ,powerrms=0;
uint8_t UART_str_buffer[30];
uint8_t PWM_duty_cycle=0;
uint8_t JSON_str_jsonpart1[260];
uint8_t *JSON_str_jsonpart2="\n\t\t\t{\n\t\t\t\t\"pistonCollision\": \"no\"\n\t\t\t}\n\t}\n}\n";

/*interrupt every 1 microsecond*/
ISR(TIMER2_COMP_vect){
	if((currentrms/1000) < THRSSHOTCURRENT ){ //to make the current by mA
		//BY DEFAULT PWM WORK 
			//PWMA_ON();
			//PWMB_ON();
	}else{
			PWMA_OFF();
			PWMB_OFF();
			UART_sendString("PWMA,PWMA PINS IS CLOSED..THE CURRENT IS VERY HIGH\n");
	}
}

int main(void)
{   
	/*initialize modules*/
	Double_PWM_initialise();
	adc_init();
	uart_initialise();
	/*here the circuit protection */
	CIR_timer2_interrupt_init();
 	/*Enable PWMA , PWMB*/
//  	PWMA_ON();
//  	PWMB_ON();
//  	UART_sendString("PWMA,PWMA INITIAL WORK\n");
	_delay_ms(50);
	
	
 while(1){
	/*atmega send to putty that's micro is ready*//* send in form :{"3":{"mfc":{"req":"130"}}} */
	UART_sendString("UART IS READY .. SEND THE MESSAGE :\n");
	_delay_ms(50);
	/*receive message from putty and put it on buffer array */
	UART_receiveString(UART_str_buffer);
	_delay_ms(50);
	

	/*duty cycle from message*/
	PWM_duty_cycle = PWM_get_duty_cycle(UART_str_buffer);
	
	
	/*put duty cycle for PWM*/
	PWM_dutyCycle_PWMA(PWM_duty_cycle);
	PWM_dutyCycle_PWMB(PWM_duty_cycle);
	UART_sendString("PWMA,PWMA  WORK WITH DUTYCYCLE.\n");
	_delay_ms(50);
	
	/*read the volt and current and power by ADC*/
	ADC_Read_calculate_Vrms_Irms_Prms(volt , current , power , &voltrms , &currentrms , &powerrms);
	/*place (volt,current ,power)RMS reading in json string*/
	JSON_place_rmsvalue_in_jsonString(JSON_str_jsonpart1 ,&powerrms , &currentrms  ,&voltrms );
	
	/*send json string   to putty  */
	UART_sendString("JSON STRING:\n");
	UART_sendString(JSON_str_jsonpart1);//frist part
	UART_sendString(JSON_str_jsonpart2);//second part
	_delay_ms(500);
	

	 
	 
	 
	 
	 
 }
	
}


