#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <sys/defs.h>

#define MAX_IDT 256
#define p 0x80
#define dpl 0x0
#define s 0x0
#define type1 0x0E
#define type4 0x0F
#define offset_16 0x000000000000FFFF
#define offset_32 0x00000000FFFFFFFF
#define type2 p | dpl | s | type1
#define type3 p | dpl | s | type4
#define udpl 0x60
#define type5 p | udpl | s | type1
//extern uint64_t final_rsp;

struct idtdescr
{
uint16_t offset_1;
uint16_t selector;
uint8_t ist;
uint8_t type;
uint16_t offset_2;
uint32_t offset_3;
uint32_t reserved;
}__attribute__((packed));

struct idtr_t{
uint16_t limit;
uint64_t offset;
}__attribute__((packed));

struct idtdescr idt[256];


void setup_idtr(uint64_t offset, uint16_t size_idt);
void set_interrupt_handler(int seg_selector, uint64_t offset, int number);
void set_interrupt_handler2(int seg_selector, uint64_t offset, int number);
void set_all_handlers();
#endif
