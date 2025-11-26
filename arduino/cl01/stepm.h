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

uint8_t stepm_get_m0_pos(void);
uint8_t stepm_get_m0_dir(void);
uint8_t stepm_get_m1_pos(void);
uint8_t stepm_get_m1_dir(void);

void stepm_move(void);

#endif // _STEPM_H_
