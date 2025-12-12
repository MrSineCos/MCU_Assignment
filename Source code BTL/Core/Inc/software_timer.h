/*
 * software_timer.h
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_flag[10];

void setTimer(int index, int counter);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
