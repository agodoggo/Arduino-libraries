/*
  WEMOS_D1_Accel.h - Library for setting up ADXL345 accelerometer shield for WEMOS_D1.
  Created by Agoston Walter, November 8, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345_U.h"

#include "WEMOS_D1_Accel.h"
#include "WEMOS_D1_general.h"

WEMOS_D1_Accel::WEMOS_D1_Accel(Adafruit_ADXL345_Unified accel)
{
  WEMOS_D1_general myWEMOS_D1_general;
  _myWEMOS_D1_general = myWEMOS_D1_general;
	
  accel = Adafruit_ADXL345_Unified(12345);
  _accel = accel;
  
  float AccelX[_sizeOfAccelArray];
  float AccelY[_sizeOfAccelArray];
  float AccelZ[_sizeOfAccelArray];
  
  int timeStampArr[_sizeOfAccelArray];
  
  OOCSIName = "Vitality@Work/Accelerometer1";
  
  int sizeOfAccelArray = 20;
  _sizeOfAccelArray = sizeOfAccelArray;
  
  int samplingInterval = 1000; //ms
  _samplingInterval = samplingInterval;
  
  int samplingIntervalAvg = 50; //ms
  _samplingIntervalAvg = samplingInterval;
  
  Serial.begin(9600);
}

void WEMOS_D1_Accel::displaySensorDetails()
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

void WEMOS_D1_Accel::displayDataRate()
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
void WEMOS_D1_Accel::displayRange()
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
void WEMOS_D1_Accel::setupAccel()
{
  if(!_accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
  }
  _accel.setRange(ADXL345_RANGE_16_G);
}
void WEMOS_D1_Accel::takeAccelMeasurement(){
	for(int i = 0; i < _sizeOfAccelArray; i++){
		for(int j = 0; j < _sizeOfPiezoArray; j++){
			sensors_event_t event; 
			_accel.getEvent(&event);
			AccelX[i] = event.acceleration.x / _sizeOfPiezoArray;
			AccelY[i] = event.acceleration.y / _sizeOfPiezoArray;
			AccelZ[i] = event.acceleration.z / _sizeOfPiezoArray;
			delay(_samplingIntervalAvg);
		}
		_myWEMOS_D1_general.getTimeStamp();
		timeStampArr[i] = _myWEMOS_D1_general.TimeStampBuf;
		delay(_samplingInterval);
	}
  }
}