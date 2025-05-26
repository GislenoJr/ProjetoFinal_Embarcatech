#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "hardware/pio.h"

#define LED_COUNT 25
#define LED_PIN 7

void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npClear();
void npWrite();
void init_led_matrix();
void draw_triangle_pattern(); 

#endif
