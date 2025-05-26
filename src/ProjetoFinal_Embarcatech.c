#include <stdio.h>
#include "pico/stdlib.h"
#include "buzzer.h"
#include "display.h"
#include "led_matrix.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define JOYSTICK_BUTTON 22  
#define SENSOR_PIN_1 16
#define SENSOR_PIN_2 18

// Variáveis globais para controle do alarme
bool alert_active = false;   // Indica se o alarme está tocando
bool alarm_enabled = false;  // Indica se o sistema de alarme está ativado

int main() {
    stdio_init_all();
    init_display();
    init_led_matrix();
    init_buzzer();

    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_init(JOYSTICK_BUTTON);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_set_dir(JOYSTICK_BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);
    gpio_pull_up(JOYSTICK_BUTTON);  

    gpio_init(SENSOR_PIN_1);
    gpio_set_dir(SENSOR_PIN_1, GPIO_IN);
    gpio_pull_up(SENSOR_PIN_1);

    gpio_init(SENSOR_PIN_2);
    gpio_set_dir(SENSOR_PIN_2, GPIO_IN);
    gpio_pull_up(SENSOR_PIN_2);

   //Assim que o codigo sobe, essa mensagem aparece no Display
    display_message("ALERTA", "Alarme", "DESLIGADO");

    while (true) {
        // Alterna entre ligar/desligar o alarme ao pressionar o botão do joystick
        if (gpio_get(JOYSTICK_BUTTON) == 0) {
            sleep_ms(300);                   // Debounce para evitar múltiplas leituras rápidas
            alarm_enabled = !alarm_enabled;  // Alterna o estado do alarme
            if (alarm_enabled) {
                display_message("ALERTA", "Alarme", "LIGADO");
            } else {
                display_message("ALERTA", "Alarme", "DESLIGADO");
            }
            while (gpio_get(JOYSTICK_BUTTON) == 0);  // Aguarda soltar o botão
        }

        // Se o alarme NÃO estiver ativado, ignora os sensores e o Botão A
        if (!alarm_enabled) {
            continue;
        }

        // Ativa o alarme ao apertar o botão A ou se um sensor detectar algo
        if (gpio_get(BUTTON_A) == 0 || gpio_get(SENSOR_PIN_1) == 1 || gpio_get(SENSOR_PIN_2) == 1) {
            alert_active = true; // Ativa o alarme
            
            if (gpio_get(BUTTON_A) == 0) {
                display_message("AVISO", "Alarme ativado", "manualmente");
            } else if (gpio_get(SENSOR_PIN_1) == 1) {
                display_message("AVISO", "Invasor", "na porta");
            } else if (gpio_get(SENSOR_PIN_2) == 1) {
                display_message("AVISO", "Invasor", "na janela");
            }
        }

        // Enquanto o alarme estiver ativo, os LEDs do triângulo acendem e os buzzers fazem som ao mesmo tempo
        while (alert_active) {
            draw_triangle_pattern(); 
            play_buzzers(); // Ativa os dois buzzers ao mesmo tempo

            sleep_ms(500);  // Tempo do efeito de alerta

            npClear();      // Apaga LEDs
            stop_buzzers();  

            sleep_ms(500);  // Tempo do efeito de alerta

            // Se o botão B for pressionado, desativa o alarme
            if (gpio_get(BUTTON_B) == 0) {
                alert_active = false;
                clear_display();  // Limpa a tela
                npClear();        // Apaga os LEDs
                stop_buzzers();   // Desativa os dois buzzers ao mesmo tempo
                display_message("ALERTA", "Alarme", "LIGADO"); // Exibe que o alarme ainda está ligado
                break;                                         // Sai do loop while(alert_active)
            }
        }
    }
}
