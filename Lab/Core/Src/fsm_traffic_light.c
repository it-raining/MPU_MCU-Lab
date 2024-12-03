/*
 * led_processing.c
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#include <fsm_traffic_light.h>
uint8_t led_buffer[NO_OF_7SEG] = { 0 };
uint8_t buffer = 0;
uint8_t red_light = 5;
uint8_t amber_light = 2;
uint8_t green_light = 3;
static uint8_t scanning_idx = 0;
uint16_t EN_Pin[NO_OF_7SEG] = { EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin };
enum ButtonState button_state[NO_OF_BUTTONS];

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

void update_buffer(uint8_t num_1, uint8_t num_2) {
	led_buffer[0] = num_1 / 10;
	led_buffer[1] = num_1 % 10;
	led_buffer[2] = num_2 / 10;
	led_buffer[3] = num_2 % 10;
}
void scanning_led(void) {
	EN0_GPIO_Port->ODR |= (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin);
	display7SEG(led_buffer[scanning_idx]);
	EN0_GPIO_Port->ODR &= ~(EN_Pin[scanning_idx]);
	scanning_idx = (scanning_idx + 1) % NO_OF_7SEG;
}

// AUTOMATIC RUN DEFINE //
uint8_t count_1, count_2;
void fsm_for_auto(void) {
	update_buffer(count_1, count_2);
	LED_RED_1_GPIO_Port->ODR |= ALL_LED;
	switch (line_1) {
	case RED:
		LED_RED_1_GPIO_Port->ODR &= ~(LED_RED_1_Pin | LED_RED_3_Pin);
		if (count_1 <= 0) {
			line_1 = GREEN;
			count_1 = green_light;
		}
		break;
	case GREEN:
		LED_GREEN_1_GPIO_Port->ODR &= ~(LED_GREEN_1_Pin | LED_GREEN_3_Pin);
		if (count_1 <= 0) {
			line_1 = AMBER;
			count_1 = amber_light;
		}
		break;
	case AMBER:
		LED_AMBER_1_GPIO_Port->ODR &= ~(LED_AMBER_1_Pin | LED_AMBER_3_Pin);
		if (count_1 <= 0) {
			line_1 = RED;
			count_1 = red_light;
		}
		break;
	}
//	LED_RED_2_GPIO_Port->ODR |= ALL_LED;
	switch (line_2) {
	case RED:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_RED_2_Pin | LED_RED_4_Pin);
		if (count_2 <= 0) {
			line_2 = GREEN;
			count_2 = green_light;
		}
		break;
	case GREEN:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_GREEN_2_Pin | LED_GREEN_4_Pin);
		if (count_2 <= 0) {
			line_2 = AMBER;
			count_2 = amber_light;
		}
		break;
	case AMBER:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_AMBER_2_Pin | LED_AMBER_4_Pin);
		if (count_2 <= 0) {
			line_2 = RED;
			count_2 = red_light;
		}
		break;
	}
	if (count_1 > 0)
		count_1 = count_1 - 1;
	if (count_2 > 0)
		count_2 = count_2 - 1;
}
void modify_red(void) {
	update_buffer(MODIFY_RED, buffer);
	HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
	HAL_GPIO_TogglePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
	HAL_GPIO_TogglePin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);

//	if (is_button_pressed(1) || is_button_pressed(2))
//		setTimer(EXPIRED, EXPIRED_PERIOD);
}
void modify_amber(void) {
	update_buffer(MODIFY_AMBER, buffer);
	HAL_GPIO_TogglePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin);
	HAL_GPIO_TogglePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin);
	HAL_GPIO_TogglePin(LED_AMBER_3_GPIO_Port, LED_AMBER_3_Pin);
	HAL_GPIO_TogglePin(LED_AMBER_4_GPIO_Port, LED_AMBER_4_Pin);

//	if (is_button_pressed(1) || is_button_pressed(2))
//		setTimer(EXPIRED, EXPIRED_PERIOD);
}
void modify_green(void) {
	update_buffer(MODIFY_GREEN, buffer);
	HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
	HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
	HAL_GPIO_TogglePin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin);
	HAL_GPIO_TogglePin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin);

//	if (is_button_pressed(1) || is_button_pressed(2))
//		setTimer(EXPIRED, EXPIRED_PERIOD);
}
void increase_mode() {
	LED_RED_1_GPIO_Port->ODR |= ALL_LED;
	mode = (mode + 1) % 5;
	switch (mode) {
	case MODIFY_RED:
		buffer = red_light;
		state_ID = Scheduler_Add_Task(modify_red, ONE_SEC, ONE_SEC);
//		setTimer(EXPIRED, EXPIRED_PERIOD);
		break;
	case MODIFY_AMBER:
		buffer = amber_light;
		state_ID = Scheduler_Add_Task(modify_amber, ONE_SEC, ONE_SEC);
//		setTimer(EXPIRED, EXPIRED_PERIOD);
		break;
	case MODIFY_GREEN:
		buffer = green_light;
		state_ID = Scheduler_Add_Task(modify_green, ONE_SEC, ONE_SEC);
//		setTimer(EXPIRED, EXPIRED_PERIOD);
		break;
	default:
	}
}
void fsm_for_traffic_light(void) {
	if (mode == INIT) {
		LED_RED_1_GPIO_Port->ODR |= ALL_LED;
		red_light = green_light + amber_light; // adjust timing
		count_1 = red_light;
		count_2 = green_light;
		line_1 = RED, line_2 = GREEN;
		state_ID = Scheduler_Add_Task(fsm_for_auto, ONE_SEC,
		ONE_SEC);
		mode = AUTO;
	}
	switch (button_state[MODIFY_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(MODIFY_BUTTON)) {
			Scheduler_Remove_Task(state_ID);
			increase_mode();
			button_state[MODIFY_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(MODIFY_BUTTON)) {
			button_state[MODIFY_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(MODIFY_BUTTON)) {
				button_state[MODIFY_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(MODIFY_BUTTON)) {
			button_state[MODIFY_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}
	switch (button_state[INCREASE_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(INCREASE_BUTTON)) {
			buffer = (buffer + 1) % 100;
			button_state[INCREASE_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(INCREASE_BUTTON)) {
			button_state[INCREASE_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(INCREASE_BUTTON)) {
				button_state[INCREASE_BUTTON] =
						BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(INCREASE_BUTTON)) {
			button_state[INCREASE_BUTTON] = BUTTON_RELEASED;
		}
//		if (is_avail(HOLD) == 1) {
//			buffer = (buffer + 1) % 100;
//			setTimer(HOLD, HALF_SEC);
//		}
		break;
	}
	switch (button_state[SET_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(SET_BUTTON)) {
			switch (mode) {
			case MODIFY_RED:
				red_light = buffer;
				break;
			case MODIFY_AMBER:
				amber_light = buffer;
				break;
			case MODIFY_GREEN:
				green_light = buffer;
				break;
			default:
			}
			button_state[SET_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(SET_BUTTON)) {
			button_state[SET_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(SET_BUTTON)) {
				button_state[SET_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(SET_BUTTON)) {
			button_state[SET_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}
}
