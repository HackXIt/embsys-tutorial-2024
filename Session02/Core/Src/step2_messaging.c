/*
 * step4_messaging.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "step2_messaging.h"

uint32_t update_queue_buffer[MSG_QUEUE_COUNT * MSG_QUEUE_SIZE];
StaticQueue_t update_queue_control_block;
osMessageQueueAttr_t update_queue_attr = {
    .name = "ProducerUpdateQueue",
    .attr_bits = 0,
    .cb_mem = &update_queue_control_block,
    .cb_size = sizeof(StaticQueue_t),
    .mq_mem = &update_queue_buffer,
    .mq_size = sizeof(update_queue_buffer)};
uint32_t monitor_queue_buffer[MSG_QUEUE_COUNT * MSG_QUEUE_SIZE];
StaticQueue_t monitor_queue_control_block;
osMessageQueueAttr_t monitor_queue_attr = {
    .name = "ProducerToMonitorQueue",
    .attr_bits = 0,
    .cb_mem = &monitor_queue_control_block,
    .cb_size = sizeof(StaticQueue_t),
    .mq_mem = &monitor_queue_buffer,
    .mq_size = sizeof(monitor_queue_buffer)};

queue_objects_t CreateQueues()
{
    queue_objects_t queue_objects;
    queue_objects.update_queue = osMessageQueueNew(MSG_QUEUE_SIZE, sizeof(data_object_t), &update_queue_attr);
    if (queue_objects.update_queue == NULL)
    {
        printf("Failed to create update queue.%s", newLine);
    }
    queue_objects.monitor_queue = osMessageQueueNew(MSG_QUEUE_SIZE, sizeof(data_object_t), &monitor_queue_attr);
    if (queue_objects.monitor_queue == NULL)
    {
        printf("Failed to create monitor queue.%s", newLine);
    }
    return queue_objects;
}