/*
 * step2_producer.h
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#ifndef INC_STEP2_PRODUCER_H_
#define INC_STEP2_PRODUCER_H_

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "step4_messaging.h"

#define PRODUCER_STACK_SIZE 128
#define INITIAL_DELAY 1000
#define MAX_PRODUCER_VALUE 0xFFFFFFFF

typedef struct producer_argument
{
    osThreadId_t thread_id;
    uint8_t initial_value;
    osMessageQueueId_t update_queue;
    osMessageQueueId_t monitor_queue;
} producer_argument_t;

void ProducerTask(void *argument);

void initializeProducerTaskAttributes(osThreadAttr_t *prodTask_attr,
                                      const char *prodTask_name,
                                      osPriority_t prodTask_priority,
                                      uint32_t *prodTask_stack_buffer,
                                      uint32_t prodTask_stack_size,
                                      StaticTask_t *prodTask_control_block);

#endif /* INC_STEP2_PRODUCER_H_ */
