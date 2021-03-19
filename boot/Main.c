#include "stdint.h"
#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"
#include "stdbool.h"
#include "task.h"

static void Hw_init(void);
static void Timer_test(void);

static void Kernel_init(void);

void User_task0(void);
void User_task1(void);
void User_task2(void); 


void main(void)
{
	Hw_init();

	uint32_t i = 100;
	while(i--)
	{
		Hal_uart_put_char('N');
	}
	Hal_uart_put_char('\n');

	putstr("Hello World!\n");
	
	//while(true);

	//Timer_test();

    Kernel_init();
}

static void Hw_init(void)
{
	Hal_interrupt_init();
	Hal_uart_init();
	Hal_timer_init();
}

static void Timer_test(void)
{
    while(true)
    {
        putstr("tic\n");
        delay(1000);
    }
}

///////////////////////////////////////////////

static void Kernel_init(void)
{
    uint32_t taskId;

    Kernel_task_init();

    taskId = Kernel_task_create(User_task0);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task0 creation fail\n");
    }

    taskId = Kernel_task_create(User_task1);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task1 creation fail\n");
    }

    taskId = Kernel_task_create(User_task2);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task2 creation fail\n");
    }

    Kernel_task_start();
}

void User_task0(void)
{
    uint32_t local = 0;

    while(true){
        delay(1000);
        putstr("User Task #0\n");
        Kernel_yield();
    }
}

void User_task1(void)
{
    uint32_t local = 0;

    while(true){
        delay(1000);
        putstr("User Task #1\n");
        Kernel_yield();
    }}

void User_task2(void)
{
    uint32_t local = 0;

    while(true){
        delay(1000);
        putstr("User Task #2\n");
        Kernel_yield();
    }
}