/*
  WEMOS_D1_general.h - Library for general functions of WEMOS_D1 sensors in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 8, 2020.
  Released into the public domain.
*/
#ifndef WEMOS_D1_general_h
#define WEMOS_D1_general_h

#include "Arduino.h"
#include "string"
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

class WEMOS_D1_general
{
  public:
    WEMOS_D1_general();
    void setupSD();
	void setupRTC();
	void getTimeStamp();
	void writeSD();
	void WiFiOff();
  private:
	int _chipSelect;
	char _TimeStampBuf[40];
	char _daysOfTheWeek[7][12];
	File _myFile;
	String _fileName;
	RTC_DS1307 _rtc;
};

#endif