#ifndef DISPLAY_H
#define DISPLAY_H

#include "hardware/i2c.h"
#include "ssd1306.h"

#define I2C_SDA 14
#define I2C_SCL 15

void init_display();
void display_message(const char *line1, const char *line2, const char *line3);
void clear_display();

#endif
