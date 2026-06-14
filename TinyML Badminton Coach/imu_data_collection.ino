#include <Arduino_BMI270_BMM150.h>

// parameters here (to be tuned)
const int   SAMPLES_PER_WINDOW = 100;
const float MOTION_THRESHOLD = 4;
const int   COOLDOWN_MS = 2000;

bool recording = false;
int sampleCount = 0;
unsigned long lastRecordingTime = 0;

void setup() {
  Serial.begin(115200);

  IMU.begin();

  Serial.println("IMU ready; hold the board still for calibration...");
  delay(1000);
  Serial.println("Waiting for swing...");
  Serial.println();
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  if (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable()) return;

  IMU.readAcceleration(aX, aY, aZ);
  IMU.readGyroscope(gX, gY, gZ);

  float accelMag = abs(aX) + abs(aY) + abs(aZ);

  if (!recording) {
    // when not moving, wait for swing/movement
    unsigned long now = millis();
    bool cooledDown = (now - lastRecordingTime) > COOLDOWN_MS;

    if (accelMag > MOTION_THRESHOLD && cooledDown) {
      recording = true;
      sampleCount = 0;
      Serial.println("SWING/MOVEMENT DETECTED");
    }

  } else {
    // record sample
    printSample(aX, aY, aZ, gX, gY, gZ);
    sampleCount++;

    if (sampleCount >= SAMPLES_PER_WINDOW) {
      recording = false;
      lastRecordingTime = millis();
      Serial.println("SWING/MOVEMENT OVER");
      Serial.println();
      Serial.println("aX,aY,aZ,gX,gY,gZ");  // reprint header for next window
    }
  }
}

void printSample(float aX, float aY, float aZ, float gX, float gY, float gZ) {
  Serial.print(aX, 4); Serial.print(",");
  Serial.print(aY, 4); Serial.print(",");
  Serial.print(aZ, 4); Serial.print(",");
  Serial.print(gX, 4); Serial.print(",");
  Serial.print(gY, 4); Serial.print(",");
  Serial.println(gZ, 4);
}
