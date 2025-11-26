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
#include "sparse.h"

void setup() {
  // give info about this project
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("");
  Serial.println(PROJECT_NAME);
  Serial.println(__FILE__);
  Serial.println(__DATE__);
  Serial.println("");
  sparse_print_help();
  Serial.println("");

  dsens_init();
  stepm_init();
}

uint8_t ans;
void loop() {
  ans = sparse();
  switch (ans) {
    case SPARSE_ANSWER_HELP:
      sparse_print_help();
      break;
    case SPARSE_ANSWER_SCAN:
      //Serial.println("STARTING SCAN");
      //stepm_goto(-50, -50);
      stepm_goto(-10, -10);
      break;
    case SPARSE_ANSWER_ABORT:
      //Serial.println("ABORT ABORT");
      stepm_stop();
      break;
  }
  if (stepm_move()) {
    Serial.print("M0: ");
    Serial.print(stepm_get_m0_pos());
    Serial.print(", ");
    Serial.print(stepm_get_m0_dir());
    Serial.print(", M1: ");
    Serial.print(stepm_get_m1_pos());
    Serial.print(", ");
    Serial.print(stepm_get_m1_dir());
    Serial.println("");
  }
}
