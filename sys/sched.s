#include "sys/sched.h"
.text
.global sched_asm
sched_asm:
movw $0x23,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
 
ret
