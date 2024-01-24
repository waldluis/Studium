

//
// INF1/B real time os kernel
// copyright (C) 2020 by J. Krumm
// License: MIT
//

#include "kernel.h"

#define TMAXQ	10
#define TNUM	3

int tq_len = 0;		// number of elements in task queue; tq_len < TMAXQ
int tq_wpos = 0;	// current write position in task queue
int tq_rpos = 0;	// current read position in task queue
int ta_cur = 0;		// current position in task array

void os_activate_task(int tid) {
 if (tid < 0 || tid >= TNUM) return;
 sys_disable_irq(); 
 sys_log('A', tid);
 
 tcb[tid] = S_READY;							//Status aktivieren

 sys_enable_irq();
}

void os_schedule_next() {
 int tid = 0;
 int is_ready = 0;

 sys_disable_irq();

 while (is_ready == 0)
 {
	 if (tcb[ta_cur] == S_READY)		//Status rücksetzen aber nicht für T0
	 {
		 if (ta_cur != 0) 
		 { 
			 tcb[ta_cur] = S_IDLE;
		 }
		 tid = ta_cur;
		 is_ready = 1;
	 }
	 else
	 {
		 ta_cur++;								//ta_cur hochsetzen oder rücksetzen
		 if (ta_cur >= TNUM) 
		 { 
			 ta_cur = 0; 
		 }
	 }
 }

 ta_cur++;								//ta_cur hochsetzen oder rücksetzen
 if (ta_cur >= TNUM)
 {
	 ta_cur = 0;
 }

 sys_log('S', tid);
 sys_enable_irq(); 
 (*task_array[tid])();
}

void task_0() {
 static int cnt = 0;
 
 sys_log('B', 0);
 sys_idle();
 cnt++;
 sys_log('E', 0);
}

void task_1() {
 static int cnt = 0;
 
 sys_log('B', 1);
 sys_log('R', 1);
 sys_idle();
 sys_idle();
 
 cnt++;
 sys_log('E', 1);
}

void task_2() {
 static int cnt = 0;
 
 sys_log('B', 2);
 sys_log('R', 2);
 sys_idle();
 sys_idle(); 

 if (cnt % 2 == 0) 
  os_activate_task(1);

 cnt++;
 sys_log('E', 2);
}

void timer_func() {
 static int cnts = 0;
 
 sys_log('I', 8);
 
 if (cnts % 12 == 2) 
  os_activate_task(2);

 if (cnts % 6 == 2)
  os_activate_task(1);
   
 cnts++;
}

tptr task_array[] = { task_0, task_1, task_2 };
int tcb[TNUM] = { S_READY, S_IDLE, S_IDLE };
int task_queue[TMAXQ+1];

NAKED void app_isr() {
 push_all_regs();
 timer_func();
 pop_all_regs();
 end_isr();
}

int app_main() {
 sys_enable_irq();
 for (int count = 0; count < 50; count++) os_schedule_next();
 return 0;
}