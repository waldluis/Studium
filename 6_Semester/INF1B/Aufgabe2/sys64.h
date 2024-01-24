
//
// INF1/B real time os system abstraction header
// copyright (C) 2020 by J. Krumm
// License: MIT
//

#pragma once
#include <inttypes.h>
#include <stddef.h>

extern int sys_log(int action, int source);
extern int sys_set_tick_interval(int tick_interval);
extern int sys_exit();
extern int sys_get_ticks();
extern void sys_idle();
extern void sys_sleep(int delay);
extern void sys_disable_irq();
extern void sys_enable_irq();

extern int sys_printf(const char *fmt, ...);

#define NAKED __attribute__((naked))
#define INLINE inline __attribute__((always_inline))
