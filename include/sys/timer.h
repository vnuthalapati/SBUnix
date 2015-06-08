#ifndef _TIMER_H
#define _TIMER_H

#include <sys/defs.h>

#define freq_div 1193

uint64_t counter;
uint64_t total_time;
//extern void timer_handler();
void timer_init();

#endif
