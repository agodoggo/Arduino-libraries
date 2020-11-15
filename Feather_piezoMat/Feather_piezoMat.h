/*
  Feather_piezoMat.h - Library for setting up Piezo Mat Sensor for Adafruit Feather ESP32.
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/
#ifndef Feather_piezoMat_h
#define Feather_piezoMat_h

#include "Adalogger_Featherwings_general.h"

class Feather_piezoMat
{
  public:
	char* OOCSIName;
	
	float piezoV_0[20];
	float piezoV_1[20];
	float piezoV_2[20];
	float piezoV_3[20];
	int timeStampArr[20];
	
	void takePiezoMeasurement();
	
  private:
	Adalogger_Featherwings_general _myAdalogger_Featherwings_general;
	int _sizeOfPiezoArray; //600
	int _samplingInterval;
	
	const int _PIEZO_PIN_0;
	const int _PIEZO_PIN_1;
	const int _PIEZO_PIN_2;
	const int _PIEZO_PIN_3;
	
	int _piezoADC_0;
	int _piezoADC_1;
	int _piezoADC_2;
	int _piezoADC_3;
};

#endif