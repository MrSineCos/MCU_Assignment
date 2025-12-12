/*
 * button.h
 *
 *  Created on: Nov 10, 2024
 *      Author: MSIFPT
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int button1_flag;

int isModePressed();
int isTimeUpPressed();
int isTimeDownPressed();
int isApplyPressed();
void getKeyInput();

#endif /* SRC_BUTTON_H_ */
