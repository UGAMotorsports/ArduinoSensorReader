
//testing the accelerometer algor

#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include "MovingAverage.h"


MPU6050 accelgyro;
int16_t ax, ay, az;
MovingAverage maX(8), maY(8), maZ(8);

void setup() {
	Serial.begin(9600);

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)

	// initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  accelgyro.setDLPFMode(0);
}

void loop() {
  ax = maX.getMovingAverage(accelgyro.getAccelerationX());
  ay = maY.getMovingAverage(accelgyro.getAccelerationY());
  az = maZ.getMovingAverage(accelgyro.getAccelerationZ());
  Serial.print("areal\t");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.println(az);
	
}


