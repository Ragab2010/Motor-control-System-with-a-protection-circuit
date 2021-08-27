/*
 * Double_PWM.c
 *
 * Created: 5/09/2019 12:59:27 PM
 *  Author: lang606
 */ 
// this code sets up counter1 for an 4kHz, 10bit, Phase Corrected PWM
// @ 16Mhz Clock


#include <avr/io.h>
#include <ctype.h>
#include <stdlib.h>
#include "Double_PWM.h"

void PWMA_ON(void){
	TCCR1A |= (1 << COM1A1);
	
	
	//OCR1A = 128;
	//OCR1A = 64;
	//OCR1A = 32;
}

void PWMB_ON(void){
	TCCR1A |= (1 << COM1B1);
	//TCCR2 |=(1<<COM20)|(1<<COM21) ;//OCR2
	//OCR1B = 128;
	//OCR1B = 64;
	//OCR1B = 32;
	//OCR2  = 64;
}
void PWMA_OFF(void){
	TCCR1A &= ~(1 << COM1A1);
	//OCR1A = 128;
	OCR1A = 0;
	//OCR1A = 32;
}

void PWMB_OFF(void){
	TCCR1A &= ~(1 << COM1B1);
	TCCR2 &= ~((1<<COM20)|(1<<COM21)) ;
	//OCR1B = 128;
	OCR1B = 0;
	//OCR1B = 32;
	OCR2  = 0;
}


void PWM_dutyCycle_PWMB(uint8_t dutyB){

	OCR1B = 255-dutyB;
	OCR2  = 255-dutyB;//PB3 OCR2
}

void PWM_dutyCycle_PWMA(uint8_t dutyA){

	OCR1A = dutyA;

}

void PWM_Delay_Mode_ONA(void)
{
	TCCR1A |= (1 << COM1A1);
	//TCCR1A |= (1 << COM1B1);
	OCR1A = 255;
	//OCR1B = 255;
	// set PWM for 100% duty cycle @ 8bit
}

void PWM_Delay_Mode_ONB(void)
{
	//TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
	//OCR1A = 255;
	OCR1B = 255;
	// set PWM for 100% duty cycle @ 8bit
}


void Double_PWM_initialise(void)
{
	//Duty cycle
	// 128 = 50%
	// 64  = 75%

	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	//DDRB |= (1 << DDB3);
	// PB1 is now an output
	
	
	// set PWM for 50% duty cycle @ 8bit
	//OCR1A = 128;
	//OCR1B = 128;
	
	// set PWM for 75% duty cycle @ 8bit
	OCR1A = 64;
	OCR1B = 64;

	OCR2 = 64;//PB3
	// set PWM for 100% duty cycle @ 8bit
	//OCR1A = 32;
	//OCR1B = 32;


	TCCR1A |= (1 << COM1A1);
	// set non-inverting mode
	TCCR1A |= (1 << COM1B1) ;

	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	// Set 8-bit fast PWM
	
	
	TCCR2 |=(1<<WGM20) |(1<<WGM21)| (1<<COM20)|(1<<COM21)|(1<<CS22) ;

	//TCCR1B |= (1 << CS10) | (1 << CS12); //1024 prescaler
	
	//TCCR1B |= (1 << CS12); // 256 prescaler
	
	TCCR1B |= (1 << CS10) | (1 << CS11); // 64 prescaler for 500 Hz
	//TCCR1B |= (1 << CS11); //8 prescaler
	// set prescaler to 8 and starts PWM
	
}


uint8_t PWM_get_duty_cycle(uint8_t * str  ){
	unsigned int duty;
	uint8_t pduty[5];
	uint8_t *first , *second, *three, flage=0 , i=0;
	first = second = three= str;
	second++;
	three +=2;
	do{
		if(isdigit(*first)&&isdigit(*second) &&isdigit(*three)){
			pduty[i++]=*first;
			pduty[i++]=*second;
			pduty[i++]=*three;
			pduty[i]='\0';
			flage=1;
			}else if(isdigit(*first)&&isdigit(*second)){
			pduty[i++]=*first;
			pduty[i++]=*second;
			pduty[i]='\0';
			flage=1;
			}else if(((*(first-2)) ==':')&&isdigit(*first)){
			pduty[i++]=*first;
			pduty[i]='\0';
			flage=1;
			}else{
			first++;
			second++;
			three++;
			flage=0;
		}
	}while(!flage);
	duty =atoi(pduty);
	return duty;
}


