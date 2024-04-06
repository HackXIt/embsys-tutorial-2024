/*
 * step3_monitor.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "step3_monitor.h"

void MonitoringTask(void *pvParameters) {
    while(1) {
        // Receive messages from the queue
        // Implement receiving logic here

        // Output values to the terminal
        // Implement UART communication here

        // Check for and process incoming commands
        // Adjust task intervals if needed
    }
}
