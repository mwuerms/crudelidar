/**
 * Martin Egli
 * 2025-11-26
 * crude lidar
 * + serial parser
 * use Arduino Serial funcions
 */
#include <Arduino.h>
#include <string.h>
#include "sparse.h"

#define SPARSE_TERMINATION (0x0D)  // CR

#define SPARSE_INBUF_SIZE (32)
char inbuf[SPARSE_INBUF_SIZE];
uint8_t inbuf_len = 0;
uint8_t inbuf_flag = 0;

// - public functions --------------------------------
void sparse_print_help(void) {
  Serial.println("12 help, scan, abort");
  Serial.print("termination: CR, ");
  Serial.print(SPARSE_TERMINATION);
  Serial.print(", ");
  Serial.println(SPARSE_TERMINATION, HEX);
}

static inline void _clear(void) {
  inbuf[0] = 0;
  inbuf_len = 0;
  inbuf_flag = 0;
}

static inline void _put(uint8_t b) {
  if (inbuf_len < (SPARSE_INBUF_SIZE - 1)) {
    inbuf[inbuf_len] = b;
    inbuf_len++;
    inbuf[inbuf_len] = 0; // string end termination
    if (b == SPARSE_TERMINATION) {
      inbuf_flag |= 0x01;
    }
    if (inbuf_len >= (SPARSE_INBUF_SIZE - 1)) {
      // overflow
      inbuf_flag |= 0x02;
    }
  }
}

static inline void read_all_from_stream(void) {
  while (Serial.available()) {
    _put(Serial.read());
  }
}

static uint8_t _find_str(const char *fstr, uint8_t fstr_len) {
  uint8_t n;
  if (inbuf_len < fstr_len) {
    return 0;
  }
  for (n = 0; n < fstr_len; n++) {
    if (fstr[n] != inbuf[n]) {
      // differs here
      return 0;
    }
  }
  // correctly found
  return 1;
}

uint8_t sparse(void) {
  uint8_t ans = SPARSE_ANSWER_NONE;
  if (Serial.available()) {
    read_all_from_stream();
    if (inbuf_flag != 0) {
      // found termination or overflow, continue
      /*Serial.print("IN: ");
      Serial.print(inbuf);
      Serial.println(" END");*/

      if (_find_str("help", strlen("help"))) {
        ans = SPARSE_ANSWER_HELP;
      }
      if (_find_str("scan", strlen("scan"))) {
        ans = SPARSE_ANSWER_SCAN;
      }
      if (_find_str("abort", strlen("abort"))) {
        ans = SPARSE_ANSWER_ABORT;
      }
      //str_buf_clear(sparse_str_buf, SPARSE_STR_BUF_SIZE);
      _clear();
    }
  }
  return ans;
}
