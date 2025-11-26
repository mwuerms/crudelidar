/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + drive stepper motors
 */
#include <Arduino.h>
#include <avr/io.h>
#include "stepm.h"

// - define the motors --------
#define NB_MOTORS (2)
#define NB_STEPS_PER_REVOLUTION (200)

// motor 0: left - right movment
#define M0_INDEX (0)
//#define M0_DIR_LEFT (0)
//#define M0_DIR_RIGHT (1)

// m0_step: D2, PD2
#define M0_STEP_PIN (1 << 2)
#define M0_STEP_OUT() DDRD |= M0_STEP_PIN
#define M0_STEP_SET() PORTD |= M0_STEP_PIN
#define M0_STEP_CLR() PORTD &= ~M0_STEP_PIN

// m0_dir: D5, PD5
#define M0_DIR_PIN (1 << 5)
#define M0_DIR_OUT() DDRD |= M0_DIR_PIN
#define M0_DIR_SET() PORTD |= M0_DIR_PIN
#define M0_DIR_CLR() PORTD &= ~M0_DIR_PIN

// motor 1: up - down movment
#define M1_INDEX (1)
//#define M1_DIR_UP (0)
//#define M1_DIR_DOWN (1)

// m1_step: D3, PD3
#define M1_STEP_PIN (1 << 3)
#define M1_STEP_OUT() DDRD |= M1_STEP_PIN
#define M1_STEP_SET() PORTD |= M1_STEP_PIN
#define M1_STEP_CLR() PORTD &= ~M1_STEP_PIN

// m1_dir: D6, PD6
#define M1_DIR_PIN (1 << 6)
#define M1_DIR_OUT() DDRD |= M1_DIR_PIN
#define M1_DIR_SET() PORTD |= M1_DIR_PIN
#define M1_DIR_CLR() PORTD &= ~M1_DIR_PIN

static struct {
  int8_t pos;
  int8_t target_pos;
  uint8_t dir;
} stepm_motors[NB_MOTORS];
static struct {
  uint8_t task;
} stepm_ctrl;
#define STEPM_TASK_NONE (0)
#define STEPM_TASK_GOTO (1)
#define STEPM_TASK_SCAN (2)

// - public functions --------------
void stepm_init(void) {
  stepm_motors[M0_INDEX].pos = 0;
  stepm_motors[M0_INDEX].dir = 0;  //M0_DIR_LEFT;
  M0_STEP_OUT();
  M0_STEP_CLR();
  M0_DIR_OUT();
  M0_DIR_CLR();

  stepm_motors[M1_INDEX].pos = 0;
  stepm_motors[M1_INDEX].dir = 0;  //M1_DIR_UP;
  M1_STEP_OUT();
  M1_STEP_CLR();
  M1_DIR_OUT();
  M1_DIR_CLR();

  stepm_ctrl.task = STEPM_TASK_NONE;
}

int8_t stepm_get_m0_pos(void) {
  return stepm_motors[M0_INDEX].pos;
}
int8_t stepm_get_m0_dir(void) {
  return stepm_motors[M0_INDEX].dir;
}
int8_t stepm_get_m1_pos(void) {
  return stepm_motors[M1_INDEX].pos;
}
int8_t stepm_get_m1_dir(void) {
  return stepm_motors[M1_INDEX].dir;
}

static inline void stepm_step_pin_set(uint8_t mi) {
  if (mi == M0_INDEX) {
    M0_STEP_SET();
  } else {
    M1_STEP_SET();
  }
}

static inline void stepm_step_pin_clr(uint8_t mi) {
  if (mi == M0_INDEX) {
    M0_STEP_CLR();
  } else {
    M1_STEP_CLR();
  }
}

static inline void stepm_dir_pin_set(uint8_t mi) {
  if (mi == M0_INDEX) {
    M0_DIR_SET();
  } else {
    M1_DIR_SET();
  }
}

static inline void stepm_dir_pin_clr(uint8_t mi) {
  if (mi == M0_INDEX) {
    M0_DIR_CLR();
  } else {
    M1_DIR_CLR();
  }
}


/**
 * @return =0: nothing left to do
 */
static uint8_t stepm_move_motor_to_target(uint8_t mi) {
  if (stepm_motors[mi].pos == stepm_motors[mi].target_pos) {
    // nothing to do
    Serial.print("_move(");
    Serial.print(mi);
    Serial.print(", if(");
    Serial.print(stepm_motors[mi].pos);
    Serial.print(" == ");
    Serial.print(stepm_motors[mi].target_pos);
    Serial.println(") -> done, return 0");
    return 0;
  }

  stepm_step_pin_set(mi);
  // use calculations as delay for now
  if (stepm_motors[mi].dir == 0) {
    stepm_dir_pin_clr(mi);
    if (stepm_motors[mi].pos < (stepm_motors[mi].target_pos)) {
      stepm_motors[mi].pos++;
    }
  } else {
    stepm_dir_pin_set(mi);
    if (stepm_motors[mi].pos > (stepm_motors[mi].target_pos)) {
      stepm_motors[mi].pos--;
    }
  }
  stepm_step_pin_clr(mi);
  return 1;
}

static int8_t t0, t1;
/**
 * @return =1: still active, =0: inactive
 */
uint8_t stepm_move(void) {
  uint8_t ans;
  switch (stepm_ctrl.task) {
    case STEPM_TASK_GOTO:

      delay(20);

      ans = stepm_move_motor_to_target(M0_INDEX);
      ans |= stepm_move_motor_to_target(M1_INDEX);
      if (ans == 0) {
        // done here
        t0 = stepm_motors[M0_INDEX].target_pos * (-1);
        t1 = stepm_motors[M1_INDEX].target_pos;
        stepm_set_scan_line(t0, t1);
        return 1;
      }
      return 1;
    case STEPM_TASK_SCAN:

      delay(20);

      ans = stepm_move_motor_to_target(M0_INDEX);
      ans |= stepm_move_motor_to_target(M1_INDEX);
      if (ans == 0) {
        // done here, next line
        /*if(t1 < 10) {
          t0 = stepm_motors[M0_INDEX].target_pos * (-1);
          t1 = stepm_motors[M1_INDEX].target_pos + 1;
          stepm_set_scan_line(t0, t1);
          return 1;
        }*/
        return 0;
      }
      return 0;
    case STEPM_TASK_NONE:
    default:
      return 0;
  }
  return 0;
}

static inline void stepm_set_target(uint8_t mi, int8_t target_pos) {
  Serial.print("_set_target(");
  Serial.print(mi);
  Serial.print(",");
  Serial.print(target_pos);
  Serial.println(");");

  stepm_motors[mi].target_pos = target_pos;
  stepm_motors[mi].dir = 0;
  if ((stepm_motors[mi].pos) > (stepm_motors[mi].target_pos)) {
    stepm_motors[mi].dir = 1;
  }

  Serial.print(" pos: ");
  Serial.print(stepm_motors[mi].pos);
  Serial.print(" dir: ");
  Serial.println(stepm_motors[mi].dir);
}

void stepm_goto(int8_t m0_steps, int8_t m1_steps) {
  stepm_set_target(M0_INDEX, m0_steps);
  stepm_set_target(M1_INDEX, m1_steps);
  stepm_ctrl.task = STEPM_TASK_GOTO;
}

void stepm_set_scan_line(int8_t m0_steps, int8_t m1_steps) {
  Serial.print("_scan_line(");
  Serial.print(m0_steps);
  Serial.print(",");
  Serial.print(m1_steps);
  Serial.println(");");
  stepm_set_target(M0_INDEX, m0_steps);
  stepm_set_target(M1_INDEX, m1_steps);
  stepm_ctrl.task = STEPM_TASK_SCAN;
}

void stepm_stop(void) {
  return;
}
