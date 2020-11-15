/*
  Adalogger_Featherwings_general.h - Library for general functions of Feather sensors with Adalogger Featherwings in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/
#ifndef Adalogger_Featherwings_general_h
#define Adalogger_Featherwings_general_h

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"

class Adalogger_Featherwings_general
{
  public:
    Adalogger_Featherwings_general();
    void setupSD(); X
	void setupRTC(); X
	void getTimeStamp(); X
	void writeSD(String value); X
	char* ssid;
	char* password;
	char* hostserver;
	int TimeStampBuf;           
	File myFile;
	String fileName;
	RTC_PCF8523 rtc;
  private:
	int _chipSelect;
	int _FPM_SLEEP_MAX_TIME;
	char _daysOfTheWeek[7][12];
};

#endif