#include "buzzer.h"
#include "pico/stdlib.h"
#include "hardware/clocks.h"

void setup_pwm(uint gpio, uint freq) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);

    pwm_set_clkdiv(slice, 4.0f);
    pwm_set_wrap(slice, clock_get_hz(clk_sys) / (4 * freq));
    pwm_set_chan_level(slice, channel, 1000);
    pwm_set_enabled(slice, true);
}

void play_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    setup_pwm(pin, BUZZER_FREQ);
}

void stop_buzzer(uint pin) {
    pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
    gpio_set_function(pin, GPIO_FUNC_SIO);
    gpio_set_dir(pin, GPIO_IN);
}

//Liga os dois buzzers ao mesmo tempo
void play_buzzers() {
    play_buzzer(BUZZER_A);
    play_buzzer(BUZZER_B);
}

//Desliga os dois buzzers ao mesmo tempo
void stop_buzzers() {
    stop_buzzer(BUZZER_A);
    stop_buzzer(BUZZER_B);
}

void init_buzzer() {
    gpio_init(BUZZER_A);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_set_dir(BUZZER_B, GPIO_OUT);
}
