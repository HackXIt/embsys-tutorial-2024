/*
 * kernelAwareness.c
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#include "kernelAwareness.h"

#define USE_CMSIS

const uint16_t delay = 1000;

#ifdef USE_CMSIS

osThreadId_t tid_threadCreateAndDestroy;
osThreadId_t tid_threadSuspended;
osThreadId_t tid_threadRunning;
const osThreadAttr_t attr_threadRunning = {
		.name = "threadRunning",
		.stack_size = STACK_SIZE * 4
};
const osThreadAttr_t attr_threadSuspended = {
		.name = "threadSuspended",
		.stack_size = STACK_SIZE * 4
};
const osThreadAttr_t attr_dynamicThread = {
		.name = "dynamicThread",
		.stack_size = STACK_SIZE * 4
};

void initKernelAwarenessDemonstration(void *argument) {
	// Create tasks
	tid_threadRunning = osThreadNew(threadRunning, NULL, &attr_threadRunning); // Running Task
	tid_threadSuspended = osThreadNew(threadSuspended, NULL, &attr_threadSuspended); // Suspended Task
	osThreadSuspend(tid_threadSuspended); // Suspend the task immediately

	// Create and Destroy Task
	tid_threadCreateAndDestroy = osThreadNew(threadCreateAndDestroy, NULL, NULL);

	osThreadExit();
}

void threadCreateAndDestroy(void *argument) {
    while(1) {
        // Create a dynamic task
        osThreadId_t tid_dynamicThread;
        tid_dynamicThread = osThreadNew(threadRunning, NULL, &attr_dynamicThread);

        // Let the dynamic task run for some time
        osDelay(delay);

        // Terminate the dynamic task
        osThreadTerminate(tid_dynamicThread);

        // Delay for observation
        osDelay(delay);
    }
}

void threadSuspended(void *argument) {
    while(1) {
        // This thread remains suspended
    }
}

void threadRunning(void *argument) {
    while(1) {
        // Running task routine
        osDelay(delay);
    }
}

#else

TaskHandle_t xTaskHandleCreateAndDestroy = NULL;
TaskHandle_t xTaskHandleSuspended = NULL;
TaskHandle_t xTaskHandleRunning = NULL;

void initKernelAwarenessDemonstration(void *argument) {
	// Create tasks
	xTaskCreate(vTaskRunning, "RunningTask", STACK_SIZE, NULL, 2, &xTaskHandleRunning);
	xTaskCreate(vTaskSuspended, "SuspendedTask", STACK_SIZE, NULL, 2, &xTaskHandleSuspended);

	// Initially suspend the SuspendedTask
	vTaskSuspend(xTaskHandleSuspended);

	// Create the CreateAndDestroyTask
	xTaskCreate(vTaskCreateAndDestroy, "CreateDestroyTask", STACK_SIZE, NULL, 1, &xTaskHandleCreateAndDestroy);

	vTaskDelete(NULL);
}

void vTaskCreateAndDestroy(void *pvParameters)
{
    while (1)
    {
        // Dynamically create a task, then delete it after some operations
        TaskHandle_t xTaskHandleDynamic;
        xTaskCreate(vTaskRunning, "DynamicTask", STACK_SIZE, NULL, 2, &xTaskHandleDynamic);

        // Perform some operations here
        vTaskDelay(delay / portTICK_PERIOD_MS);

        // Delete the dynamically created task
        vTaskDelete(xTaskHandleDynamic);

        // Delay to allow observation in debugger
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }
}

void vTaskSuspended(void *pvParameters)
{
    while (1)
    {
        // Task code here. This task remains suspended for observation purposes.
    }
}

void vTaskRunning(void *pvParameters)
{
    while (1)
    {
        // Running task code here
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }
}

#endif
