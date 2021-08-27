/*
 * ADC.h
 *
 * Created: 25/09/2019 6:55:29 PM
 *  Author: srinivas
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
uint16_t ADC_convert_channel_to_millivolts(uint8_t channel);
void ADC_Read_calculate_Vrms_Irms_Prms(float *pv , float *pi , float *pp , float *Vrms , float *Irms , float *Prms );
void UART_sendfloat( float  value);


#endif /* ADC_H_ */