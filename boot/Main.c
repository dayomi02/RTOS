#include "stdint.h"
#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"
#include "stdbool.h"

static void Hw_init(void);
static void Timer_test(void);

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

	Timer_test();

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