/*
 * input_processing.c
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */
#include "input_reading.h"
#include "input_processing.h"

enum ButtonState {
	BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND
};
enum ButtonState button_1 = BUTTON_RELEASED;
enum ButtonState button_2 = BUTTON_RELEASED;
enum ButtonState button_3 = BUTTON_RELEASED;
void fsm_for_input_processing(void) {
	switch (button_1) {
	case BUTTON_RELEASED:
		if (is_button_pressed(0)) {
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
			button_1 = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(0)) {
			button_1 = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(0)) {
				button_1 = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(0)) {
			button_1 = BUTTON_RELEASED;
		} else {
			if (is_avail(HOLD) == 1) {
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
	switch (button_2) {
	case BUTTON_RELEASED:
		if (is_button_pressed(1)) {
			buffer = (buffer + 1) % 100;
			button_2 = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(1)) {
			button_2 = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(1)) {
				button_2 = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(1)) {
			button_2 = BUTTON_RELEASED;
		}
		if (is_avail(HOLD) == 1) {
			buffer = (buffer + 1) % 100;
			setTimer(HOLD, HALF_SEC);
		}
		break;
	}
	switch (button_3) {
	case BUTTON_RELEASED:
		if (is_button_pressed(2)) {
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
			button_3 = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(2)) {
			button_3 = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(2)) {
				button_3 = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(2)) {
			button_3 = BUTTON_RELEASED;
		}
		break;
	}
}

