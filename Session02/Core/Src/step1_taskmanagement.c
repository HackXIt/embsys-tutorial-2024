/*
 * step1_taskmanagement.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "step1_taskmanagement.h"

osThreadId_t producer_thread_id[NUM_PRODUCERS];
uint32_t producer_thread_stack[NUM_PRODUCERS][PRODUCER_STACK_SIZE];
StaticTask_t producer_thread_control_block[NUM_PRODUCERS];
// NOTE Initially provided values for the producers (Sets max limit to 10 producers, otherwise adjust the size of the array accordingly)
uint32_t producer_initial_values[10] = {
    8, 4, 2, 6, 1, 9, 7, 3, 5, 0};
osThreadId_t monitor_thread_id;
uint32_t monitor_thread_stack[MONITOR_STACK_SIZE];
StaticTask_t monitor_thread_control_block;
osThreadAttr_t monitor_attributes;

void CreateTasks()
{
    printf("Create queues...%s", newLine);
    queue_objects_t queues = CreateQueues();

    printf("Creating producers...%s", newLine);
    osThreadAttr_t producer_attributes[NUM_PRODUCERS];

    for (uint8_t i = 0; i < NUM_PRODUCERS; i++)
    {
        initializeProducerTaskAttributes(&producer_attributes[i],
                                         "ProducerTask",
                                         osPriorityLow,
                                         producer_thread_stack[i],
                                         PRODUCER_STACK_SIZE,
                                         &producer_thread_control_block[i]);
        producer_argument_t *producer_args = pvPortMalloc(sizeof(producer_argument_t));
        if (producer_args == NULL)
        {
            printf("Failed to allocate memory for producer arguments.%s", newLine);
        }
        producer_args->initial_value = producer_initial_values[i];
        producer_args->update_queue = queues.update_queue;
        producer_args->monitor_queue = queues.monitor_queue;
        producer_thread_id[i] = osThreadNew(ProducerTask, (void *)producer_args, &producer_attributes[i]);
        // NOTE ALWAYS check if the thread is created successfully
        if (producer_thread_id[i] == NULL)
        {
            printf("Failed to create producer thread %d%s", i, newLine);
        }
    }

    printf("Create monitor...%s", newLine);
    initializeMonitoringTaskAttributes(&monitor_attributes, "MonitorTask", osPriorityNormal, monitor_thread_stack, &monitor_thread_control_block);
    monitor_argument_t *monitor_args = pvPortMalloc(sizeof(monitor_argument_t));
    if (monitor_args == NULL)
    {
        printf("Failed to allocate memory for monitor arguments.%s", newLine);
    }
    monitor_args->producer_ids = producer_thread_id;
    monitor_args->producer_count = NUM_PRODUCERS;
    monitor_args->monitor_queue = queues.monitor_queue;
    monitor_args->update_queue = queues.update_queue;
    monitor_thread_id = osThreadNew(MonitoringTask, (void *)monitor_args, &monitor_attributes);
}
