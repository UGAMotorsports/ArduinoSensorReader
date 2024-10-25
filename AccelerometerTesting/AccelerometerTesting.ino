
//testing the accelerometer algor

#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <MovingAverage.h>

MPU6050 accelgyro;
int16_t ax, ay, az;
MovingAverage maX(20), maY(20), maZ(20);

void setup() {
	Serial.begin(115200);

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)

	// initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize(ACCEL_FS::A8G, GYRO_FS::G2000DPS); //range of 8g [-4g, 4g]
  accelgyro.CalibrateAccel(5);

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
	
  delay(20);
}


