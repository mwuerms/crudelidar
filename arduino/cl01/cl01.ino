/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + drive stepper motors and 
 * + get distance measuremnts
 */

#define PROJECT_NAME "crude lidar 01"
#define SERIAL_BAUD_RATE (115200)

#include "dsens.h"
#include "stepm.h"

void setup() {
  // give info about this project
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("");
  Serial.println(PROJECT_NAME);
  Serial.println(__FILE__);
  Serial.println(__DATE__);
  Serial.println("");

  dsens_init();
  stepm_init();
}

void loop() {
  stepm_move();
  Serial.print("M0: ");
  Serial.print(stepm_get_m0_pos());
  Serial.print(", ");
  Serial.print(stepm_get_m0_dir());
  Serial.print(", M1: ");
  Serial.print(stepm_get_m1_pos());
  Serial.print(", ");
  Serial.print(stepm_get_m1_dir());
  Serial.println("");
  delay(50);
}
