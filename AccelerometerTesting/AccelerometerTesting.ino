
//testing the accelerometer algor

#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <MovingAverage.h>

MPU6050 accelgyro;
int16_t ax, ay, az;
VectorInt16 rawA;
MovingAverage maX(10), maY(10), maZ(10);


void setup() {
	Serial.begin(115200);

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)

	// initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize(); 
  accelgyro.CalibrateAccel(5);
  accelgyro.CalibrateGyro(5);
  accelgyro.setFullScaleAccelRange(1); //range of 8g [-4g, 4g]
}

void loop() {
    accelgyro.getAcceleration(&rawA.x, &rawA.y, &rawA.z);

    ax = maX.getMovingAverage(rawA.x);
    ay = maY.getMovingAverage(rawA.y);
    az = maZ.getMovingAverage(rawA.z);
    Serial.print("areal\t");
    Serial.print(ax);
    Serial.print("\t");
    Serial.print(ay);
    Serial.print("\t");
    Serial.println(az);

    delay(10);

}


