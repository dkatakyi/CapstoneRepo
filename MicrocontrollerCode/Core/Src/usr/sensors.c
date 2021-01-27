/*
 * sensors.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */
#include "sensors.h"

uint32_t CO2Conversion()
{
 if(/*input pin read*/ == 0)
 {
  return 0;
 }

 else if((/*input pin read*/) < 0.4)  /*preheating voltage is from 0.2 to 0.4 */
 {
  return -1;
 }

 else 
 {
  int voltagedif = ((/*input pin read*/) * 1000) - 400;
  float PPM = voltagedif * 50.0/16.0; 
  
  return PPM;
 }
 
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

