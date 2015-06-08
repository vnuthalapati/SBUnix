#ifndef _STDIO_H
#define _STDIO_H
#include<sys/defs.h>
int printf(const char *format, ...);
int scanf(const char *format, ...);
void write2(int fd,const void *buf, uint64_t count);
#endif
