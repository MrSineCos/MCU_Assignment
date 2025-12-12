/*
 * global.h
 *
 *  Created on: Dec 12, 2025
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#define INIT 1
#define RED_GREEN 2
#define RED_YELOW 3
#define GREEN_RED 4
#define YELOW_RED 5

#define GREEN_TIME 7000
#define YELOW_TIME 3000
#define SCAN_TIME 250
// RED_TIME = GREEN_TIME + YELOW_TIME


#define MAN_RED_GREEN 10
#define MAN_RED_YELOW 11
#define MAN_GREEN_RED 12
#define MAN_YELOW_RED 13

#define SETTING 19
#define RED_SETTING 20
#define YELOW_SETTING 21
#define GREEN_SETTING 22


extern int status;
extern int red;
extern int yelow;
extern int green;
extern int current_status;
extern int current_time;

#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "fsm_manual.h"
#include "fsm_setting.h"


#endif /* INC_GLOBAL_H_ */
