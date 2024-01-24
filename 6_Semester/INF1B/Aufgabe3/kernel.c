
//
// INF1/B real time os kernel
// copyright (C) 2020 by J. Krumm
// License: MIT
//

#include "kernel.h"

//
// global internal kernel variables
// prefix g_ denotes global quality
//

TCB *g_first_task = NULL;
TCB *g_this_task = NULL;
TCB *g_next_timer = NULL;


uint16_t x86_get_cs() {
 uint16_t rv;
 asm (" mov %%cs,%0" : "=r"(rv) );
 return rv;
}

uint16_t x86_get_ss() {
 uint16_t rv;
 asm (" mov %%ss,%0" : "=r"(rv) );
 return rv;
}

void push(TCB *task, uint64_t val) {
 uint64_t *sp = (uint64_t*)task->tcb_stack;
 *(--sp) = val;
 task->tcb_stack = (uint8_t*) sp;
}
 
INLINE void push_acd_regs() {
 asm( "push %rax; push %rcx; push %rdx ");
}

INLINE void push_other_regs() {
 asm( "push %rbx" );
 asm( "push %rbp" );
 asm( "push %rsi" );
 asm( "push %rdi" );
 asm( "push %r8" );
 asm( "push %r9" );
 asm( "push %r10" );
 asm( "push %r11" );
 asm( "push %r12" );
 asm( "push %r13" );
 asm( "push %r14" );
 asm( "push %r15" );
}

/*
INLINE void pop_all_regs() {
 asm( "pop %r15" );
 asm( "pop %r14" );
 asm( "pop %r13" );
 asm( "pop %r12" );
 asm( "pop %r11" );
 asm( "pop %r10" );
 asm( "pop %r9" );
 asm( "pop %r8" );
 asm( "pop %rdi" );
 asm( "pop %rsi" );
 asm( "pop %rbp" );
 asm( "pop %rbx" );
 asm( "pop %rdx" );
 asm( "pop %rcx" );
 asm( "pop %rax" );
}
*/

INLINE void pop_all_regs() {
 asm( "pop %r15; pop %r14; pop %r13; pop %r12" );
 asm( "pop %r11; pop %r10; pop %r9;  pop %r8" );
 asm( "pop %rdi; pop %rsi; pop %rbp" );
 asm( "pop %rbx; pop %rdx; pop %rcx; pop %rax" );
}

void task_cont_task(TCB *task) { 
 if (g_this_task != task) {
  TCB *tt = g_this_task;
  if (tt->tcb_state == T_RUNNING) tt->tcb_state = T_READY;
  g_this_task = task;
  g_this_task->tcb_state = T_RUNNING;
  
  sys_log('S', task->tcb_id);
 }
 
 restore_rsp();
 pop_all_regs(); 
 // return to restored task; will automatically re-enable interrupts (RFLAGS.IF=1)
 end_isr();
}

// highest priority first
NAKED void task_schedule_prio() {
 TCB *next_task = g_first_task;
 
 while (next_task) {
  if (next_task->tcb_state < T_WAITING) break;
  next_task = next_task->tcb_next_task;
 }
 
 task_cont_task(next_task);
}


// round robin style 
NAKED void task_schedule_rr() {
 TCB *next_task = g_this_task->tcb_next_task;
 
 while (next_task) {
  if (next_task->tcb_state < T_WAITING) break;
  next_task = next_task->tcb_next_task;
 }
 
 if (!next_task) {
  next_task = g_first_task;
  while (next_task) {
   if (next_task->tcb_state < T_WAITING) break;
   next_task = next_task->tcb_next_task;
  }
 }
 
 task_cont_task(next_task);
}

NAKED void task_schedule() {
 sys_disable_irq();
 asm( "mov %rax,-0x28(%rsp)" );		// save RAX
 asm( "mov %rcx,-0x30(%rsp)" );  	// save RCX 
 asm( "mov %rdx,-0x38(%rsp)" );  	// save RDX
 asm( "pop %rcx" ); 			// get RIP => RCX
 asm( "mov %rsp,%rax" );		// get RSP => RAX
 asm( "mov %ss,%rdx; push %rdx" ); 	// push SS
 asm( "push %rax" );			// push RSP
 asm( "pushfq" );			// push RFLAGS
 asm( "btsq $9,0(%rsp)" );		// set IF flag in saved RFLAGS
 asm( "mov %cs,%rdx; push %rdx" );	// push CS
 asm( "push %rcx");			// push RIP
 
 asm( "sub $0x18,%rsp" );		// RAX, RCX, RDX already saved
 push_other_regs(); 
 save_rsp();
 task_schedule_next();
}

NAKED void task_dispatch() { 
 restore_rsp();
 pop_all_regs();
 // return to task
 // should also allow IF by restoring RFLAGS
 end_isr();
}

static void internal_task_end_routine();

void task_init_task(TCB *task) {
 task->tcb_state = T_READY;
 task->tcb_stack = task->tcb_initial_stack;
 push(task, (uint64_t)internal_task_end_routine);
 uint64_t rsp = (uint64_t)(task->tcb_stack);
 
 // create stack frame for iretq
 push(task, x86_get_ss());
 push(task, rsp);
 push(task, 0x202); // set IF bit (no. 9 => allow IRQ); set reserved bit 1 
 push(task, x86_get_cs());
 push(task, (uint64_t)(task->tcb_initial_addr));
 
  // push 15 quadword zeros for register start values; exclude RSP
 for (int idx = 0; idx < 15; idx++) { 
  push(task, 0);
 } 
 
 task->tcb_timeout = 0;
 task->tcb_ev_wait_mask = 0;
 task->tcb_ev_sent_mask = 0;
 task->tcb_next_blocked = NULL;
}

// currently equivalent to task_term()
// could also restart task => task_init_task(g_this_task)
static void internal_task_end_routine() {
 sys_disable_irq();
 sys_log('f', g_this_task->tcb_id);
 g_this_task->tcb_state = T_STOPPED;
 task_schedule();
}

int task_create_task(TCB *task, uint8_t *stack, int stacksize, void *entry) {
 static int s_id = 0;
 if (task == NULL) return E_ARG;
 
 if (stacksize < 2*256) return E_ARG;
 if (stack == NULL) return E_ARG;
 if (entry == NULL) return E_ARG;
 
 uint8_t * stack_ptr = stack + stacksize; 
 
 task->tcb_id = s_id++;
 task->tcb_state = T_READY;
 task->tcb_initial_stack = stack_ptr;
 task->tcb_initial_addr = (uint8_t*)entry;
 task->tcb_next_task = g_first_task;
 task->tcb_next_blocked = NULL;

 g_first_task = g_this_task = task;
 task_init_task(task);
 return OK;
}

void task_term() {
 sys_disable_irq();
 sys_log('F', g_this_task->tcb_id);
 g_this_task->tcb_state = T_STOPPED;
 task_schedule();
}

void task_activate_task(TCB *task) {
 if (task == NULL) return;
 sys_disable_irq();
 if (task->tcb_state == T_STOPPED) task_init_task(task);
 task_schedule();
}

void isr_activate_task(TCB *task) {
 if (task == NULL) return;
 if (task->tcb_state == T_STOPPED) task_init_task(task);
}

void task_start_scheduler() {
 TCB *tt = g_this_task;
 sys_log('S', tt->tcb_id);
 task_dispatch();
}
