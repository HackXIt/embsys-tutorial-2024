/*
 * step3_monitor.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "step3_monitor.h"

static bool received_byte = false;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        received_byte = true;
    }
}

void MonitoringTask(void *argument)
{
    monitor_argument_t monitor_argument = *((monitor_argument_t *)argument);
    uint8_t received_char;
    bool receiving = false;
    bool command_received = false;
    char rx_uart_buffer[MONITOR_RX_UART_BUFFER_SIZE];
    uint8_t rx_uart_index = 0;
    osStatus_t ret;
    data_object_t rx_data_object = {
        .senderId = NULL,
        .value = 0};
    data_object_t tx_data_object = {
        .senderId = NULL,
        .value = 0};
    HAL_UART_Receive_IT(&huart2, &received_char, 1);
    for (;;)
    {
        ret = osMessageQueueGet(monitor_argument.monitor_queue, &rx_data_object, NULL, MONITOR_QUEUE_POLLING_TIMEOUT);
        switch (ret)
        {
        case osOK:
            if (receiving)
            {
                // Do not print while receiving UART data (usability)
                break;
            }
            // Received data from producer
            for (uint8_t i = 0; i < monitor_argument.producer_count; i++)
            {
                if (monitor_argument.producer_ids[i] == rx_data_object.senderId)
                {
                    printf("RX from producer %u: %lu%s", i, rx_data_object.value, newLine);
                    break;
                }
            }
            break;
        case osErrorTimeout:
            // No data received from producers
            break;
        case osErrorResource:
            // Queue is empty (nothing to get from the queue (try semantics).)
            break;
        case osErrorParameter:
            // parameter mq_id is NULL or invalid, non-zero timeout specified in an ISR.
            break;
        default:
            // Unexpected / Unhandled error
            break;
        }
        if (received_byte)
        {
            receiving = true;
            printf("%c", received_char);
            if (received_char == '\r')
            {
                rx_uart_buffer[rx_uart_index] = '\0';
                rx_uart_index = 0;
                receiving = false;
                command_received = true;
                printf("%s", newLine);
            }
            else
            {
                rx_uart_buffer[rx_uart_index] = received_char;
                rx_uart_index = (rx_uart_index + 1) % MONITOR_RX_UART_BUFFER_SIZE;
                if (rx_uart_index == 0)
                {
                    printf("INPUT LIMIT REACHED!%s", newLine);
                    memset(rx_uart_buffer, 0, MONITOR_RX_UART_BUFFER_SIZE);
                }
            }
            received_byte = false;
            HAL_UART_Receive_IT(&huart2, &received_char, 1);
        }
        if (command_received)
        {
            uint32_t producer_number;
            uint32_t producer_value;
            unsigned int sscanf_result = sscanf(rx_uart_buffer, "T%lu %lu", &producer_number, &producer_value);
            switch (sscanf_result)
            {
            case 0:
                printf("Invalid command!%s", newLine);
                break;
            case 1:
                printf("Invalid command!%s", newLine);
                break;
            case 2:
                tx_data_object.senderId = monitor_argument.producer_ids[producer_number];
                tx_data_object.value = producer_value;
                ret = osMessageQueuePut(monitor_argument.update_queue, &tx_data_object, 0, 0);
                switch (ret)
                {
                case osOK:
                    printf("TX to producer %lu: %lu%s", producer_number, producer_value, newLine);
                    break;
                case osErrorTimeout:
                    // This should not occur, since we don't use timeouts => undefined behaviour
                    break;
                case osErrorResource:
                    // Queue is full (try-semantics)
                    break;
                case osErrorParameter:
                    // parameter mq_id is NULL or invalid, non-zero timeout specified in an ISR.
                    break;
                default:
                    // Unexpected / Unhandled error
                    break;
                }
                break;
            default:
                // Unexpected / Unhandled error
                break;
            }
            command_received = false;
            memset(rx_uart_buffer, 0, MONITOR_RX_UART_BUFFER_SIZE);
        }
    }
}

void initializeMonitoringTaskAttributes(osThreadAttr_t *monitorTask_attr,
                                        const char *monitorTask_name,
                                        osPriority_t monitorTask_priority,
                                        uint32_t *monitorTask_stack_buffer,
                                        StaticTask_t *monitorTask_control_block)
{
    monitorTask_attr->name = monitorTask_name;
    monitorTask_attr->priority = monitorTask_priority;
    monitorTask_attr->stack_size = MONITOR_STACK_SIZE * 4;
    monitorTask_attr->stack_mem = monitorTask_stack_buffer;
    monitorTask_attr->cb_mem = monitorTask_control_block;
    monitorTask_attr->cb_size = sizeof(StaticTask_t);
}
