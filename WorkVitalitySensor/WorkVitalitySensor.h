/*
  WorkVitalitySensor.h - Library for general functions of sensors in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 11, 2020.
  Released into the public domain.
*/
#ifndef WorkVitalitySensor_h
#define WorkVitalitySensor_h

//general libraries
#include "Arduino.h"

// #include Sd card libraries
#include <SPI.h>
#include <SD.h>

// #include RTC libraries
#include <Wire.h>
#include "RTClib.h"

// #include Wificlock libraries (specific to ESP32)
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// #include accel libraries
// #include <Wire.h> (already included by RTC library)
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


// class WorkVitalitySensor
// {
  // public:
    // WorkVitalitySensor();
	
	// SD card component
	// SD_card *SD_card;
	
	// RTC component
	// RTC *rtc;
	
	// WiFiClock component
	// WiFiClock *wifiClock;
	
	// accelerometer class
	// Accel *accel;
	
	// toggle class
	// Toggle *toggle;
	
	// push button class
	// PushButton *pushButton;
	
	// piezo mat class
	// PiezoMat *piezoMat;
// }
class SD_card
{
  public:
	SD_card();
	
	//pins
	int chipSelect;
	
	//file variables
	String fileName;
	
	//functions
	void setupSD();
	void writeSD();
  private:
	File _myFile;
};


//accessory classes
class RTC
{
  public:
	RTC();
	
	//functions
	void setupRTC();
	int getTimeStamp();
  private:
	//RTC object for Wemos D1 Shield
	RTC_DS1307 _rtc;
};

class WiFiClock
{
  public:
	WiFiClock();
	//functions
	void connectWiFi();
	void calibrateSysTime();
	int getTimeStamp();
	
	//wifi data
	char* ssid;
	char* password;
	
	//NTP Client
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP);

	
  private:
	//NTP server data
	char* _ntpServer;
	int _SysInitTime_UTC; //so that we only need to connect to the server on startup to calibrate system time
};

//Data Classes
class WiFiData
{
  public:
	WiFiData();
	
	//data
	char* ssid;
	char* password;
};

class OOCSIData
{
public:
	OOCSIData();
	
	//data
	char* OOCSIName;

private:
	char* _hostserver;
};


//data gathering classes
class Accel{
  public:
	Accel(Adafruit_ADXL345_Unified _accel);
	
	//data array
	int data[3];//[x,y,z]
	
	//functions
	void displaySensorDetails();
	void displayDataRate();
	void displayRange();
	void setupAccel();
	void takeMeasurement();
  private:
	//accel object
	Adafruit_ADXL345_Unified _accel;
};

class Toggle{
	public:
		Toggle();
		//pins
		int pinHigh;
		int pinLow;
		int pinLED;
		
		//variables
		int state;
	
		//functions
		int takeMeasurement();
};

class PushButton{
	public:
		PushButton();
		//pins
		int pinA;
		int pinB;
		int pinLED;
		
		//variables
		int state;
		
		//functions
		int takeMeasurement();
};
class PiezoMat{
  public:
	PiezoMat();
	
	//pins
	int pinPiezo1;
	int pinPiezo2;
	int pinPiezo3;
	int pinPiezo4;
	
	float piezoV[4];
	
	//functions
	void takeMeasurement();
};

#endif