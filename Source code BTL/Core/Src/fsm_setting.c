/*
 * fsm_setting.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */


#include "fsm_setting.h"
#include "i2c_lcd.h"
#include <stdio.h>
#include <string.h>

int count = 0, leds = 1;
int red_term, green_term, yelow_term;

static char last_mode_setting[17] = "";
static int last_time_setting = -1;

static void lcd_update_setting(const char *mode_text, int seconds) {
	int sec = seconds < 0 ? 0 : seconds;
	if (strncmp(last_mode_setting, mode_text, sizeof(last_mode_setting)) != 0) {
		strncpy(last_mode_setting, mode_text, sizeof(last_mode_setting) - 1);
		last_mode_setting[sizeof(last_mode_setting) - 1] = '\0';
		lcd_put_cursor(0, 0);
		lcd_send_string("                ");
		lcd_put_cursor(0, 0);
		lcd_send_string(last_mode_setting);
	}
	if (sec != last_time_setting) {
		last_time_setting = sec;
		char line[17];
		snprintf(line, sizeof(line), "TIME:%02ds       ", sec);
		line[16] = '\0';
		lcd_put_cursor(1, 0);
		lcd_send_string(line);
	}
}

void fsm_setting() {
	switch(status) {
		case SETTING:
			INIT_LIGHT();
			setTimer(0,SCAN_TIME);
			status = RED_SETTING;
			count = red/1000;
			last_mode_setting[0] = '\0';
			last_time_setting = -1;
			lcd_update_setting("SET RED", count);
			break;
		case RED_SETTING:
			//TODO
			lcd_update_setting("SET RED", count);
			if (isTimeUpPressed() == 1) {
				count++;
				if (count > 99) count = 0;
				lcd_update_setting("SET RED", count);
			}
			if (isTimeDownPressed() == 1) {
				if (count > 0) count--;
				lcd_update_setting("SET RED", count);
			}
			if (isModePressed() == 1) {
				setTimer(1,current_time);
				status = current_status;
			}
			if (timer_flag[0] == 1) {
				setTimer(0,SCAN_TIME);
				Toggle_red();
				leds = leds == 1 ? 2 : 1;
			}
			if (isApplyPressed()) {
				INIT_LIGHT();
				setTimer(0,SCAN_TIME);
				red_term = count;
				count = yelow/1000;
				lcd_update_setting("SET YEL", count);
				status = YELOW_SETTING;
			}
			break;
		case YELOW_SETTING:
			//TODO
			lcd_update_setting("SET YEL", count);
			if (isTimeUpPressed() == 1) {
				count++;
				if (count > 99) count = 0;
				lcd_update_setting("SET YEL", count);
			}
			if (isTimeDownPressed() == 1) {
				if (count > 0) count--;
				lcd_update_setting("SET YEL", count);
			}
			if (isModePressed() == 1) {
				setTimer(1,current_time);
				status = current_status;
			}
			if (timer_flag[0] == 1) {
				setTimer(0,SCAN_TIME);
				Toggle_yelow();
				leds = leds == 1 ? 2 : 1;
			}
			if (isApplyPressed()) {
				INIT_LIGHT();
				setTimer(0,SCAN_TIME);
				yelow_term = count;
				count = green/1000;
				lcd_update_setting("SET GRN", count);
				status = GREEN_SETTING;
			}
			break;
		case GREEN_SETTING:
			//TODO
			lcd_update_setting("SET GRN", count);
			if (isTimeUpPressed() == 1) {
				count++;
				if (count > 99) count = 0;
				lcd_update_setting("SET GRN", count);
			}
			if (isTimeDownPressed() == 1) {
				if (count > 0) count--;
				lcd_update_setting("SET GRN", count);
			}
			if (isModePressed() == 1) {
				setTimer(1,current_time);
				status = current_status;
			}
			if (timer_flag[0] == 1) {
				setTimer(0,SCAN_TIME);
				Toggle_green();
				leds = leds == 1 ? 2 : 1;
			}
			if (isApplyPressed()) {
				setTimer(0,SCAN_TIME);
				green_term = count;
				count = 0;
				if (green_term > 0 && yelow_term > 0 && red_term == green_term + yelow_term) {
					red = red_term*1000;
					green = green_term*1000;
					yelow = yelow_term*1000;
				}
				status = INIT;
			}
			break;
		default:
			break;
	}
}
