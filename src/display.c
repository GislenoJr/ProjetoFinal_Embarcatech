#include "display.h"
#include <string.h>

static uint8_t ssd[ssd1306_buffer_length];
static struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

void init_display() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    clear_display();
}

void display_message(const char *line1, const char *line2, const char *line3) {
    memset(ssd, 0, ssd1306_buffer_length);
    ssd1306_draw_string(ssd, 10, 10, line1);
    ssd1306_draw_string(ssd, 10, 25, line2);
    ssd1306_draw_string(ssd, 10, 40, line3);
    render_on_display(ssd, &frame_area);
}

void clear_display() {
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}
