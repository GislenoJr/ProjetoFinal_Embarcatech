#ifndef BUZZER_H
#define BUZZER_H

#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define BUZZER_A 21
#define BUZZER_B 10
#define BUZZER_FREQ 4000

void setup_pwm(uint gpio, uint freq);
void play_buzzer(uint pin);
void stop_buzzer(uint pin);
void init_buzzer();
void play_buzzers();  
void stop_buzzers();  

#endif
