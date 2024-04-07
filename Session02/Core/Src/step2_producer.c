/*
 * step2_producer.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "step2_producer.h"

void ProducerTask(void *argument)
{
    producer_argument_t producer_argument = *((producer_argument_t *)argument);
    uint32_t producer_value = producer_argument.initial_value;
    uint32_t delay = INITIAL_DELAY;
    data_object_t rx_data_object = {
        .senderId = NULL,
        .value = 0};
    data_object_t tx_data_object = {
        .senderId = osThreadGetId(),
        .value = producer_value};
    osStatus_t ret;
    for (;;)
    {
        ret = osMessageQueueGet(producer_argument.update_queue, &rx_data_object, NULL, 0);
        switch (ret)
        {
        case osOK:
            if (rx_data_object.senderId == tx_data_object.senderId)
            {
                // Update the delay value
                delay = rx_data_object.value;
            }
            else
            {
                // Not our message, put it back in the queue
                osMessageQueuePut(producer_argument.update_queue, &rx_data_object, 0, 0);
            }
            break;
        case osErrorResource:
            // EXPECTED behavior when queue is empty (try-semantics)
            break;
        case osErrorParameter:
            // parameter mq_id is NULL or invalid, non-zero timeout specified in an ISR.
            break;
        case osErrorTimeout:
            // This should not occur, since we don't use timeouts => undefined behaviour
            break;
        default:
            // Unexpected / Unhandled error
            break;
        }
        ret = osMessageQueuePut(producer_argument.monitor_queue, &tx_data_object, 0, 0);
        switch (ret)
        {
        case osOK:
            // No error => increment counter value
            producer_value = (producer_value + 1) % MAX_PRODUCER_VALUE;
            tx_data_object.value = producer_value;
            break;
        case osErrorTimeout:
            // This should not occur, since we don't use timeouts => undefined behaviour
            break;
        case osErrorResource:
            // PROBLEM behavior => queue is full => monitor is possibly dead!
            break;
        case osErrorParameter:
            // Actual problematic ERROR occurred => panic!
            break;
        default:
            // Unhandled error occoured => panic!
            break;
        }
        // Delay for a period of time
        osDelay(delay);
    }
}

// NOTE Helper function to initialize producer task attributes
void initializeProducerTaskAttributes(osThreadAttr_t *prodTask_attr,
                                      const char *prodTask_name,
                                      osPriority_t prodTask_priority,
                                      uint32_t *prodTask_stack_buffer,
                                      uint32_t prodTask_stack_size,
                                      StaticTask_t *prodTask_control_block)
{
    prodTask_attr->name = prodTask_name;
    prodTask_attr->attr_bits = 0;
    prodTask_attr->priority = prodTask_priority;
    prodTask_attr->stack_size = PRODUCER_STACK_SIZE * 4;
    prodTask_attr->stack_mem = prodTask_stack_buffer;
    prodTask_attr->cb_mem = prodTask_control_block;
    prodTask_attr->cb_size = sizeof(StaticTask_t);
}