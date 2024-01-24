
//
// INF1/B real time os kernel header
// copyright (C) 2020 by J. Krumm
// License: MIT
// Last change: 25.05.2021
//

#pragma once

#include "sys64.h"

//
// task control block (TCB) + state flags
//

struct tcb_t {
 uint16_t	tcb_state;
 uint16_t	tcb_id;
 uint8_t*	tcb_stack;
 uint8_t*	tcb_initial_stack;
 uint8_t*	tcb_initial_addr;
 struct tcb_t	*tcb_next_task;
 struct tcb_t	*tcb_next_blocked;
 uint32_t	tcb_timeout;
 uint32_t	tcb_ev_wait_mask;
 uint32_t	tcb_ev_sent_mask;
};

#define		T_READY		0x00
#define		T_RUNNING	0x10
#define		T_WAITING	0x20
#define		T_STOPPED	0x80

#define		OK		0
#define		E_ARG		1
#define		E_ID		2
#define		E_EVENTS	3

#ifndef task_schedule_next
#define task_schedule_next	task_schedule_prio
#endif

typedef struct tcb_t TCB;

//
// global internal kernel variables
//

extern TCB *g_first_task;
extern TCB *g_this_task;
extern TCB *g_next_timer;

//
// task handling API
//

extern void task_start_scheduler();
extern void task_schedule();
extern void task_dispatch();
extern void task_reset();
extern void task_term();

extern void task_schedule_rr();
extern void task_schedule_prio();

extern void task_activate_task(TCB *task);
extern int task_create_task(TCB *task, uint8_t *stack, int stacksize, void *entry);

extern void isr_activate_task(TCB *task);
extern void isr_task_cont();

//
// timer & event processing API
//

#define EVENT_WAIT_LONG	0xffffff
extern void task_wait_timeout(uint32_t delta);

extern int isr_event_send(TCB *task, uint32_t mask);

extern int event_send(TCB *task, uint32_t mask);
uint32_t event_wait(uint32_t mask, uint32_t timeout);


//
// semaphore API
//

struct sem_t {
 int s_count;
 TCB *s_blocked;
};

typedef struct sem_t SEM;

extern int semaphore_create_with_count(SEM *sem, int start);
extern int semaphore_create(SEM *sem);

extern int isr_semaphore_give(SEM *sem);
extern int semaphore_give(SEM *sem);
extern int semaphore_take(SEM *sem);

//
// helper functions for Interrupt service routine (ISR)
//

extern void isr_check_timers();

// The following inline routines are X86_64 specific

INLINE void push_all_regs() { 
 asm( "push %rax" );
 asm( "push %rcx" );
 asm( "push %rdx" );
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

INLINE void end_isr() {
 asm ( "iretq" );
}

INLINE void save_rsp() {
 asm( "mov %%rsp,%0" : "=m"(g_this_task->tcb_stack));
}

INLINE void restore_rsp() {
 asm( "mov %0,%%rsp" :: "m"(g_this_task->tcb_stack)); 
}

//
// template interrupt service routine
//




/*
NAKED void template_isr() {
 push_all_regs();
 save_rsp();
 //isr_check_timers();
 task_schedule_next();
}
*/



