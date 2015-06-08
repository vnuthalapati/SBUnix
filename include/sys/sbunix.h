#ifndef __SBUNIX_H
#define __SBUNIX_H

#include <sys/defs.h>
extern int x;
extern int y;
void kprintf(const char *fmt, ...);
int writedisp(int fd, const char* add, int size);
void cls();
void init_pics(int pic1, int pic2);
void memcopy(volatile char *src,volatile char *dst,int size);
void memcpy(volatile char *src,volatile char *dst,int size);
void reset_os();
#endif
