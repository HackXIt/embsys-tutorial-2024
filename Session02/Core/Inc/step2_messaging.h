/*
 * step4_messaging.hh
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#ifndef INC_STEP4_MESSAGING_H_
#define INC_STEP4_MESSAGING_H_

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "uart_helper.h"
#include "stdbool.h"
#include "printf.h"

typedef struct data_object
{
    osThreadId_t senderId;
    uint32_t value;
} data_object_t;

#define MSG_QUEUE_COUNT 5
#define MSG_QUEUE_SIZE sizeof(data_object_t)

typedef struct queue_objects
{
    osMessageQueueId_t update_queue;
    osMessageQueueId_t monitor_queue;
} queue_objects_t;

queue_objects_t CreateQueues();

#endif /* INC_STEP4_MESSAGING_H_ */
