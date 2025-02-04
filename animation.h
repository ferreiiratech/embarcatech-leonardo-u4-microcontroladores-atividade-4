#ifndef ANIMATION_H
#define ANIMATION_H

#include "pico/stdlib.h"
#include "ws2818b.pio.h"

#define TOTAL_LEDS 25

struct pixel_t {
    uint8_t G, R, B;
};

typedef struct pixel_t npLED_t;

extern npLED_t leds[TOTAL_LEDS];
extern PIO np_pio;

#endif