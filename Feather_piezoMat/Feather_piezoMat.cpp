/*
  Feather_piezoMat.cpp - Library for setting up Piezo Mat Sensor for Adafruit Feather ESP32.
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/
#include "Adalogger_Featherwings_general.h"
#include "Feather_piezoMat.h"

Feather_piezoMat::Feather_piezoMat()
{
	
  Adalogger_Featherwings_general myAdalogger_Featherwings_general;
  _myAdalogger_Featherwings_general = myAdalogger_Featherwings_general;
  
  OOCSIName = "Vitality@Work/PiezoSensorMat";
  
  float piezoV_0[_sizeoOfPiezoArray];
  float piezoV_1[_sizeoOfPiezoArray];
  float piezoV_2[_sizeoOfPiezoArray];
  float piezoV_3[_sizeoOfPiezoArray];
  
  int timeStampArr[_sizeoOfPiezoArray];
  
  int sizeoOfPiezoArray = 20;
  _sizeoOfPiezoArray = sizeoOfPiezoArray;
  
  int samplingInterval = 1000; //ms
  _samplingInterval = samplingInterval;
  
  int samplingIntervalAvg = 50; //ms
  _samplingIntervalAvg = samplingInterval;
  
  const int PIEZO_PIN_0 = A2;
  _PIEZO_PIN_0 = PIEZO_PIN_0;
  const int PIEZO_PIN_1 = A3;
  _PIEZO_PIN_1 = PIEZO_PIN_1;
  const int PIEZO_PIN_2 = A4;
  _PIEZO_PIN_2 = PIEZO_PIN_2;
  const int PIEZO_PIN_3 = A7;
  _PIEZO_PIN_3 = PIEZO_PIN_3;
  
  pinMode(PIEZO_PIN_0,INPUT);
  pinMode(PIEZO_PIN_1,INPUT);
  pinMode(PIEZO_PIN_2,INPUT);
  pinMode(PIEZO_PIN_3,INPUT);

  int piezoADC_0;
  _piezoADC_0 = piezoADC_0;
  int piezoADC_1;
  _piezoADC_1 = piezoADC_1;
  int piezoADC_2;
  _piezoADC_2 = piezoADC_2;
  int piezoADC_3;
  _piezoADC_3 = piezoADC_3;
  
  Serial.begin(9600);
}

void Feather_piezoMat::takeAccelMeasurement(){
	for(int i = 0; i < _sizeoOfPiezoArray; i++){
		for(int j = 0; j < _sizeOfPiezoArray; j++){
			_piezoADC_0 = analogRead(_PIEZO_PIN_0);
			_piezoADC_1 = analogRead(_PIEZO_PIN_1);
			_piezoADC_2 = analogRead(_PIEZO_PIN_2);
			_piezoADC_3 = analogRead(_PIEZO_PIN_3);

			piezoV_0[i] = _piezoADC_0 / (1023.0 * 5.0) / _sizeOfPiezoArray;
			piezoV_1[i] = _piezoADC_1 / (1023.0 * 5.0) / _sizeOfPiezoArray;
			piezoV_2[i] = _piezoADC_2 / (1023.0 * 5.0) / _sizeOfPiezoArray;
			piezoV_3[i] = _piezoADC_3 / (1023.0 * 5.0) / _sizeOfPiezoArray;
			delay(_samplingIntervalAvg)
		}
		
		_myAdalogger_Featherwings_general.getTimeStamp();
		timeStampArr[i] = _myAdalogger_Featherwings_general.TimeStampBuf;
		
		// Serial.print("piezoV_0:");Serial.print(piezoV_0);Serial.print(", ");
		// Serial.print("piezoV_1:");Serial.print(piezoV_1);Serial.print(", ");
		// Serial.print("piezoV_2:");Serial.print(piezoV_2);Serial.print(", ");
		// Serial.print("piezoV_3:");Serial.print(piezoV_3);Serial.print(", ");
		// Serial.println();
		
		delay(_samplingInterval);
	}
//  getTimeStamp();
}