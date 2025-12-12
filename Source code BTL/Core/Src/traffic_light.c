/*
 * traffic_light.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */


#include "traffic_light.h"

typedef enum {
	LIGHT_OFF_STATE = 0,
	LIGHT_GREEN_STATE = 0x01,
	LIGHT_YELLOW_STATE = 0x02,
	LIGHT_RED_STATE = 0x03
} LightState;

static void set_group_color(GPIO_TypeDef *portA, uint16_t pinA,
		GPIO_TypeDef *portB, uint16_t pinB, LightState state) {
	GPIO_PinState a = (state & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET; // A is MSB
	GPIO_PinState b = (state & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET; // B is LSB
	HAL_GPIO_WritePin(portA, pinA, a);
	HAL_GPIO_WritePin(portB, pinB, b);
}

static void set_axis1(LightState state) {
	set_group_color(LED1_A_GPIO_Port, LED1_A_Pin, LED1_B_GPIO_Port, LED1_B_Pin, state);
}

static void set_axis2(LightState state) {
	set_group_color(LED2_A_GPIO_Port, LED2_A_Pin, LED2_B_GPIO_Port, LED2_B_Pin, state);
}

void INIT_LIGHT() {
	set_axis1(LIGHT_OFF_STATE);
	set_axis2(LIGHT_OFF_STATE);
}

void LIGHT_RED_GREEN() {
	set_axis1(LIGHT_RED_STATE);
	set_axis2(LIGHT_GREEN_STATE);
}

void LIGHT_RED_YELOW() {
	set_axis1(LIGHT_RED_STATE);
	set_axis2(LIGHT_YELLOW_STATE);
}

void LIGHT_GREEN_RED() {
	set_axis1(LIGHT_GREEN_STATE);
	set_axis2(LIGHT_RED_STATE);
}

void LIGHT_YELOW_RED() {
	set_axis1(LIGHT_YELLOW_STATE);
	set_axis2(LIGHT_RED_STATE);
}

void Toggle_red(){
	static int red_on = 0;
	red_on = !red_on;
	LightState state = red_on ? LIGHT_RED_STATE : LIGHT_OFF_STATE;
	set_axis1(state);
	set_axis2(state);
}

void Toggle_yelow(){
	static int y_on = 0;
	y_on = !y_on;
	LightState state = y_on ? LIGHT_YELLOW_STATE : LIGHT_OFF_STATE;
	set_axis1(state);
	set_axis2(state);
}

void Toggle_green(){
	static int g_on = 0;
	g_on = !g_on;
	LightState state = g_on ? LIGHT_GREEN_STATE : LIGHT_OFF_STATE;
	set_axis1(state);
	set_axis2(state);
}
