/*
 * floatingPoint.h
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#ifndef INC_FLOATINGPOINT_H_
#define INC_FLOATINGPOINT_H_

#include "printf.h"

#ifdef USE_CMSIS
#include "cmsis_os2.h"
#else
#include "FreeRTOS.h"
#include "task.h"
#endif

void initFpuDemonstration(void);
void performCalculations(void);
// Task function prototype
void FpuTask(void *argument);

#endif /* INC_FLOATINGPOINT_H_ */
