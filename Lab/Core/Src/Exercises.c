/*
 * Exercises.c
 *
 *  Created on: Sep 7, 2024
 *      Author: HP
 */
#include "Exercises.h"

UserTimer Clk_Timer, LED_Timer, LM;
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = { 1, 2, 3, 4 };
int hour = 15, minute = 8, second = 50;

void setClkTimer(int duration) {
	Clk_Timer.counter = duration / TIMER_CYCLE;
	Clk_Timer.flag = 0;
}
void setLEDTimer(int duration) {
	LED_Timer.counter = duration / TIMER_CYCLE;
	LED_Timer.flag = 0;
}
void setMatrixTimer(int duration) {
	LM.counter = duration / TIMER_CYCLE;
	LM.flag = 0;
}
void timerRun() {
	if (Clk_Timer.counter > 0) {
		Clk_Timer.counter--;
		if (Clk_Timer.counter <= 0)
			Clk_Timer.flag = 1;
	}
	if (LED_Timer.counter > 0) {
		LED_Timer.counter--;
		if (LED_Timer.counter <= 0)
			LED_Timer.flag = 1;
	}
	if (LM.counter > 0) {
		LM.counter--;
		if (LM.counter <= 0)
			LM.flag = 1;
	}
}

void display7SEG(int num) {
	SEG0_GPIO_Port->ODR &= ~ALL_SEG;
	switch (num) {
	case 0:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_0); // 0
		break;
	case 1:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_1); // 1
		break;
	case 2:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_2); // 2
		break;
	case 3:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_3); // 3
		break;
	case 4:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_4); // 4
		break;
	case 5:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_5); // 5
		break;
	case 6:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_6); // 6
		break;
	case 7:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_7); // 7
		break;
	case 8:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_8); // 8
		break;
	case 9:
		SEG0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_9); // 9
		break;
	default:
		SEG0_GPIO_Port->ODR |= (ALL_SEG); // Turn off all segments
	}
}
void update7SEG(int index) {
	switch (index) {
	case 0:
		display7SEG(led_buffer[0]);
		break;
	case 1:
		display7SEG(led_buffer[1]);
		break;
	case 2:
		display7SEG(led_buffer[2]);
		break;
	case 3:
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}
void updateClockBuffer() {
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

void Ex1_Init() {
	Clk_Timer.counter = 50;
	LED_Timer.counter = 100;
	index_led = 0;
	display7SEG(1);
}

void Ex1_Run() {
	Clk_Timer.counter--;
	LED_Timer.counter--;
	if (LED_Timer.counter <= 0) {
		LED_Timer.counter = 100;
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
	switch (index_led) {
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 1;
			display7SEG(2);
		}
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 0;
			display7SEG(1);
		}
		break;
	}
}

void Ex2_Init() {
	Clk_Timer.counter = 50;
	LED_Timer.counter = 100;
	index_led = 0;
	display7SEG(1);
}
void Ex2_Run() {
	Clk_Timer.counter--;
	LED_Timer.counter--;
	if (LED_Timer.counter <= 0) {
		LED_Timer.counter = 100;
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	}
	switch (index_led) {
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 1;
			display7SEG(2);
		}
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 2;
			display7SEG(3);
		}
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 3;
			display7SEG(0);
		}
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		if (Clk_Timer.counter <= 0) {
			Clk_Timer.counter = 50;
			index_led = 0;
			display7SEG(1);
		}
		break;
	default:
		index_led = 0;
	}
}
void Ex3_Init() {
	Clk_Timer.counter = 50;
	LED_Timer.counter = 100;
	index_led = 0;
	display7SEG(1);
}
void Ex3_Run() {
	Clk_Timer.counter--;
	LED_Timer.counter--;
	if (LED_Timer.counter <= 0) {
		LED_Timer.counter = 100;
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	}
	switch (index_led) {
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		break;
	default:
		index_led = 0;
	}
	if (Clk_Timer.counter <= 0) {
		Clk_Timer.counter = 50;
		update7SEG(index_led++);
		if (index_led > 3)
			index_led = 0;
	}
}

void Ex4_Init() {
	Clk_Timer.counter = 1000 / 10 / 4; // 1Hz /period_callback /4 led
	LED_Timer.counter = 100;
	index_led = 0;
	display7SEG(1);
}
void Ex4_Run() {
	Ex3_Run();
}

void Ex5_Init() {
	hour = 15, minute = 8, second = 50;
	Ex4_Init();
}
void Ex5_Run() {
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
	updateClockBuffer();
	HAL_Delay(1000);
}
void Ex5_TI() {
	Ex4_Run();
}

void Ex7_Init() {
	hour = 15, minute = 8, second = 50;
	index_led = 0;
	setClkTimer(23);
	setLEDTimer(97);
}
void Ex7_Run() {
	if (LED_Timer.flag == 1) {
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		setLEDTimer(1000);
		second++;
	}
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
	updateClockBuffer();
}
void Ex7_TI() {
	timerRun();
	update7SEG(index_led);
	switch (index_led) {
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		break;
	}
	if (Clk_Timer.counter <= 0) {
		Clk_Timer.counter = 25;
		index_led = (index_led + 1) % 4;
	}
}

void Ex8_Init() {
	Ex7_Init();
}
void Ex8_Run() {
	if (LED_Timer.flag == 1) {
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		setLEDTimer(1000);
		second++;
	}
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
	updateClockBuffer();
	if (Clk_Timer.flag == 1) {
		update7SEG(index_led);
		switch (index_led) {
		case 0:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
			break;
		}
		index_led = (index_led + 1) % 4;
		setClkTimer(250);
	}
}
void Ex8_TI() {
	timerRun();
}
/////////////// LED MATRIX ///////////////
const int MAX_LED_MATRIX = 8;
uint32_t index_led_matrix = 0;
uint8_t shift = 0;
uint16_t row_pin[] = { ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin,
ROW5_Pin, ROW6_Pin, ROW7_Pin };
uint8_t matrix_buffer[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 }; // scan row to row
uint8_t char_A[8] = { 0x18, 0x3c, 0x66, 0x66, 0x7e, 0x7e, 0x66, 0x66 };

uint8_t clz(int x) {
	int position = 0;
	if (x >> 8) {
		position += 8;
		x >>= 8;
	}
	if (x >> 4) {
		position += 4;
		x >>= 4;
	}
	if (x >> 2) {
		position += 2;
		x >>= 2;
	}
	if (x >> 1) {
		position += 1;
	}
	return position;
}

void rowDisplay(int buffer) {
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 0) & 0x1) << clz(ENM0_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 1) & 0x1) << clz(ENM1_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 2) & 0x1) << clz(ENM2_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 3) & 0x1) << clz(ENM3_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 4) & 0x1) << clz(ENM4_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 5) & 0x1) << clz(ENM5_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 6) & 0x1) << clz(ENM6_Pin));
	ENM0_GPIO_Port->ODR &= ~(((buffer >> 7) & 0x1) << clz(ENM7_Pin));
}

void Ex9_Init() {
	index_led_matrix = 0;
	setMatrixTimer(371);
}
void Ex9_Run() {
	if (LM.flag == 1) {
		ROW0_GPIO_Port->ODR |= ALL_ROW;
		ENM0_GPIO_Port->ODR |= ALL_EN;
		HAL_GPIO_WritePin(ROW0_GPIO_Port, row_pin[index_led_matrix], 0);
		rowDisplay(char_A[index_led_matrix]);
		index_led_matrix = (index_led_matrix + 1) % 8;
		setMatrixTimer(100);
	}
}
void float_up(uint8_t *buffer) {
	uint8_t tmp = buffer[0];
	for (int i = 0; i < MAX_LED_MATRIX - 1; i++)
		buffer[i] = buffer[i + 1];
	buffer[MAX_LED_MATRIX - 1] = tmp;
}
void shift_right(uint8_t *buffer) {
	for (int i = 0; i < MAX_LED_MATRIX; i++)
		buffer[i] = (buffer[i] << 1)
				| (buffer[i] >> (MAX_LED_MATRIX - 1));
}
void Ex10_Init() {
	index_led_matrix = 0;
	setMatrixTimer(371);
	setLEDTimer(283); // Use for effect motion
}
void Ex10_Run() {
	if (LM.flag == 1) {
		ROW0_GPIO_Port->ODR |= ALL_ROW;
		ENM0_GPIO_Port->ODR |= ALL_EN;
		HAL_GPIO_WritePin(ROW0_GPIO_Port, row_pin[index_led_matrix], 0);
		rowDisplay(char_A[index_led_matrix]);
		index_led_matrix = (index_led_matrix + 1) % 8;
		setMatrixTimer(100);
	}
	if (LED_Timer.flag == 1) {
		float_up((uint8_t*) char_A);
		setLEDTimer(800);
	}
}

