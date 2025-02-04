#include <stdint.h>
#include "animation.h"
#include "led_control.h"
#include "pico/stdlib.h"
#include "sprites.h"

// Recebe um valor de 0 a 9 para exibi-lo na matriz de LEDs
void display_number(int value){
    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {

            int index = getIndex(linha, coluna);
            set_led_rgb(index, numbers[value][coluna][linha][0], numbers[value][coluna][linha][1], numbers[value][coluna][linha][2]);
        }
    }

    // Atualiza a matriz de LEDs com as alterações
    buffer();
}