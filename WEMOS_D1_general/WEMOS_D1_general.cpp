/*
  WEMOS_D1_general.h - Library for general functions of WEMOS_D1 sensors in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 8, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

#include "WEMOS_D1_general.h"

WEMOS_D1_general::WEMOS_D1_general()
{
  int chipSelect = D4;
  _chipSelect = chipSelect;
  char _TimeStampBuf[40];
  File myFile;
  _myFile = myFile;
  String fileName = "test.txt";
  strcpy(_fileName,fileName);
  static char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  strcpy(_daysOfTheWeek,daysOfTheWeek);
  RTC_DS1307 rtc;
  _rtc = rtc;
  
  Serial.begin(9600);
}

void WEMOS_D1_general::setupSD(){
  //setup for SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(_chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void WEMOS_D1_general::setupRTC(){
  if (!_rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (!_rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void WEMOS_D1_general::getTimeStamp() {
    DateTime now = _rtc.now();
//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();

//    byte currHour = now.hour();
//    byte currMinute = now.minute();
//    byte currSecond = now.second();

    sprintf(_TimeStampBuf, "%02d/%02d/%02d(%s)-%02d:%02d:%02d", now.year(),now.month(),now.day(),_daysOfTheWeek[now.dayOfTheWeek()],now.hour(), now.minute(), now.second());
}

void WEMOS_D1_general::writeSD(){
	_myFile = SD.open(_fileName, FILE_WRITE);
	// if the file opened okay, write to it:
	if (_myFile) 
	{
		Serial.print("Writing to test.txt...");
		_myFile.println(_TimeStampBuf);
		// close the file:
		_myFile.close();
		Serial.println("done.");
	}
	else
	{
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}

void WEMOS_D1_general::WiFiOff() {
    // https://arduino.stackexchange.com/questions/43376/can-the-wifi-on-esp8266-be-disabled
    //Serial.println("diconnecting client and wifi");
    //client.disconnect();
    wifi_station_disconnect();
    wifi_set_opmode(NULL_MODE);
    wifi_set_sleep_type(MODEM_SLEEP_T);
    wifi_fpm_open();
    wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
}