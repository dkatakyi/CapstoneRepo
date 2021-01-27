/*
 * sensors.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */
#include "sensors.h"

uint32_t CO2Conversion()
{
 
}
uint32_t TempConversion()
{
  float tempVal;
  
   return tempVal = 0.001/(/*input pin read*/);   /*0.001 is voltage per degree celsius conversion value*/
 }

uint32_t NoiseConversion()
{
 float PinVoltage, dBVal;
 
  PinVoltage = (/*input pin read*/) / 1024.0 * 5.0;   /* 5.0 is voltage that is powering sensor */
  return  dBVal = PinVoltage * 50.0; /* 50.0 is voltage to dB conversion value */ 
}

