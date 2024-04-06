/*
 * stackUsage.h
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#ifndef INC_MEMORYUSAGE_H_
#define INC_MEMORYUSAGE_H_

#include "FreeRTOS.h"
#include "printf.h"
#include <stdlib.h>

#define USE_CMSIS

#ifdef USE_CMSIS
#include "cmsis_os2.h"
#else
#include "FreeRTOS.h"
#include "task.h"
#endif

#define STACK_SIZE 512 // Size of stack in words

void MemoryTask(void *argument);
void initMemoryUsageDemonstration(void *argument);

#endif /* INC_MEMORYUSAGE_H_ */
