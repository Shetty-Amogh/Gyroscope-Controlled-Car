#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>

Adafruit_MPU6050 mpu;

SoftwareSerial BT(2, 3);

void setup() {
  BT.begin(115200);
  Serial.begin(115200);
  while (!Serial);

  if (!mpu.begin()) {
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  // Convert to gravity‑based tilt (pitch & roll)
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll  = atan2( ay, az) * 180.0 / PI;
  // -ve pitch is right 
  // -ve roll is down

  // 0-30 : slow
  // 30-75 : quick
  // 75-90 : max


  BT.print("P:");
  BT.print(pitch, 1);
  BT.print(",R:");
  BT.print(roll, 1);
  BT.println();
  Serial.println("uploaded");
  delay(100);

}