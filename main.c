#include "pico/stdlib.h"

#define red_pin 13
#define time_sleep 100

// Função que define o estado do led
void set_led_color(uint pin, bool status) {
    gpio_put(pin, status);
}

int main() {
    // Inicialização do pino do LED
    gpio_init(red_pin);
    gpio_set_dir(red_pin, GPIO_OUT);

    bool led_status = false; 

    // Loop principal
    while (true) {
        set_led_color(red_pin, led_status);
        led_status = !led_status; // Inverte o estado do LED
        sleep_ms(time_sleep);
    }

  return 0;
}
