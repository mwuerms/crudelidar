/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + serial parser
 */

#ifndef _SPARSE_H_
#define _SPARSE_H_

#include <stdint.h>

void sparse_print_help(void);

#define SPARSE_ANSWER_NONE (0)
#define SPARSE_ANSWER_HELP (1)
#define SPARSE_ANSWER_SCAN (10)
#define SPARSE_ANSWER_ABORT (11)
uint8_t sparse(void);

#endif  // _SPARSE_H_
