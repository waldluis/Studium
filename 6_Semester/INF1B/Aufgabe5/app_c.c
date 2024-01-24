
//
// INF1/B real time os app
// copyright (C) 2020 by J. Krumm
// License: Unlicense
//

#include "kernel.h"

int8_t  wifi_msg[256];
uint8_t stack0[64 * 1024];
uint8_t stack1[64 * 1024];
uint8_t stack2[64 * 1024];
uint8_t stack3[64 * 1024];
TCB tcb0, tcb1, tcb2, tcb_w;  

SEM writing, sending;

void task0() {
	while (1) {
		sys_idle();
	}
}

void task1()
{
    int i;
    semaphore_take(&writing);
    for(i = 0; i < 4; i++)
    {
        wifi_msg[i] = '1';
        sys_idle();
    }
    wifi_msg[i] = 0;

    semaphore_give(&sending);
    semaphore_give(&writing);
}

void task2() {
 int idx;
 semaphore_take(&writing);
 for (idx = 0; idx < 6; idx++) {
  wifi_msg[idx] = '2';
  sys_idle();
 }
 wifi_msg[idx] = 0;

 semaphore_give(&sending);
 semaphore_give(&writing);
}

void task3() {
 int ticks = sys_get_ticks();
 while(1)
 {
     semaphore_take(&sending);
    ticks = sys_get_ticks();
    sys_printf("wifi send: time=%d, msg = %s\n", ticks, wifi_msg);
    sys_idle();
    semaphore_give(&sending);
 }
}

TCB *my_get_task(int tid) {
 for (TCB *tcb = g_first_task; tcb; tcb = tcb->tcb_next_task) {
  if (tcb->tcb_id == tid) return tcb;
 }
 return NULL;
}

int task_plan[] = { 5, 1, 15, 2, 25, 1, 27, 2, 40,  1, 43, 2, 44, 1, 55, 1, 56, 2, 100, -1};

NAKED void app_isr() {
 push_all_regs();
 save_rsp();

 static int cnt = 0;

 if (cnt >= sizeof(task_plan)/sizeof(int)) sys_exit();

 int tick = sys_get_ticks();
 int ticknum = task_plan[cnt];

 if (ticknum <= tick) {
  int tasknum = task_plan[cnt+1];
  TCB *tcb = my_get_task(tasknum);
 
  if (tcb)
   isr_activate_task(tcb);
  else
   sys_exit();

  cnt += 2;
 }

 sys_log('I', 8);
 task_schedule_next();
}

int app_main() {
 wifi_msg[0] = 0;

 // put your code here
    task_create_task(&tcb0, stack0, sizeof(stack0), task0);
	task_create_task(&tcb1, stack1, sizeof(stack1), task1);
	task_create_task(&tcb2, stack2, sizeof(stack2), task2);
	task_create_task(&tcb_w, stack3, sizeof(stack3), task3);
	sys_enable_irq();

    semaphore_create_with_count(&writing, 1);
    semaphore_create_with_count(&sending, 1);



    task_start_scheduler();
}