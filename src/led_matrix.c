#include "led_matrix.h"
#include "pico/stdlib.h"
#include "ws2818b.pio.h"

typedef struct {
    uint8_t G, R, B;
} pixel_t;
typedef pixel_t npLED_t;

static npLED_t leds[LED_COUNT];
static PIO np_pio;
static uint sm;

// Define o padrão de LEDs para o triângulo
static int triangle_pattern[25] = {
    0,   0,   255, 0,   0,
    0,   255, 255, 255, 0,
    255, 255, 255, 255, 255,
    0,   255, 255, 255, 0,
    0,   0,   255, 0,   0 
};

void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0) {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
    npClear();
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        npSetLED(i, 0, 0, 0);
    }
    npWrite();
}

void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100);
}

// Ativa apenas os LEDs do triângulo
void draw_triangle_pattern() {
    for (uint i = 0; i < LED_COUNT; i++) {
        if (triangle_pattern[i]) {   // Apenas os LEDs do triângulo acendem
            npSetLED(i, 255, 0, 0);  // Vermelho máximo
        }
    }
    npWrite();
}

void init_led_matrix() {
    npInit(LED_PIN);
    npClear();
}
