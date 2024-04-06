/*
 * kernelAwareness.h
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#ifndef INC_KERNELAWARENESS_H_
#define INC_KERNELAWARENESS_H_

//#define USE_CMSIS

#include <stdint.h>
#define STACK_SIZE 256 // Size of stack in words (not bytes)

void initKernelAwarenessDemonstration(void *argument);

#ifdef USE_CMSIS
#include "cmsis_os2.h"
void threadCreateAndDestroy(void *argument);
void threadSuspended(void *argument);
void threadRunning(void *argument);
#else
#include "FreeRTOS.h"
#include "task.h"
void vTaskCreateAndDestroy(void *pvParameters);
void vTaskSuspended(void *pvParameters);
void vTaskRunning(void *pvParameters);
#endif

#endif /* INC_KERNELAWARENESS_H_ */
