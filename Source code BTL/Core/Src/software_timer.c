/*
 * software_timer.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */


#include "software_timer.h"

int timer_flag[10];
int timer_counter[10];

void setTimer(int index, int counter) {
	timer_flag[index] = 0;
	timer_counter[index] = counter/10;
}

void timer_run() {
	for (int i = 0; i < 10; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
		}
		if (timer_counter[i] <= 0) {
			timer_flag[i] = 1;
		}
	}
}
