/*
 * sensors.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */
#include "sensors.h"

float CO2Conversion(uint32_t input) 
{
 if(input == 0)
 {
  return 0; /*this should print fault*/
 }

 else if((input) < 0.4)  /*preheating voltage is from 0.2 to 0.4 */
 {
  return -1; /* this should print "preheating CO2"*/
 }

 else 
 {
  float voltagedif = ((input) * 1000) - 400; /*this is for voltage to PPM conversion*/
  return voltagedif * 50.0/16.0; 
  }
 /*CO2 has a 100ms delay before looping*/
}


float TempConversion(uint32_t input)
{
  return (input )* 5/10.24;   /* voltage to degree celsius conversion*/
  /* has an 500ms delay before looping*/
 }

float NoiseConversion(uint32_t input)
{
 float PinVoltage;
  PinVoltage = (input) / 1024.0 * 5.0;   /* 5.0 is voltage that is powering sensor */
  return PinVoltage * 50.0; /* 50.0 is voltage to dB conversion value */
 
 
 /* has an 125ms delay before looping*/
}

