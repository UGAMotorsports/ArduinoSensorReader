
#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>

MPU6050 accelgyro;
VectorInt16 a;

void setup() {
	Serial.begin(115200);

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)

	// initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize(ACCEL_FS::A8G, GYRO_FS::G2000DPS);
}

void loop() {
  ax = accelgyro.getAccelerationX();
  ay = accelgyro.getAccelerationY();
  az = accelgyro.getAccelerationZ();
  Serial.print("areal\t");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.println(az);

  delay(100);
	
}


