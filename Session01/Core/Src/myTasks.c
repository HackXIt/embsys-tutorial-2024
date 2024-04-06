/*
 * myTasks.c
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#include "myTasks.h"

// BE AWARE - stack definitions will still be placed in freertos.c when using IOC-Configuration to define tasks
// That's why we need to use the "extern" keyword here, since those variables are defined & initialized elsewhere!
// (only if we need to access them however, if we don't we will not need to define the external variables here)
// "extern" only DECLARES a variable - IT DOES NOT initialize values.
// The prototypes MUST MATCH (i.e. copy-paste the keywords/types + variableName and put "extern" before it like below)
// Usually only the taskHandle is regularly required

extern osThreadId_t defaultTaskHandle;
extern osThreadId_t myStaticTaskHandle;
extern osThreadId_t myDynamicTaskHandle;

// If you define & configure your handles, control blocks and attributes solely in code, you would not need to use "extern".
// All of my demonstrations are created in-code in their respective source files.
// (it literally just means doing the work of the code-generator yourself)
// The code generator doesn't do anything magically - it simply creates the necessary variables FOR YOU as you've defined them
// Doing the work yourself allows for better fine-control & you'll gain more knowledge in the process (I guarantee!)
// Additionally - If you define them yourself, you will not have to rely on CubeMX to work on a project using FreeRTOS

const osThreadAttr_t initTask = {
		.name = "initDemo",
		.stack_size = 512
};

void StartDefaultTask(void *argument) {
#ifdef KERNEL_AWARENESS_DEMONSTRATION
	osThreadNew(initKernelAwarenessDemonstration, NULL, &initTask);
#endif /* KERNEL_AWARENESS_DEMONSTRATION */

#ifdef ADDITIONAL_FEATURES_DEMONSTRATION

#endif /* ADDITIONAL_FEATURES_USE_CASE */

#ifdef FLOATING_POINT_DEMONSTRATION
	osThreadNew(initFpuDemonstration, NULL, &initTask);
#endif /* FLOATING_POINT_DEMONSTRATION */

#ifdef MEMORY_USAGE_DEMONSTRATION
	osThreadNew(initMemoryUsageDemonstration, NULL, &initTask);
#endif /* MEMORY_USAGE_DEMONSTRATION */
	osThreadExit();
}
/*
void MyStaticTask(void *argument) {
	// This task is allocated statically
	osThreadExit();
}

void MyDynamicTask(void *argument) {
	// This task is allocated dynamically
	osThreadExit();
}
*/
