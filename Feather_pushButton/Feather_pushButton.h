/*
  Feather_pushButton.h - Library for general functions of Feather sensor with pushButton in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/
#ifndef Feather_pushButton_h
#define Feather_pushButton_h

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

class Feather_pushButton
{
  public:
    Feather_pushButton();
	
    void setupSD();
	void setupTime();
	void getTimeStamp();
	void writeSD(String value);
	
	int chipSelect;
	
	char* ssid;
	char* password;
	char* hostserver;
	
	int TimeStampBuf;
	File myFile;
	String fileName;
	
  private:
	int _FPM_SLEEP_MAX_TIME;
	char* _ntpServer;
	int _systemInitTime_UTC;
};

#endif