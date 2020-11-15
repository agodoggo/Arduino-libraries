/*
  Feather_general.cpp - Library for general functions of Feather sensors used with Adalogger Featherwings in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/

//for NTP server comm
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "Wire.h"
#include "RTClib.h"
#include "OOCSI.h"

#include "Feather_general.h"

Feather_general::Feather_general()
{
	//wifi variables
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP);
	
	ssid = "tue-psk";
	password = "!Demoday1";
	hostserver = "oocsi.id.tue.nl";
	
	int systemInitTime_UTC;
	_systemInitTime_UTC = systemInitTime_UTC;
	
	char* ntpServer = "pool.ntp.org";
	for (int i = 0; i < sizeof(); i++){
		_ntpServer[i] = ntpServer[i];
	}
	
	int chipSelect = 33;
	_chipSelect = chipSelect;

	int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;
	_FPM_SLEEP_MAX_TIME = FPM_SLEEP_MAX_TIME;
  
	Serial.begin(9600);
}

void Feather_general::setupSD(){
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(_chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void Feather_general::setupTime(){ //for use with the Adalogger FeatherWings
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("CONNECTED");
  int NTPTime_UTC = NTPClient.getEpochTime();
  systemInitTime_UTC = NTPTime_UTC - millis()*1000;
}
void Feather_general::connectWiFi(){
	WiFi.begin(ssid,password);
	while (WiFi.status() != WL_CONNECTED) {
		delay (500);
	}
}
void Feather_general::initializeTime(){
	timeClient.begin();
	timeClient.update();
	timeClient.getEpochTime()
}
void Feather_general::getTimeStamp() {
    TimeStampBuf = systemInitTime_UTC + 1000*millis();
}

void Feather_general::writeSD(String value){
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