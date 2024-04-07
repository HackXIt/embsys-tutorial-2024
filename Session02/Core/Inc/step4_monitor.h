/*
 * step3_monitor.h
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#ifndef INC_STEP3_MONITOR_H_
#define INC_STEP3_MONITOR_H_

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "uart_helper.h"
#include "step2_messaging.h"
#include "usart.h"
#include "stdint.h"
#include "string.h"
#include "printf.h"
#include "stdio.h"

#define MONITOR_STACK_SIZE 512
#define MONITOR_RX_UART_BUFFER_SIZE 16
#define MONITOR_QUEUE_POLLING_TIMEOUT 1000

typedef struct monitor_argument
{
    osThreadId_t *producer_ids;
    uint32_t producer_count;
    osMessageQueueId_t monitor_queue;
    osMessageQueueId_t update_queue;
} monitor_argument_t;

void MonitoringTask(void *pvParameters);

void initializeMonitoringTaskAttributes(osThreadAttr_t *monitorTask_attr,
                                        const char *monitorTask_name,
                                        osPriority_t monitorTask_priority,
                                        uint32_t *monitorTask_stack_buffer,
                                        StaticTask_t *monitorTask_control_block);

#endif /* INC_STEP3_MONITOR_H_ */
