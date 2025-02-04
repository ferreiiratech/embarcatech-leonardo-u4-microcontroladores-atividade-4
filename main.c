#include "src/animation.h"
#include "src/led_control.h"
#include <stdio.h>

#define PIN_LED_RED 13 // Pino do LED vermelho
#define TIME_SLEEP 100 // Tempo de espera em milissegundos para o led piscar 5 vezes por segundo, 1000/5 = 200ms e um ciclo leva 100ms*2 = 200ms
#define PIN_MATRIZ_LED 7 // Pino da matriz de LEDs
#define PIN_BUTTON_A 5 // Pino do botão A
#define PIN_BUTTON_B 6 // Pino do botão B

const uint64_t DEBOUNCE_TIME = 500000; // Tempo de debounce em microssegundos
volatile int8_t number_position = 0; // Posição do número atual exibido na matriz de LEDs
volatile uint64_t last_interrupt_time = 0; // Tempo da última interrupção do botão A
volatile bool led_status = false; // Estado do LED comum

void button_isr(uint gpio, uint32_t events) {
    uint64_t current_time = time_us_64(); // Obtém o tempo atual em microssegundos

    if (current_time - last_interrupt_time < DEBOUNCE_TIME) return; // Ignora bouncing caso o tempo entre interrupções seja menor que 500ms
    last_interrupt_time = current_time;

    // Incrementa um número na matriz de LEDs caso o botão A seja pressionado
    if (gpio == PIN_BUTTON_A) {
        number_position++;
        if (number_position >= 10) number_position = 0;
        
        display_number(number_position);
    } 
    
    // Decrementa um número na matriz de LEDs caso o botão B seja pressionado
    if (gpio == PIN_BUTTON_B) {
        number_position--;
        if (number_position < 0) number_position = 9;

        display_number(number_position);
    }
}

int main() {
    // Inicialização do pino do LED
    gpio_init(PIN_LED_RED);
    gpio_set_dir(PIN_LED_RED, GPIO_OUT);

    // Configuração do botão A
    gpio_init(PIN_BUTTON_A);
    gpio_set_dir(PIN_BUTTON_A, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_A);
    
    // Configuração do botão B
    gpio_init(PIN_BUTTON_B);
    gpio_set_dir(PIN_BUTTON_B, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_B);

    // Configuração da interrupção do botão A e do botão B
    gpio_set_irq_enabled_with_callback(PIN_BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_isr);
    gpio_set_irq_enabled(PIN_BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    init_led_matrix(PIN_MATRIZ_LED);

    // Loop principal do programa
    while (true) {
        // Inicia o programa exibindo o número 0 na matriz de LEDs
        display_number(number_position);

        // Atualiza o estado do LED
        set_led_color(PIN_LED_RED, led_status);
        led_status = !led_status;
        sleep_ms(TIME_SLEEP);
    }

  return 0;
}
