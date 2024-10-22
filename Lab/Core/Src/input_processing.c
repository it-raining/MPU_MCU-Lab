/*
 * input_processing.c
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */
#include "swTimer.h"
#include "input_reading.h"
#include "input_processing.h"
#include "led_processing.h"

enum ButtonState {
	BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND
};
enum ButtonState button_state[NO_OF_BUTTONS];
void fsm_for_input_processing(void) {
	switch (button_state[MODIFY_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(MODIFY_BUTTON)) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
			mode = (mode + 1) % 5;
			switch (mode) {
			case MODIFY_RED:
				buffer = red_light;
				setTimer(EXPIRED, EXPIRED_PERIOD);
				break;
			case MODIFY_AMBER:
				buffer = amber_light;
				setTimer(EXPIRED, EXPIRED_PERIOD);
				break;
			case MODIFY_GREEN:
				buffer = green_light;
				setTimer(EXPIRED, EXPIRED_PERIOD);
				break;
			default:
			}
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
		} else {
			if (is_avail(HOLD) == 1) {
				LED_RED_1_GPIO_Port->ODR |= ALL_LED;
				mode = (mode + 1) % 5;
				switch (mode) {
				case MODIFY_RED:
					buffer = red_light;
					break;
				case MODIFY_AMBER:
					buffer = amber_light;
					break;
				case MODIFY_GREEN:
					buffer = green_light;
					break;
				default:
				}
				setTimer(HOLD, HALF_SEC);
			}
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
				button_state[INCREASE_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(INCREASE_BUTTON)) {
			button_state[INCREASE_BUTTON] = BUTTON_RELEASED;
		}
		if (is_avail(HOLD) == 1) {
			buffer = (buffer + 1) % 100;
			setTimer(HOLD, HALF_SEC);
		}
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

