/*
 * global.c
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */
#include "global.h"

MODE mode = INIT;
uint8_t led_buffer[NO_OF_7SEG] = {0};
uint8_t red_light = 5;
uint8_t amber_light = 2;
uint8_t green_light = 3;
STATE line_1 = RED, line_2 = GREEN;
