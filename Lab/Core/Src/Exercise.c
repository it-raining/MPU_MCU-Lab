/*
 * Exercise.c
 *
 *  Created on: Sep 6, 2024
 *      Author: HP
 */
#include "Exercise.h"

int idx = 0, counter = 3;
int LED_1 = 5;
int LED_2 = 3;
uint8_t hour = 0, minute = 0, second = 0;
STATE state = RED_GREEN; // init state

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
void clearAllClock() {
	GPIOB->ODR &= ~0b111111111111; // 12 bits
}
void setNumberOnClock(int num) {
	int scaler = (num + 11) % 12;
	GPIOB->ODR |= (1 << scaler);
}
void clearNumberOnClock(int num) {
	GPIOB->ODR &= ~(1 << num);
}
void setClock() {
	clearAllClock();
	setNumberOnClock(hour % 12);
	setNumberOnClock(minute * 12 / 60);
	setNumberOnClock(second * 12 / 60);
}

void Ex1_Init() {
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 1);
}

void Ex1_Run() {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}

void Ex2_Init() {
	counter = 3;
	HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, 0);
	HAL_GPIO_WritePin(LED_12_GPIO_Port, LED_12_Pin, 0);
	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
}

void Ex2_Run() {
	switch (idx) {
	case 0:
		HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
		HAL_GPIO_TogglePin(LED_11_GPIO_Port, LED_11_Pin);
		counter--;
		if (!counter) {
			idx = 1;
			counter = 2;
		}
		break;
	case 1:
		HAL_GPIO_TogglePin(LED_11_GPIO_Port, LED_11_Pin);
		HAL_GPIO_TogglePin(LED_12_GPIO_Port, LED_12_Pin);
		counter--;
		if (!counter) {
			idx = 2;
			counter = 5;
		}
	case 2:
		HAL_GPIO_TogglePin(LED_12_GPIO_Port, LED_12_Pin);
		HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
		counter--;
		if (!counter) {
			idx = 0;
			counter = 3;
		}
	}
}

void Ex3_Init() {
}
void Ex3_Run() {
	RED_1_Port->ODR &= ~((1 << 12) - 1);
	switch (state) {
	case RED_GREEN:
		HAL_GPIO_WritePin(RED_1_Port, RED_1_Pin, 1);
		HAL_GPIO_WritePin(RED_3_Port, RED_3_Pin, 1);
		HAL_GPIO_WritePin(GREEN_2_Port, GREEN_2_Pin, 1);
		HAL_GPIO_WritePin(GREEN_4_Port, GREEN_4_Pin, 1);
		counter--;
		if (!counter) {
			counter = 2;
			state = RED_YELLOW;
		}
		break;
	case RED_YELLOW:
		HAL_GPIO_WritePin(RED_1_Port, RED_1_Pin, 1);
		HAL_GPIO_WritePin(RED_3_Port, RED_3_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_2_Port, YELLOW_2_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_4_Port, YELLOW_4_Pin, 1);
		counter--;
		if (!counter) {
			counter = 3;
			state = GREEN_RED;
		}
		break;
	case GREEN_RED:
		HAL_GPIO_WritePin(GREEN_1_Port, GREEN_1_Pin, 1);
		HAL_GPIO_WritePin(GREEN_3_Port, GREEN_3_Pin, 1);
		HAL_GPIO_WritePin(RED_2_Port, RED_2_Pin, 1);
		HAL_GPIO_WritePin(RED_4_Port, RED_4_Pin, 1);
		counter--;
		if (!counter) {
			counter = 2;
			state = YELLOW_RED;
		}
		break;
	case YELLOW_RED:
		HAL_GPIO_WritePin(YELLOW_1_Port, YELLOW_1_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_3_Port, YELLOW_3_Pin, 1);
		HAL_GPIO_WritePin(RED_2_Port, RED_2_Pin, 1);
		HAL_GPIO_WritePin(RED_4_Port, RED_4_Pin, 1);
		counter--;
		if (!counter) {
			counter = 3;
			state = RED_GREEN;
		}
		break;
	}
}

void Ex4_Init() {
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
	counter = 0;
}
void Ex4_Run() {
	if (counter >= 10)
		counter = 0;
	display7SEG(counter++);
}

void Ex5_Init() {
	idx = 0;
	state = RED_GREEN;
	counter = 3;
	LED_1 = 5;
	LED_2 = 3;
	display7SEG(LED_1);
}
void Ex5_Run() {
	switch (idx) {
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		display7SEG(LED_2);
		idx = 1;
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		display7SEG(LED_1);
		idx = 0;
		break;
	}
	RED_1_Port->ODR &= ~((1 << 12) - 1);
	switch (state) {
	case RED_GREEN:
		HAL_GPIO_WritePin(RED_1_Port, RED_1_Pin, 1);
		HAL_GPIO_WritePin(RED_3_Port, RED_3_Pin, 1);
		HAL_GPIO_WritePin(GREEN_2_Port, GREEN_2_Pin, 1);
		HAL_GPIO_WritePin(GREEN_4_Port, GREEN_4_Pin, 1);
		if (counter <= 0) {
			counter = 2;
			LED_2 = 2;
			state = RED_YELLOW;
		}
		break;
	case RED_YELLOW:
		HAL_GPIO_WritePin(RED_1_Port, RED_1_Pin, 1);
		HAL_GPIO_WritePin(RED_3_Port, RED_3_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_2_Port, YELLOW_2_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_4_Port, YELLOW_4_Pin, 1);
		if (counter <= 0) {
			counter = 3;
			LED_1 = 3;
			LED_2 = 5;
			state = GREEN_RED;
		}
		break;
	case GREEN_RED:
		HAL_GPIO_WritePin(GREEN_1_Port, GREEN_1_Pin, 1);
		HAL_GPIO_WritePin(GREEN_3_Port, GREEN_3_Pin, 1);
		HAL_GPIO_WritePin(RED_2_Port, RED_2_Pin, 1);
		HAL_GPIO_WritePin(RED_4_Port, RED_4_Pin, 1);
		if (counter <= 0) {
			counter = 2;
			LED_1 = 2;
			state = YELLOW_RED;
		}
		break;
	case YELLOW_RED:
		HAL_GPIO_WritePin(YELLOW_1_Port, YELLOW_1_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_3_Port, YELLOW_3_Pin, 1);
		HAL_GPIO_WritePin(RED_2_Port, RED_2_Pin, 1);
		HAL_GPIO_WritePin(RED_4_Port, RED_4_Pin, 1);
		if (counter <= 0) {
			counter = 3;
			LED_1 = 5;
			LED_2 = 3;
			state = RED_GREEN;
		}
		break;
	}
	counter--;
	LED_1--;
	LED_2--;
}

void Ex6_Init() {
}
void Ex6_Run() {
	clearAllClock();
	int scaler = (idx + 11) % 12;
	GPIOB->ODR |= (1 << scaler);
	idx = (idx < 11) ? idx + 1 : 0;
}

void Ex10_Init() {
	hour = 3;
	minute = 59;
	second = 30;
	setClock();
}
void Ex10_Run() {
	second++;
	if (second >= 60) {
		second = 0;
		minute++;
	}
	if (minute >= 60) {
		minute = 0;
		hour++;
	}
	if (hour >= 24) {
		hour = 0;
	}
	setClock();
}
