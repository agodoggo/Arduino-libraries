/*
  WorkVitalitySensor.cpp - Library for general functions of sensors in Vitality@Work Project Fall 2020
  Created by Agoston Walter, November 13, 2020.
  Released into the public domain.
*/

//general libraries
#include "Arduino.h"

#include "WorkVitalitySensor.h"

// WorkVitalitySensor class
// WorkVitalitySensor::WorkVitalitySensor()
// {
	// SD_card = new SD_card;
	// rtc = new RTC;
	// wifiClock = new WiFiClock;
	// accel = new Accel;
	// toggle = new Toggle;
	// pushButton = new PushButton;
	// piezoMat = new PiezoMat;
// }

//SD card class
SD_card::SD_card()
{
	File myFile;
	_myFile = myFile;
}

void SD_card::setupSD()
{
  // Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    // Serial.println("initialization failed!");
    return;
  }
  // Serial.println("initialization done.");
}

void SD_card::writeSD()
{
	_myFile = SD.open(fileName, FILE_WRITE);
	if (_myFile) 
	{
		_myFile.println(value);
		_myFile.close();
		// Serial.println("done.");
	}
	else
	{
		// Serial.println("error opening test.txt");
	}
}
	
//RTC class
RTC::RTC()
{
	RTC_DS1307 rtc;
	_rtc = rtc;
}

void RTC::setupRTC()
{
	if (!_rtc.begin()) {
		// Serial.println("Couldn't find RTC");
		// Serial.flush();
		abort();
	}

	if (!_rtc.isrunning()) {
		// Serial.println("RTC is NOT running, let's set the time!");
		_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}
	
	_rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //doing it anyway just to have the time up to date
}

int RTC::getTimeStamp()
{
	DateTime now = _rtc.now();
    return now.unixtime();
}

//WiFiClock class
WiFiClock::WiFiClock()
{
	char* ntpServer = "pool.ntp.org";
	for (int i = 0; i < sizeof(ntpServer); i++){
		_ntpServer[i] = ntpServer[i];
	}
	
	int SysInitTime_UTC;
	_SysInitTime_UTC = SysInitTime_UTC;
	
	ssid = "tue-psk";
	password = "!Demoday1";
}

void WiFiClock::connectWiFi()
{
  WiFi.begin(_ssid,_password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      // Serial.print(".");
  }
  // Serial.println("CONNECTED");
  timeClient.begin();
}

void WiFiClock::calibrateSysTime()
{
	timeClient.update();
	_SysInitTime_UTC = _timeClient.getEpochTime() - millis()*1000;
}

int WiFiClock::getTimeStamp()
{
  return _SysInitTime_UTC + millis()*1000;
}

//WiFiData class
WiFiData::WiFiData()
{
	ssid = "tue-psk";
	password = "!Demoday1";
}

//OOCSI Data class
OOCSIData::OOCSIData()
{
	hostserver = "oocsi.id.tue.nl";
	for(int i = 0; i < sizeof(hostserver); i++){
		_hosterver[i] = hostserver[i];
	}
}


//Accel class
Accel:Accel(Adafruit_ADXL345_Unified accel)
{
	accel = Adafruit_ADXL345_Unified _accel(12345);
	_accel = accel;
}
void Accel::displaySensorDetails()
{
  sensor_t sensor;
  _accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void Accel::displayDataRate()
{
  Serial.print  ("Data Rate:    "); 
  
  switch(_accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");
}
void Accel::displayRange()
{
	Serial.print  ("Range:         +/- "); 
  
  switch(_accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");
}
void Accel::setupAccel()
{
  if(!_accel.begin())
  {
    // Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
  }
  _accel.setRange(ADXL345_RANGE_16_G);
}
void Accel::takeMeasurement()
{
	sensors_event_t event; 
	_accel.getEvent(&event);
	data[0] = event.acceleration.x;
	data[1] = event.acceleration.y;
	data[2] = event.acceleration.z;
}

//Toggle Class
Toggle::Toggle()
{
	pinMode(pinHigh,INPUT);
	pinMode(pinLow,INPUT);
	pinMode(pinLED,OUTPUT);
	state=0;
}

int Toggle::takeMeasurement()
{
	if(digitalRead(pinHigh) == HIGH)
	{
		return 1;
	}	
	else if(digitalRead(pinLow) == HIGH)
	{
		return 0;
	}
}

//PushButton Class
PushButton::PushButton()
{
	pinMode(pinA,OUTPUT);
	digitalWrite(pinA,HIGH);
	pinMode(pinB,INPUT);
	state=0;
}

int PushButton::takeMeasurement()
{
	return digitalRead(pinB);
}

//PiezoMat Class
PiezoMat::PiezoMat()
{
	pinMode(pinPiezo1,INPUT);
	pinMode(pinPiezo2,INPUT);
	pinMode(pinPiezo3,INPUT);
	pinMode(pinPiezo4,INPUT);
}

void PiezoMat::takeMeasurement()
{
	piezoV[0] = analogRead(pinPiezo1) / (1023 * 5.0);
	piezoV[1] = analogRead(pinPiezo2) / (1023 * 5.0);
	piezoV[2] = analogRead(pinPiezo3) / (1023 * 5.0);
	piezoV[3] = analogRead(pinPiezo4) / (1023 * 5.0);
}
	
