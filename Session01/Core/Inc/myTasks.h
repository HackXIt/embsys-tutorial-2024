/*
 * myTasks.h
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#ifndef INC_MYTASKS_H_
#define INC_MYTASKS_H_

// The following definition allow me to demonstrate different topics
// It basically tells the compiler to only use specific sections of code for the final program
//#define KERNEL_AWARENESS_DEMONSTRATION
//#define ADDITIONAL_FEATURES_DEMONSTRATION
//#define FLOATING_POINT_DEMONSTRATION
#define MEMORY_USAGE_DEMONSTRATION

// NOTE Any required peripherals/headers shall be imported here, so that myTasks.c only needs to import this header to work!
#include "cmsis_os2.h"

// Unnecessary prototypes due to freertos.c - but still good practice
void StartDefaultTask(void *argument);
void MyStaticTask(void *argument);
void MyDynamicTask(void *argument);

#ifdef KERNEL_AWARENESS_DEMONSTRATION
#include "kernelAwareness.h"
#endif /* KERNEL_AWARENESS_DEMONSTRATION */

#ifdef ADDITIONAL_FEATURES_DEMONSTRATION
#include "additionalFeatures.h"
#endif /* ADDITIONAL_FEATURES_DEMONSTRATION */

#ifdef FLOATING_POINT_DEMONSTRATION
#include "floatingPoint.h"
#endif /* FLOATING_POINT_DEMONSTRATION */

#ifdef MEMORY_USAGE_DEMONSTRATION
#include "memoryUsage.h"
#endif /* MEMORY_USAGE_DEMONSTRATION */

#endif /* INC_MYTASKS_H_ */
