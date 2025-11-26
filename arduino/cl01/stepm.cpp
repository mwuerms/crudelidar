/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + drive stepper motors
 */

#include <avr/io.h>
#include "stepm.h"

// - define the motors --------
#define NB_MOTORS (2)
#define NB_STEPS_PER_REVOLUTION (200)

// motor 0: left - right movment
#define M0_INDEX (0)
#define M0_DIR_LEFT (0)
#define M0_DIR_RIGHT (1)

// m0_step: D2, PD2
#define M0_STEP_PIN (1 << 2)
#define M0_STEP_OUT() DDRD  |=  M0_STEP_PIN
#define M0_STEP_SET() PORTD |=  M0_STEP_PIN
#define M0_STEP_CLR() PORTD &= ~M0_STEP_PIN

// m0_dir: D5, PD5
#define M0_DIR_PIN (1 << 5)
#define M0_DIR_OUT() DDRD  |=  M0_DIR_PIN
#define M0_DIR_SET() PORTD |=  M0_DIR_PIN
#define M0_DIR_CLR() PORTD &= ~M0_DIR_PIN

// motor 1: up - down movment
#define M1_INDEX (1)
#define M1_DIR_UP (0)
#define M1_DIR_DOWN (1)

// m1_step: D3, PD3
#define M1_STEP_PIN (1 << 3)
#define M1_STEP_OUT() DDRD  |=  M1_STEP_PIN
#define M1_STEP_SET() PORTD |=  M1_STEP_PIN
#define M1_STEP_CLR() PORTD &= ~M1_STEP_PIN

// m1_dir: D6, PD6
#define M1_DIR_PIN (1 << 6)
#define M1_DIR_OUT() DDRD  |=  M1_DIR_PIN
#define M1_DIR_SET() PORTD |=  M1_DIR_PIN
#define M1_DIR_CLR() PORTD &= ~M1_DIR_PIN


static struct {
    uint8_t pos;
    uint8_t dir;
} stepm_ctrl[NB_MOTORS];

// - public functions --------------
void stepm_init(void) {
    stepm_ctrl[M0_INDEX].pos = 0;
    stepm_ctrl[M0_INDEX].dir = M0_DIR_LEFT;
    M0_STEP_OUT();
    M0_STEP_CLR();
    M0_DIR_OUT();
    M0_DIR_CLR();

    stepm_ctrl[M1_INDEX].pos = 0;
    stepm_ctrl[M1_INDEX].dir = M1_DIR_UP;
    M1_STEP_OUT();
    M1_STEP_CLR();
    M1_DIR_OUT();
    M1_DIR_CLR();
}

uint8_t stepm_get_m0_pos(void) {return stepm_ctrl[M0_INDEX].pos;}
uint8_t stepm_get_m0_dir(void) {return stepm_ctrl[M0_INDEX].dir;}
uint8_t stepm_get_m1_pos(void) {return stepm_ctrl[M1_INDEX].pos;}
uint8_t stepm_get_m1_dir(void) {return stepm_ctrl[M1_INDEX].dir;}

// for simplicity reasons put all the movements here
// this is a fixed routine
void stepm_move(void) {
    M0_STEP_SET();
    M1_STEP_SET();

    // use calculations as delay for now
    if(stepm_ctrl[M0_INDEX].dir == M0_DIR_LEFT) {
        M0_DIR_CLR();
        if(stepm_ctrl[M0_INDEX].pos < (100-1)) {
            stepm_ctrl[M0_INDEX].pos++;
        }
        else {
            stepm_ctrl[M0_INDEX].dir = M0_DIR_RIGHT;
        }
    }
    else {
        M0_DIR_SET();
        if(stepm_ctrl[M0_INDEX].pos > (0+1)) {
            stepm_ctrl[M0_INDEX].pos--;
        }
        else {
            stepm_ctrl[M0_INDEX].dir = M0_DIR_LEFT;
        }
    }

    if(stepm_ctrl[M1_INDEX].dir == M0_DIR_LEFT) {
        M1_DIR_CLR();
        if(stepm_ctrl[M1_INDEX].pos < (100-1)) {
            stepm_ctrl[M1_INDEX].pos++;
        }
        else {
            stepm_ctrl[M1_INDEX].dir = M0_DIR_RIGHT;
        }
    }
    else {
        M1_DIR_SET();
        if(stepm_ctrl[M1_INDEX].pos > (0+1)) {
            stepm_ctrl[M1_INDEX].pos--;
        }
        else {
            stepm_ctrl[M1_INDEX].dir = M0_DIR_LEFT;
        }
    }

    M0_STEP_CLR();
    M1_STEP_CLR();
}
