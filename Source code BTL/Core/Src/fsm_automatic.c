/*
 * fsm_automatic.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */

#include "fsm_automatic.h"
#include "i2c_lcd.h"
#include <stdio.h>
#include <string.h>

int time;
int time2;

static char last_mode_line[17] = "";
static int last_v = -1;
static int last_h = -1;

static void lcd_update_mode(const char *text) {
	if (strncmp(last_mode_line, text, sizeof(last_mode_line)) != 0) {
		strncpy(last_mode_line, text, sizeof(last_mode_line) - 1);
		last_mode_line[sizeof(last_mode_line) - 1] = '\0';
		lcd_put_cursor(0, 0);
		lcd_send_string("                ");
		lcd_put_cursor(0, 0);
		lcd_send_string(last_mode_line);
	}
}

static void lcd_update_timers(int vertical_seconds, int horizontal_seconds) {
	int v = vertical_seconds < 0 ? 0 : vertical_seconds;
	int h = horizontal_seconds < 0 ? 0 : horizontal_seconds;
	if (v == last_v && h == last_h) return;
	last_v = v;
	last_h = h;
	char line[17];
	snprintf(line, sizeof(line), "V:%02d   H:%02d   ", v, h);
	line[16] = '\0';
	lcd_put_cursor(1, 0);
	lcd_send_string(line);
}

void fsm_automatic_run() {
	switch(status) {
	case INIT:
		//TODO
		time = red/1000;
		time2 = green/1000;
		INIT_LIGHT();
		lcd_clear();
		memset(last_mode_line, 0, sizeof(last_mode_line));
		last_v = -1;
		last_h = -1;
		lcd_update_mode("AUTO INIT");
		lcd_update_timers(time, time2);
		status = RED_GREEN;
		setTimer(1,green);
		setTimer(2,1000);
		break;
	case RED_GREEN:
		//TODO
		lcd_update_mode("AUTO R-G");
		lcd_update_timers(time, time2);
		LIGHT_RED_GREEN();
		if (timer_flag[2] == 1) {
			time--;
			time2--;
			setTimer(2,1000);
		}
		if (timer_flag[1] == 1) {
			status = RED_YELOW;
			setTimer(1,yelow);
			time2 = yelow/1000;
		}
		if (isModePressed() == 1) {
			status = MAN_RED_GREEN;
			current_status = RED_GREEN;
			current_time = time < time2 ? time : time2;
		}
		if (isApplyPressed() == 1) {
			current_status = RED_GREEN;
			current_time = time < time2 ? time : time2;
			status = SETTING;
		}
		break;
	case RED_YELOW:
		//TODO
		lcd_update_mode("AUTO R-Y");
		lcd_update_timers(time, time2);
		LIGHT_RED_YELOW();
		if (timer_flag[2] == 1) {
			time--;
			time2--;
			setTimer(2,1000);
		}
		if (timer_flag[1] == 1) {
			status = GREEN_RED;
			setTimer(1,green);
			time = green/1000;
			time2 = red/1000;
		}
		if (isModePressed() == 1) {
			status = MAN_RED_YELOW;
			current_status = RED_YELOW;
			current_time = time < time2 ? time : time2;
		}
		if (isApplyPressed() == 1) {
			current_status = RED_GREEN;
			current_time = time < time2 ? time : time2;
			status = SETTING;
		}
		break;
	case GREEN_RED:
		//TODO
		lcd_update_mode("AUTO G-R");
		lcd_update_timers(time, time2);
		LIGHT_GREEN_RED();
		if (timer_flag[2] == 1) {
			time--;
			time2--;
			setTimer(2,1000);
		}
		if (timer_flag[1] == 1) {
			status = YELOW_RED;
			setTimer(1,yelow);
			time = yelow/1000;
		}
		if (isModePressed() == 1) {
			status = MAN_GREEN_RED;
			current_status = GREEN_RED;
			current_time = time < time2 ? time : time2;
		}
		if (isApplyPressed() == 1) {
			current_status = RED_GREEN;
			current_time = time < time2 ? time : time2;
			status = SETTING;
		}
		break;
	case YELOW_RED:
		//TODO
		lcd_update_mode("AUTO Y-R");
		lcd_update_timers(time, time2);
		LIGHT_YELOW_RED();
		if (timer_flag[2] == 1) {
			time--;
			time2--;
			setTimer(2,1000);
		}
		if (timer_flag[1] == 1) {
			status = RED_GREEN;
			setTimer(1,green);
			time2 = green/1000;
			time = red/1000;
		}
		if (isModePressed() == 1) {
			status = MAN_YELOW_RED;
			current_status = YELOW_RED;
			current_time = time < time2 ? time : time2;
		}
		if (isApplyPressed() == 1) {
			current_status = RED_GREEN;
			current_time = time < time2 ? time : time2;
			status = SETTING;
		}
		break;
	default:
		break;
	}
}


