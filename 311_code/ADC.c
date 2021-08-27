/*
 * adc.c
 *
 * Created: 25/09/2019 6:29PM
 *  Author: srinivas
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <math.h>
#include "ADC.h"

 // Code is from lab 7 NEED to edit.

 void adc_init(void){
	 ADMUX = 0x40;
	 ADCSRA = 0x80;
 }


 // This function converts an ADC channel and returns the result in millivolts 
 uint16_t ADC_convert_channel_to_millivolts(uint8_t channel) { 

	// Set the channel we wish to convert
	channel &=0x07;
	DDRC &=~(1<<channel);
	ADMUX |= channel ;

	// Start the conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to finish
	while ((ADCSRA & (1 << ADIF)) == 0) {
		;
	}
	// Read out the ADC counts
	uint16_t adc_count = (ADCL << 0) | (ADCH << 8);

	// Convert the counts to millivolts (use 32 bits to prevent overflow)
//	uint32_t millivolts = (uint32_t)adc_count * (uint32_t)5000 / 1024;
	//millivolts += 100;

	return (uint16_t)adc_count;
 }

void ADC_Read_calculate_Vrms_Irms_Prms(float *pv , float *pi , float *pp , float *Vrms , float *Irms , float *Prms ){
	uint8_t i;
	uint16_t temp=0;
	for(i=0 ; i<5;i++ )
	{
		temp=ADC_convert_channel_to_millivolts(0);
		
		pv[i] =(float)((temp * 5)/1024);//vin =((Dout*Vref)/1024)  Vref =5v , 10bit resluation =1024
		pi[i] =(float)pv[i]/0.01;
		pp[i] = pv[i]*pi[i];
		_delay_ms(10);
	}
		
		for(i=0 ; i<5;i++ )
		{
			*Vrms +=pv[i] * pv[i];//power 2
			*Irms +=pi[i] * pi[i];
			*Prms +=pp[i] * pp[i];
		}
			*Vrms /=5;//divide by number of sample  =5
			*Irms /=5;
			*Prms /=5;
		*Vrms =sqrt(*Vrms);//take squre
		*Irms =sqrt(*Irms);
		*Prms =sqrt(*Prms);
}

