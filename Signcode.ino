// #include <Wire.h>
// #include <SoftwareSerial.h>
// #include <MPU6050.h>

// SoftwareSerial bluetooth(10, 11); // RX, TX

// MPU6050 mpu;

// String mapFlexGesture(int flex1, int flex2, int flex3, int flex4) {
//   if (flex1 > 840 && flex2 > 810 && flex3 > 870 && flex4 > 815) return "Hello";
//   else if (flex1 < 810 && flex2 < 800 && flex3 > 850 && flex4 < 800) return "Yes";
//   else if (flex1 < 810 && flex2 < 770 && flex3 < 850 && flex4 < 770) return "Hello";
//   else if (flex1 > 850 && flex2 < 820 && flex3 > 870 && flex4 < 800) return "Stop";
//   else if (flex1 < 800 && flex2 < 770 && flex3 < 850 && flex4 < 770) return "Thank You";
//   else if (flex1 > 820 && flex2 > 830 && flex3 > 860 && flex4 < 810) return "Good Morning";
//   else if (flex1 < 790 && flex2 < 780 && flex3 < 810 && flex4 < 780) return "Good Night";
//   else if (flex1 > 870 && flex2 > 850 && flex3 < 800 && flex4 > 860) return "I Love You";
//   else if (flex1 < 750 && flex2 > 810 && flex3 < 830 && flex4 > 820) return "Sorry";
//   else if (flex1 > 880 && flex2 < 790 && flex3 > 860 && flex4 > 870) return "Please";
//   else if (flex1 > 830 && flex2 < 800 && flex3 > 840 && flex4 < 820) return "Help";
//   else if (flex1 < 770 && flex2 > 850 && flex3 > 870 && flex4 > 840) return "Welcome";
//   else if (flex1 > 860 && flex2 < 780 && flex3 > 850 && flex4 < 810) return "Water";
//   else if (flex1 < 780 && flex2 > 800 && flex3 < 810 && flex4 < 780) return "Food";
//   else if (flex1 > 850 && flex2 > 860 && flex3 < 780 && flex4 > 870) return "Goodbye";
//   else if (flex1 < 750 && flex2 < 760 && flex3 > 830 && flex4 > 850) return "Congratulations";
//   else {
//     const char gestures[] = "abcdefghijklmnopqrstuvwxyz";
//     int index = ((flex1 + flex2 + flex3 + flex4) / 160) % 26;
//     return "Letter: " + String(gestures[index]);
//   }
// }

// String mapMPUGesture(int ax, int ay, int az, int gx, int gy, int gz) {
//   if (ax < -12000) return "Tilt Left";
//   else if (ax > 12000) return "Tilt Right";
//   else if (ay < -12000) return "Tilt Forward";
//   else if (ay > 12000) return "Tilt Backward";
//   else if (abs(gx) > 25000 || abs(gy) > 25000 || abs(gz) > 25000) return "Shake";
//   else if (az < 1000) return "Free Fall or Drop";
//   else return "";
// }

// void setup() {
//   Serial.begin(9600);
//   bluetooth.begin(9600);

//   Wire.begin();
//   mpu.initialize();

//   if (!mpu.testConnection()) {
//     Serial.println("MPU6050 connection failed!");
//     while (1);
//   }

//   Serial.println("Setup complete.");
// }

// void loop() {
//   int flex1 = analogRead(A0);
//   int flex2 = analogRead(A1);
//   int flex3 = analogRead(A2);
//   int flex4 = analogRead(A3);

//   int16_t ax, ay, az, gx, gy, gz;
//   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

//   String flexGesture = mapFlexGesture(flex1, flex2, flex3, flex4);
//   String mpuGesture = mapMPUGesture(ax, ay, az, gx, gy, gz);

//   if (flexGesture != "") {
//     bluetooth.println("Flex Gesture: " + flexGesture);
//     Serial.println("Flex Gesture: " + flexGesture);
//   }

//   if (mpuGesture != "") {
//     bluetooth.println("MPU Gesture: " + mpuGesture);
//     Serial.println("MPU Gesture: " + mpuGesture);
//   }

//   delay(1000);
// }

#include <Wire.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>

SoftwareSerial bluetooth(10, 11); // RX, TX

MPU6050 mpu;

String lastMPUGesture = "";

int16_t prev_ax = 0, prev_ay = 0, prev_az = 0;
int16_t prev_gx = 0, prev_gy = 0, prev_gz = 0;

const int MPU_THRESHOLD = 3000;  // Adjust for sensitivity
//Values are chosen based on the analysis of actuall datasets and not random .
String mapFlexGesture(int flex1, int flex2, int flex3, int flex4) {
  if (flex1 > 840 && flex2 > 810 && flex3 > 870 && flex4 > 815) return "Hello";
  else if (flex1 < 810 && flex2 < 800 && flex3 > 850 && flex4 < 800) return "Yes";
  else if (flex1 < 810 && flex2 < 770 && flex3 < 850 && flex4 < 770) return "Hello";
  else if (flex1 > 850 && flex2 < 820 && flex3 > 870 && flex4 < 800) return "Stop";
  else if (flex1 < 800 && flex2 < 770 && flex3 < 850 && flex4 < 770) return "Thank You";
  else if (flex1 > 820 && flex2 > 830 && flex3 > 860 && flex4 < 810) return "Good Morning";
  else if (flex1 < 790 && flex2 < 780 && flex3 < 810 && flex4 < 780) return "Good Night";
  else if (flex1 > 870 && flex2 > 850 && flex3 < 800 && flex4 > 860) return "I Love You";
  else if (flex1 < 750 && flex2 > 810 && flex3 < 830 && flex4 > 820) return "Sorry";
  else if (flex1 > 880 && flex2 < 790 && flex3 > 860 && flex4 > 870) return "Please";
  else if (flex1 > 830 && flex2 < 800 && flex3 > 840 && flex4 < 820) return "Help";
  else if (flex1 < 770 && flex2 > 850 && flex3 > 870 && flex4 > 840) return "Welcome";
  else if (flex1 > 860 && flex2 < 780 && flex3 > 850 && flex4 < 810) return "Water";
  else if (flex1 < 780 && flex2 > 800 && flex3 < 810 && flex4 < 780) return "Food";
  else if (flex1 > 850 && flex2 > 860 && flex3 < 780 && flex4 > 870) return "Goodbye";
  else if (flex1 < 750 && flex2 < 760 && flex3 > 830 && flex4 > 850) return "Congratulations";
  else {
    const char gestures[] = "abcdefghijklmnopqrstuvwxyz";
    int index = ((flex1 + flex2 + flex3 + flex4) / 160) % 26;
    return "Letter: " + String(gestures[index]);
  }
}

String mapMPUGesture(int ax, int ay, int az, int gx, int gy, int gz) {
  if (ax < -12000) return "Tilt Left";
  else if (ax > 12000) return "Tilt Right";
  else if (ay < -12000) return "Tilt Forward";
  else if (ay > 12000) return "Tilt Backward";
  else if (abs(gx) > 25000 || abs(gy) > 25000 || abs(gz) > 25000) return "Shake";
  else if (az < 1000) return "Free Fall or Drop";
  else return "";
}

bool hasSignificantMPUChange(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) {
  return (abs(ax - prev_ax) > MPU_THRESHOLD ||
          abs(ay - prev_ay) > MPU_THRESHOLD ||
          abs(az - prev_az) > MPU_THRESHOLD ||
          abs(gx - prev_gx) > MPU_THRESHOLD ||
          abs(gy - prev_gy) > MPU_THRESHOLD ||
          abs(gz - prev_gz) > MPU_THRESHOLD);
}

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("Setup complete.");
}

void loop() {
  int flex1 = analogRead(A0);
  int flex2 = analogRead(A1);
  int flex3 = analogRead(A2);
  int flex4 = analogRead(A3);

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  String flexGesture = mapFlexGesture(flex1, flex2, flex3, flex4);
  String mpuGesture = "";

  if (hasSignificantMPUChange(ax, ay, az, gx, gy, gz)) {
    mpuGesture = mapMPUGesture(ax, ay, az, gx, gy, gz);
    if (mpuGesture != "" && mpuGesture != lastMPUGesture) {
      bluetooth.println("MPU Gesture: " + mpuGesture);
      Serial.println("MPU Gesture: " + mpuGesture);
      lastMPUGesture = mpuGesture;
    }
  }

  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;
  prev_gx = gx;
  prev_gy = gy;
  prev_gz = gz;

  if (flexGesture != "") {
    bluetooth.println("Flex Gesture: " + flexGesture);
    Serial.println("Flex Gesture: " + flexGesture);
  }

  delay(2500); // Reduced for faster updates but still readable
}
