/*
  WEMOS_D1_Accel.h - Library for setting up ADXL345 accelerometer shield for WEMOS_D1.
  Created by Agoston Walter, November 8, 2020.
  Released into the public domain.
*/
#ifndef WEMOS_D1_Accel_h
#define WEMOS_D1_Accel_h

#include "Arduino.h"
#include "string"
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345_U.h"

class WEMOS_D1_Accel
{
  public:
    WEMOS_D1_Accel(Adafruit_ADXL345_Unified accel);
    float averageAccel[3];
	void displaySensorDetails();
    void displayDataRate();
    void displayRange();
    void setupAccel();
	void takeAccelMeasurement();
  private:
    Adafruit_ADXL345_Unified _accel;
};

#endif