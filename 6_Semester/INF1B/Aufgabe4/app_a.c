
//
// INF1/B real time os app
// copyright (C) 2020 by J. Krumm
// License: Unlicense
//

#include "kernel.h"

uint8_t stack0[64 * 1024];
uint8_t stack1[64 * 1024];
uint8_t stack2[64 * 1024];
uint8_t stack3[64 * 1024];
TCB tcb0, tcb1, tcb2, tcb3;
#define EVT1 1
#define EVT2 2
#define EVT3 4

int g_total;

void do_some_work() {
	int tid = g_this_task->tcb_id;
	sys_printf("task%d: g_total = %d\n", tid, g_total);
	sys_idle();
	sys_idle();
	sys_idle();
}

void task0() {
	while (1) {
		sys_idle();
	}
}

void task1() {
	event_wait(EVT1, 5);
	g_total = 0;
	event_send(&tcb2, 2);
}

void task2() {
	while (1)
	{
		event_wait(EVT2, 1000);
		g_total++;
		do_some_work();
		event_send(&tcb3, EVT3);
	}
}

void task3() {
	while (1)
	{
		event_wait(EVT3, 1000);
		g_total = g_total * 2;
		do_some_work();
		event_send(&tcb2, EVT2);
	}
}

NAKED void app_isr() {
	push_all_regs();
	save_rsp();

	if (sys_get_ticks() == 10)
	{
		isr_event_send(&tcb1, EVT1);
	}

	if (sys_get_ticks() > 100) sys_exit();
	sys_log('I', 8);
	isr_check_timers();
	task_schedule_next();
}

int app_main() {
	task_create_task(&tcb0, stack0, sizeof(stack0), task0);
	task_create_task(&tcb1, stack1, sizeof(stack1), task1);
	task_create_task(&tcb2, stack2, sizeof(stack2), task2);
	task_create_task(&tcb3, stack3, sizeof(stack3), task3);
	sys_enable_irq();

	task_start_scheduler();
	return 0;
}
