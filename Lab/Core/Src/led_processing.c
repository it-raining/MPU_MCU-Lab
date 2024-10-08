/*
 * led_processing.c
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#include "led_processing.h"

void display7SEG(int num) {
	SEG_0_GPIO_Port->ODR &= ~ALL_SEG;
	switch (num) {
	case 0:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_0); // 0
		break;
	case 1:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_1); // 1
		break;
	case 2:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_2); // 2
		break;
	case 3:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_3); // 3
		break;
	case 4:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_4); // 4
		break;
	case 5:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_5); // 5
		break;
	case 6:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_6); // 6
		break;
	case 7:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_7); // 7
		break;
	case 8:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_8); // 8
		break;
	case 9:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_9); // 9
		break;
	default:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG); // Turn off all segments
	}
}

// SCANNING 4 7SEG-LED TO DISPLAY NUMBER //
static uint8_t scanning_idx = 0;
uint16_t EN_Pin[NO_OF_7SEG] = { EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin };

void update_buffer(uint8_t num_1, uint8_t num_2) {
	led_buffer[0] = num_1 / 10;
	led_buffer[1] = num_1 % 10;
	led_buffer[2] = num_2 / 10;
	led_buffer[3] = num_2 % 10;
}
void scanning_led(void) {
	if (is_avail(SCANNING) == 1) {
		EN0_GPIO_Port->ODR |= (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin);
		display7SEG(led_buffer[scanning_idx]);
		EN0_GPIO_Port->ODR &= ~(EN_Pin[scanning_idx]);
		scanning_idx = (scanning_idx + 1) % NO_OF_7SEG;
		setTimer(SCANNING, (1000 / NO_OF_7SEG) / SCANNING_FREQ);
	}
}

// AUTOMATIC RUN DEFINE //
int count_1, count_2;
void fsm_for_auto(void) {
	update_buffer(count_1, count_2);
	switch (line_1) {
	case RED:
		LED_RED_1_GPIO_Port->ODR &= ~(LED_RED_1_Pin | LED_RED_3_Pin);
		if (count_1 <= 0) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
			line_1 = GREEN;
			count_1 = green_light;
		}
		break;
	case GREEN:
		LED_GREEN_1_GPIO_Port->ODR &= ~(LED_GREEN_1_Pin | LED_GREEN_3_Pin);

		if (count_1 <= 0) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
			line_1 = AMBER;
			count_1 = amber_light;
		}
		break;
	case AMBER:
		LED_AMBER_1_GPIO_Port->ODR &= ~(LED_AMBER_1_Pin | LED_AMBER_3_Pin);
		if (count_1 <= 0) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
			line_1 = RED;
			count_1 = red_light;
		}
		break;
	}

	switch (line_2) {
	case RED:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_RED_2_Pin | LED_RED_4_Pin);
		if (count_2 <= 0) {
			LED_RED_2_GPIO_Port->ODR |= ALL_LED;
			line_2 = GREEN;
			count_2 = green_light;
		}
		break;
	case GREEN:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_GREEN_2_Pin | LED_GREEN_4_Pin);
		if (count_2 <= 0) {
			LED_RED_2_GPIO_Port->ODR |= ALL_LED;
			line_2 = AMBER;
			count_2 = amber_light;
		}
		break;
	case AMBER:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_AMBER_2_Pin | LED_AMBER_4_Pin);
		if (count_2 <= 0) {
			LED_RED_2_GPIO_Port->ODR |= ALL_LED;
			line_2 = RED;
			count_2 = red_light;
		}
		break;
	}
	if (is_avail(COUNTDOWN) == 1) {
		if (count_1 > 0)
			count_1 = count_1 - 1;
		if (count_2 > 0)
			count_2 = count_2 - 1;
		setTimer(COUNTDOWN, ONE_SEC);
	}
}

void fsm_for_traffic_light(void) {
	switch (mode) {
	case INIT:
		setTimer(COUNTDOWN, 97);
		setTimer(SCANNING, 253);
		if (1) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
			count_1 = red_light;
			count_2 = green_light;
			mode = AUTO;
		}
		break;
	case AUTO:
		fsm_for_auto();
		break;
	case MODIFY:
		break;
	default:
		mode = INIT;
	}
	scanning_led();
}
