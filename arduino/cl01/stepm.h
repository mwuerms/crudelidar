/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + drive stepper motors
 */

#ifndef _STEPM_H_
#define _STEPM_H_

#include <stdint.h>

void stepm_init(void);

int8_t stepm_get_m0_pos(void);
int8_t stepm_get_m0_dir(void);
int8_t stepm_get_m1_pos(void);
int8_t stepm_get_m1_dir(void);

uint8_t stepm_move(void);
void stepm_goto(int8_t m0_steps, int8_t m1_steps);
void stepm_set_scan_line(int8_t m0_steps, int8_t m1_steps);
void stepm_stop(void);

#endif  // _STEPM_H_
