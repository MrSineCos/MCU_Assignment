/*
 * fsm_manual.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */


#include "fsm_manual.h"
#include "i2c_lcd.h"
#include <string.h>

static char last_manual_mode[17] = "";

static void lcd_show_manual_mode(const char *mode_text) {
	if (strncmp(last_manual_mode, mode_text, sizeof(last_manual_mode)) != 0) {
		strncpy(last_manual_mode, mode_text, sizeof(last_manual_mode) - 1);
		last_manual_mode[sizeof(last_manual_mode) - 1] = '\0';
		lcd_put_cursor(0, 0);
		lcd_send_string("                ");
		lcd_put_cursor(0, 0);
		lcd_send_string(last_manual_mode);
		lcd_put_cursor(1, 0);
		lcd_send_string("V:--   H:--   ");
	}
}

void fsm_manual() {
	switch(status) {
		case MAN_RED_GREEN:
			//TODO

			lcd_show_manual_mode("MANUAL R-G");

			LIGHT_RED_GREEN();

			if (isModePressed() == 1) {
				status = MAN_RED_YELOW;
			}
			if (isApplyPressed() == 1) {
				status = current_status;
				setTimer(1,current_time*1000);
			}
			break;
		case MAN_RED_YELOW:
			//TODO

			lcd_show_manual_mode("MANUAL R-Y");

			LIGHT_RED_YELOW();

			if (isModePressed() == 1) {
				status = MAN_GREEN_RED;
			}
			if (isApplyPressed() == 1) {
				status = current_status;
				setTimer(1,current_time*1000);
			}
			break;
		case MAN_GREEN_RED:
			//TODO

			lcd_show_manual_mode("MANUAL G-R");

			LIGHT_GREEN_RED();

			if (isModePressed() == 1) {
				status = MAN_YELOW_RED;
			}
			if (isApplyPressed() == 1) {
				status = current_status;
				setTimer(1,current_time*1000);
			}
			break;
		case MAN_YELOW_RED:
			//TODO

			lcd_show_manual_mode("MANUAL Y-R");

			LIGHT_YELOW_RED();

			if (isModePressed() == 1) {
				status = MAN_RED_GREEN;
			}
			if (isApplyPressed() == 1) {
				status = current_status;
				setTimer(1,current_time*1000);
			}
			break;
		default:
			break;
		}
}
