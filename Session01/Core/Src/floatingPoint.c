/*
 * floatingPoint.c
 *
 *  Created on: Mar 31, 2024
 *      Author: RINI
 */

#include "floatingPoint.h"

void initFpuDemonstration(void) {
#ifdef USE_CMSIS
    osThreadNew(FpuTask, NULL, NULL);
    osThreadExit();
#else
    xTaskCreate(FpuTask, "FP Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskDelete(NULL);
#endif
}

void FpuTask(void *argument) {
    while (1) {
        performCalculations();
#ifdef USE_CMSIS
        osDelay(1000);
#else
        vTaskDelay(pdMS_TO_TICKS(1000));
#endif
    }
}

void performCalculations(void) {
    // Example floating-point operations
    float a = 5.5f, b = 2.3f;
    float result1 = a * b;
    float result2 = a / b;
    float result3 = a + b;
    float result4 = a - b;

    printf("Results of calculations:\r\n");
    printf("Multiplication: %.2f\r\n", result1);
    printf("Division: %.2f\r\n", result2);
    printf("Addition: %.2f\r\n", result3);
    printf("Subtraction: %.2f\r\n", result4);

    // Display information about FPU usage
#ifdef __FPU_USED
    printf("FPU is enabled.\n");
#else
    printf("FPU is not enabled.\n");
#endif
}
