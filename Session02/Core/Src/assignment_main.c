/*
 * assignment_main.c
 *
 *  Created on: Apr 6, 2024
 *      Author: RINI
 */

#include "assignment_main.h"

void StartDefaultTask(void *argument)
{
    CreateTasks();
    osThreadExit();
}