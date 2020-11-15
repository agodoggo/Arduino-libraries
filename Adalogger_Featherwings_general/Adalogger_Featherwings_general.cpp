/*
  Adalogger_Featherwings_general.h - Library for general functions of Feather sensors used with Adalogger Featherwings in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include <WiFi.h>
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

#include "Adalogger_Featherwings_general.h"

Adalogger_Featherwings_general::Adalogger_Featherwings_general()
{
	ssid = "tue-psk";
	password = "!Demoday1";
	hostserver = "oocsi.id.tue.nl";
	
	int chipSelect = 4;
	_chipSelect = chipSelect;

	int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;
	_FPM_SLEEP_MAX_TIME = FPM_SLEEP_MAX_TIME;
  
	Serial.begin(9600);
}

void Adalogger_Featherwings_general::setupSD(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(_chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void Adalogger_Featherwings_general::setupRTC(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.start();
}

void Adalogger_Featherwings_general::getTimeStamp() {
    DateTime now = rtc.now();
    TimeStampBuf = now.unixtime();
}

void Adalogger_Featherwings_general::writeSD(String value){
	myFile = SD.open(fileName, FILE_WRITE);
	if (myFile) 
	{
		myFile.println(value);
		myFile.close();
		Serial.println("done.");
	}
	else
	{
		Serial.println("error opening test.txt");
	}
}