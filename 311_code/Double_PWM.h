/*
 * Double_PWM.h
 *
 * Created: 5/09/2019 1:00:03 PM
 *  Author: hraw865
 */ 


#ifndef DOUBLE_PWM_H_
#define DOUBLE_PWM_H_


void Double_PWM_initialise(void);
void PWMA_ON(void);
void PWMA_OFF(void);
void PWMB_ON(void);
void PWMB_OFF(void);
void PWM_Delay_Mode_ON(void);
void PWM_Delay_Mode_ONA(void);
void PWM_Delay_Mode_ONB(void);
int Comarator (void);
void PWM_dutyCycle_PWMA(uint8_t dutyA);
void PWM_dutyCycle_PWMB(uint8_t dutyB);
uint8_t PWM_get_duty_cycle(uint8_t * str  );//this function for extract the dutycycle

//void PWM_Delay_Mode_OFF(void);

#endif /* DOUBLE_PWM_H_ */