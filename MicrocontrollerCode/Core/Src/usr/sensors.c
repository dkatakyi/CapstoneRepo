/*
 * sensors.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */
#include "sensors.h"

void CO2Conversion()
{
 
}
void TempConversion()
{
  float tempVal;
  
   return tempVal = 0.001/(/*input pin read*/);   /*0.001 is voltage per degree celsius conversion value*/
 }

void NoiseConversion()
{
 float PinVoltage, dBVal;
 
  PinVoltage = (/*input pin read*/) / 1024.0 * 5.0;   /* 5.0 is voltage that is powering sensor */
  return  dBVal = PinVoltage * 50.0; /* 50.0 is voltage to dB conversion value */ 
}

