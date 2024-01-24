
//
// INF1/B real time os app
// copyright (C) 2020 by J. Krumm
// License: Unlicense
//

#define task_schedule_next	task_schedule_rr

#include "kernel.h"

uint8_t stack0[64*1024];
uint8_t stack1[64*1024];
uint8_t stack2[64*1024];
TCB tcb0, tcb1, tcb2;

void task0() {
 while (1) {
  if (sys_get_ticks() > 100) sys_exit();
  sys_idle();
 }
}

void task1() {
 while (1) {
  sys_idle();
  sys_idle();
 }
}

void task2() {
 while (1) {
  sys_idle();
  sys_idle();
  sys_idle();
 }
}

NAKED void app_isr() {
 // interrupt service already with cleared IF
 push_all_regs();
 save_rsp();

 sys_log('I', 8);
 task_schedule_next();

 // will not come back to here after task switch!
 task_dispatch();
}

int app_main() {
 task_create_task(&tcb0, stack0, sizeof(stack0), task0);
 task_create_task(&tcb1, stack1, sizeof(stack1), task1);
 task_create_task(&tcb2, stack2, sizeof(stack2), task2);
 sys_enable_irq();

 task_start_scheduler();
 return 0;
}
