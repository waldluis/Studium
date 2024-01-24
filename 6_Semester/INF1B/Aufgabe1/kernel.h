
//
// INF1/B real time os kernel
// copyright (C) 2020 by J. Krumm
// License: MIT
//

#pragma once

#include "sys64.h"

//
// task pointer and state flags
//

typedef void(*tptr)();
#define S_IDLE 	0
#define S_READY	1

//
// global internal kernel variables
//

extern tptr task_array[];
extern int tcb[];
extern int task_queue[];
extern int tq_len;
extern int tq_wpos;
extern int tq_rpos;
extern int ta_cur;

//
// task handling API
//

extern void os_schedule_next();
extern void os_activate_task(int tid);

//
// helper functions for Interrupt service routine (ISR)
// The following inline routines are X86_64 specific
// 

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

INLINE void end_isr() {
 asm ( "iretq" );
}

//
// template interrupt service routine
//

/*
NAKED void template_isr() {
 push_all_regs();
 save_rsp();
 isr_check_timers();
 task_schedule_next();
}
*/