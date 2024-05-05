/*
 * step1_taskmanagement.h
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#ifndef INC_STEP1_TASKMANAGEMENT_H_
#define INC_STEP1_TASKMANAGEMENT_H_

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "printf.h"

#include "step3_producer.h"
#include "step4_monitor.h"

#define NUM_PRODUCERS 3

void CreateTasks();

#endif /* INC_STEP1_TASKMANAGEMENT_H_ */
