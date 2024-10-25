
//testing the accelerometer algor

#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include "MovingAverage.h"


MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
	Serial.begin(9600);

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)

	// initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  accelgyro.setDLPFMode(0);
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print("areal\t") 	      ;
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.println(az);
	
}


