
//
// INF1/B real time os app
// copyright (C) 2020 by J. Krumm
// License: Unlicense
//

#include "kernel.h"

uint8_t stack0[64 * 1024];
uint8_t stack1[64 * 1024];
uint8_t stack2[64 * 1024];
TCB tcb0, tcb1, tcb2;

void task0() {
	while (1) {
		sys_idle();
	}
}

void task1() {
	sys_idle();
	sys_idle();
	task_term();
}

void task2() {
	static int count1 = 0;
	count1++;
	if ((count1 % 2) == 0)//activate Task 1 every second time
	{
		task_activate_task(&tcb1);
	}
	sys_idle();
	sys_idle();
	task_term();
}

NAKED void app_isr() {
	push_all_regs();
	save_rsp();

	static int count = 0;
	count++;

	if ((count % 8) == 0)//activate Task 2 every 8th time
	{
		isr_activate_task(&tcb2);
	}

	if (sys_get_ticks() > 100) sys_exit();
	sys_log('I', 8);
	task_schedule_next();
}

int app_main() {
	task_create_task(&tcb0, stack0, sizeof(stack0), task0);
	task_create_task(&tcb1, stack1, sizeof(stack1), task1);
	task_create_task(&tcb2, stack2, sizeof(stack2), task2);
	sys_enable_irq();

	task_start_scheduler();
	return 0;
}