/*
 * JSON_PROTOCOL.c
 *
 * Created: 18/10/2019 08:22:32 م
 *  Author: srinivas
 */ 

#include <stdio.h>
#include <stdint.h>
#include "JSON_PROTOCOL.h"
void JSON_place_rmsvalue_in_jsonString(uint8_t *p_part1 , float *p_power , float *P_current , float *p_volt){
	
	sprintf(p_part1 , "{\n\t\"3\":\n\t{\n\t\t\"mfc\":\n\t\t\t{\n\t\t\t\t\"req\":\"128\",\n\t\t\t\t\"cur\":\"123\"\n\t\t\t},\n\t\t\t\"ver\"\"1.2.3\",\n\t\t\t\"param\":\n\t\t\t{\n\t\t\t\t\"pwr\":\"%dW\"\n\t\t\t\t\"freq\":\"100HZ\"\n\t\t\t\t\"curr\":\"%dmA\"\n\t\t\t\t\"volt\":\"%dV\"\n\t\t\t},\n\t\t\t\"clr\":\"ew\",\n\t\t\t\"ew\":[\"cmprStalled\",\"pistonCollision\"]\n\t\t\t\"user\":",(int)*p_power  ,(int)*P_current , (int)*p_volt);
	
}