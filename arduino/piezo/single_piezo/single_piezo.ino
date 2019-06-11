/*
single_servo.ino

Author     : Wolf Chen
Date       : 2019/05/30
Description: This code can detect the analog output from piezo vibration sensor.

What you need to prepare:
1. Arduino board
2. Piezo Vibration Sensor
3. 1M ohm Resistance

Tested material:
1. Arduino UNO
2. Piezo Vibration Sensor
*/

#include <math.h>

int baud_rate = 9600;
const int PIEZO_PIN = A0;
float initVoltage = 0.0;
float initSum = 0.0;
float initAve = 0.0;
int count = 0;

void setup(){
  Serial.begin(baud_rate);
  Serial.print("Initializing...\n");

  // Get the initial value from the sensor
  delay(500);
  for (int i = 1; i < 100; i++){
    initVoltage = analogRead(PIEZO_PIN);
    initSum += initVoltage;
    count++;
  }
  initAve = initSum / count;
  Serial.print("Done\nThe offset value is: ");
  Serial.println(initAve);
  Serial.print("\nYou can start detecting...\n");
}

void loop(){
  // Read the analog value from pin A0  
  int piezoADC = analogRead(PIEZO_PIN);
  // Turn the value into voltage
  float piezoV = (piezoADC - initAve);
  // float piezoV = piezoV / 1023.0 * 5.0;
  // Minimum value calibration
  if (piezoV < 0){
    piezoV = 0;
  }

  Serial.println(piezoV);
  delay(250);
}
