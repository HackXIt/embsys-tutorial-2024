/*
 * stackUsage.c
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#include "memoryUsage.h"

// Declare buffers and control blocks for static tasks
#if defined(USE_CMSIS)
uint32_t staticTaskBuffer[STACK_SIZE*4];
StaticTask_t staticTaskControlBlock;
const osThreadAttr_t staticTask_attributes = {
	.name = "StaticMemoryTask",
	.stack_mem = staticTaskBuffer,
	.stack_size = sizeof(staticTaskBuffer),
	.cb_mem = &staticTaskControlBlock,
	.cb_size = sizeof(staticTaskControlBlock),
};
#else
StaticTask_t staticTaskBuffer;
StackType_t staticTaskStack[STACK_SIZE];
#endif

void initMemoryUsageDemonstration(void *argument) {
#ifdef USE_CMSIS
	printf("Dynamic:\r\n");
	osThreadNew(MemoryTask, NULL, NULL); // Dynamic allocation
	osDelay(1000);
	printf("Static:\r\n");
	osThreadNew(MemoryTask, NULL, &staticTask_attributes); // Static allocation
    osThreadExit();
#else
    printf("Dynamic:\r\n");
    xTaskCreate(MemoryTask, "DynamicMemoryTask", STACK_SIZE, NULL, 1, NULL); // Dynamic allocation
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("Static:\r\n");
	xTaskCreateStatic(MemoryTask, "StaticMemoryTask", STACK_SIZE, NULL, 1, staticTaskStack, &staticTaskBuffer); // Static allocation
    vTaskDelete(NULL);
#endif
}

void MemoryTask(void *argument) {
    // Stack allocation: local variables
    uint32_t stackVariable = 0xDEADBEEF;
    printf("Address of stackVariable: %p\r\n", (void *)&stackVariable);

    // Heap allocation: dynamic memory
    uint32_t *heapVariable = (uint32_t *)pvPortMalloc(sizeof(uint32_t));
    if (heapVariable != NULL) {
        *heapVariable = 0xFEEDBEEF;
        printf("Address of heapVariable: %p\r\n", (void *)heapVariable);

        // Use the heap variable for something
        printf("Value of heapVariable: 0x%X\r\n", *heapVariable);

        // Remember to free the heap memory
        vPortFree(heapVariable);
    } else {
        printf("Heap allocation failed!\r\n");
    }

    // Suspend the task so the addresses can be read in the terminal
#ifdef USE_CMSIS
//    osThreadSuspend(osThreadGetId());
    osThreadExit();
#else
//    vTaskSuspend(NULL);
    vTaskDelete(NULL);
#endif
}
