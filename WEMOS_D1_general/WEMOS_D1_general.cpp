/*
  WEMOS_D1_general.h - Library for general functions of WEMOS_D1 sensors in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 8, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
// #include "ESP8266WiFi.h"
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

#include "WEMOS_D1_general.h"

WEMOS_D1_general::WEMOS_D1_general()
{
	ssid = "tue-psk";
	password = "!Demoday1";
	hostserver = "oocsi.id.tue.nl";
	
	int chipSelect = D4;
	_chipSelect = chipSelect;

	int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;
	_FPM_SLEEP_MAX_TIME = FPM_SLEEP_MAX_TIME;
  
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
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void WEMOS_D1_general::getTimeStamp() {
    DateTime now = rtc.now();
    TimeStampBuf = now.unixtime();
}

void WEMOS_D1_general::writeSD(String value){
	myFile = SD.open(fileName, FILE_WRITE);
	// if the file opened okay, write to it:
	if (myFile) 
	{
		myFile.println(value);
		// close the file:
		myFile.close();
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
    wifi_fpm_do_sleep(_FPM_SLEEP_MAX_TIME);
}