#include<sys/interrupt.h>
#include<sys/sbunix.h>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr128();
extern void idt_ins(struct idtr_t*);
//void *memset(void *str, int c, int n);
void setup_idtr(uint64_t address, uint16_t size_idt)
{
	struct idtr_t idtrb;
	//uint64_t address = (uint64_t)(&idt);
	idtrb.limit = (sizeof(struct idtdescr)*256)-1;
	idtrb.offset = address;
	//printf("off is %d\n",(int)idtrb.offset);
	//printf("idt is %p\n",idt);
//	memset(&idt,0,sizeof(struct idtdescr)*256);
	idt_ins(&idtrb);
	//__asm volatile("lidt (%0)"::"p"(&idtrb):"cc","memory");
	//printf("off is %d\n",(int)idtrb.offset);
	//printf("off is %d\n",(int)idtrb.offset);
        //printf("idt is %p\n",idt);
}

void set_interrupt_handler(int seg_selector, uint64_t offset, int number)
{
	uint64_t offsetcpy1 = offset;
	uint64_t offsetcpy2 = offset;
	uint64_t offsetcpy3 = offset;
	
	idt[number].offset_1 = offsetcpy1 & offset_16;
	idt[number].selector = 8;
	idt[number].ist = 0;
	idt[number].type = type2;
	idt[number].offset_2 = (offsetcpy2 >> 16) & offset_16;
	idt[number].offset_3 = (offsetcpy3 >> 32) & offset_32;
	idt[number].reserved = 0;
}

void set_interrupt_handler2(int seg_selector, uint64_t offset, int number)
{
        uint64_t offsetcpy1 = offset;
        uint64_t offsetcpy2 = offset;
        uint64_t offsetcpy3 = offset;

        idt[number].offset_1 = offsetcpy1 & offset_16;
        idt[number].selector = 8;
        idt[number].ist = 0;
        idt[number].type = type2;
        idt[number].offset_2 = (offsetcpy2 >> 16) & offset_16;
        idt[number].offset_3 = (offsetcpy3 >> 32) & offset_32;
        idt[number].reserved = 0;
}
void set_interrupt_handler3(int seg_selector, uint64_t offset, int number)
{
        uint64_t offsetcpy1 = offset;
        uint64_t offsetcpy2 = offset;
        uint64_t offsetcpy3 = offset;

        idt[number].offset_1 = offsetcpy1 & offset_16;
        idt[number].selector = 8;
        idt[number].ist = 0;
        idt[number].type = type5;
        idt[number].offset_2 = (offsetcpy2 >> 16) & offset_16;
        idt[number].offset_3 = (offsetcpy3 >> 32) & offset_32;
        idt[number].reserved = 0;
}

void set_all_handlers()
{
	//memset(idt,0,128*256-1);
	set_interrupt_handler2(8, ((uint64_t)isr0), 0);
	set_interrupt_handler2(8, ((uint64_t)isr1), 1);
	set_interrupt_handler2(8, ((uint64_t)isr2), 2);
	set_interrupt_handler2(8, ((uint64_t)isr3), 3);
	set_interrupt_handler2(8, ((uint64_t)isr4), 4);
	set_interrupt_handler2(8, ((uint64_t)isr5), 5);
	set_interrupt_handler2(8, ((uint64_t)isr6), 6);
	set_interrupt_handler2(8, ((uint64_t)isr7), 7);
	set_interrupt_handler2(8, ((uint64_t)isr8), 8);
	set_interrupt_handler2(8, ((uint64_t)isr9), 9);
	set_interrupt_handler2(8, ((uint64_t)isr10), 10);
	set_interrupt_handler2(8, ((uint64_t)isr11), 11);
	set_interrupt_handler2(8, ((uint64_t)isr12), 12);
	set_interrupt_handler2(8, ((uint64_t)isr13), 13);
	set_interrupt_handler2(8, ((uint64_t)isr14), 14);
	set_interrupt_handler2(8, ((uint64_t)isr15), 15);
	set_interrupt_handler2(8, ((uint64_t)isr16), 16);
	set_interrupt_handler2(8, ((uint64_t)isr17), 17);
	set_interrupt_handler2(8, ((uint64_t)isr18), 18);
	set_interrupt_handler2(8, ((uint64_t)isr19), 19);
	set_interrupt_handler2(8, ((uint64_t)isr20), 20);
	set_interrupt_handler2(8, ((uint64_t)isr21), 21);
	set_interrupt_handler2(8, ((uint64_t)isr22), 22);
	set_interrupt_handler2(8, ((uint64_t)isr23), 23);
	set_interrupt_handler2(8, ((uint64_t)isr24), 24);
	set_interrupt_handler2(8, ((uint64_t)isr25), 25);
	set_interrupt_handler2(8, ((uint64_t)isr26), 26);
	set_interrupt_handler2(8, ((uint64_t)isr27), 27);
	set_interrupt_handler2(8, ((uint64_t)isr28), 28);
	set_interrupt_handler2(8, ((uint64_t)isr29), 29);
	set_interrupt_handler2(8, ((uint64_t)isr30), 30);
	set_interrupt_handler2(8, ((uint64_t)isr31), 31);
	set_interrupt_handler(8, ((uint64_t)isr32), 32);
	set_interrupt_handler3(8, ((uint64_t)isr33), 33);
	set_interrupt_handler3(8,((uint64_t)isr128),128);
}
/*
void *memset(void *str, int c, int  n)
{
int i=0;
char *temp=(char*)str;
for(i=0;i<n;i++)
{
*(temp+i)=c;
}
return (void*)temp;
}*/
