#include<sys/kernlib.h>
#include <sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/tarfs.h>
#include <sys/timer.h>
#include <sys/interrupt.h>
#include <sys/pmap.h>
#include <sys/tarfshandling.h>
//#include <sys/proc.h>
#include <sys/sched.h>
//uint64_t exception_stack;
void start(uint32_t* modulep, void* physbase, void* physfree)
{
	uint64_t address = (uint64_t)(&idt);
        uint16_t size_idt = (uint16_t)(sizeof(idt));
	int my_variable = 0;
//        int i = 922222895;
	//int i =0;
        struct smap_t {
                uint64_t base, length;
                uint32_t type;
        }__attribute__((packed)) *smap;
	struct process *newproc1,*newproc2,*newproc3;
        cls();
//        while(--i>0);
        while(modulep[0] != 0x9001) modulep += modulep[1]+2;
        for(smap = (struct smap_t*)(modulep+2); smap < (struct smap_t*)((char*)modulep+modulep[1]+2*4); ++smap) {
                if (smap->type == 1 /* memory */ && smap->length != 0) {
                   kprintf("Available Physical Memory [%x-%x]\n", smap->base, smap->base + smap->length);
                }
        }
        kprintf("tarfs in [%p:%p]\n", &_binary_tarfs_start, &_binary_tarfs_end);
        set_all_handlers();
        setup_idtr(address,size_idt);
	npages_determine(134205440);
	set_consts((uint64_t)physbase,(uint64_t)physfree);
	mm_init();
	loadcr3(katopa((uint64_t)pml4e),(uint64_t)physbase,(uint64_t)physfree);
	my_variable++;
	newproc1 = (struct process*)process_setup((uint64_t)physbase,(uint64_t)physfree,"bin/newhello");
	curproc_count++;
	newproc2 = process_setup((uint64_t)physbase,(uint64_t)physfree,"bin/sacrifice");
	curproc_count++;
	newproc3 = process_setup((uint64_t)physbase,(uint64_t)physfree,"bin/pragathi");
	proc_status(newproc1);
	proc_status(newproc2);
	proc_status(newproc3);	
	cur_proc = newproc1;
	/*while(i<10000)
	{
	kmalloc(30);
	i++;
	}*/
	exception_stack = page_alloc();
	first_sched();
        while(1){}

}

#define INITIAL_STACK_SIZE 4096
char stack[INITIAL_STACK_SIZE];
uint32_t* loader_stack;
extern char kernmem, physbase;
struct tss_t tss;

void boot(void)
{
	// note: function changes rsp, local stack variables can't be practically used
	//register char *s, *v;
	__asm__(
		"movq %%rsp, %0;"
		"movq %1, %%rsp;"
		:"=g"(loader_stack)
		:"r"(&stack[INITIAL_STACK_SIZE])
	);
	reload_gdt();
	setup_tss();
	start(
		(uint32_t*)((char*)(uint64_t)loader_stack[3] + (uint64_t)&kernmem - (uint64_t)&physbase),
		&physbase,
		(void*)(uint64_t)loader_stack[4]
	);
	//s = "!!!!! start() returned !!!!!";
	//for(v = (char*)0xb8000; *s; ++s, v += 2) *v = *s;
	while(1);
}
