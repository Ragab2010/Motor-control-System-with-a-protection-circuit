/*
 * CIR_PROTECTION_.c
 *
 * Created: 18/10/2019 10:56:45 م
 *  Author: srinivas
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "CIR_PROT.h"

void CIR_timer2_interrupt_init(){
	TCCR2 =(1<<WGM21)|(1<<CS20)|(1<<CS21);
	TIMSK |=(1<<OCIE2);
	OCR2 =249;
	sei();
}