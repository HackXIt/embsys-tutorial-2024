#include "cmsis_os2.h"

#define STACK_SIZE 128

uint32_t task_stack[STACK_SIZE];
StaticTask_t task_control_block;

void MyTask(void *argument)
{
    // Task initialization here
    while (1)
    {
        // Task code here
    }
}

void InitTaskStatic(void)
{
    // Initialize memory outside function scope
    osThreadId_t task_id;
    osThreadAttr_t task_attributes = {
        .name = "StaticTask",
        .attr_bits = 0, // Important! Initialize to 0, otherwise the task will not be created
        .priority = osPriorityNormal,
        .stack_mem = task_stack,
        .stack_size = STACK_SIZE * 4,
        .cb_mem = &task_control_block,
        .cb_size = sizeof(StaticTask_t)};
    task_id = osThreadNew(MyTask, NULL, &task_attributes);
    if (task_id == NULL)
    {
        // Handle failure - task was not created
    }
}

void InitTaskDynamic(void)
{
    osThreadId_t task_id;
    osThreadAttr_t task_attributes = {
        .name = "DynamicTask",
        .attr_bits = 0,
        .priority = osPriorityNormal,
        .stack_size = STACK_SIZE * 4,
        .stack_mem = NULL,
        .stack_size = 0,
        .cb_mem = NULL,
        .cb_size = 0};
    task_id = osThreadNew(MyTask, NULL, &task_attributes);
    if (task_id == NULL)
    {
        // Handle failure - task was not created
    }
}