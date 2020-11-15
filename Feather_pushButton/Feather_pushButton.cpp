/*
  Feather_pushButton.cpp - Library for general functions of Feather sensors used with Adalogger Featherwings in Vitality@Work Project Fall 2020
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

#include "Feather_pushButton.h"

Feather_pushButton::Feather_pushButton()
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
