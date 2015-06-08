//#include<sys/kernlib.h>
//#include<sys/sbunix.h>
#include <sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/tarfs.h>
#include <sys/timer.h>
#include <sys/interrupt.h>
#include <sys/pmap.h>
#include <sys/tarfshandling.h>
#include <sys/proc.h>
#include <sys/sched.h>


extern void fault_handler(struct trap_frame *tf1)
{
	uint64_t address,physaddr,copy_address,copy_page;
	struct vma_area * temp;
	struct Page *temp_page;
	pte_t * temp_pte;
	__asm volatile("movq %%cr2,%0":"=r"(address)::"cc","memory");
	if(tf1->err_no==6)
	{
	temp = cur_proc->mm_struct;
	while(temp != NULL)
	{
		if(temp->vma_start<=address && temp->vma_end>=address)
		{
			physaddr = katopa(page_alloc());
			map_region(cur_proc->pml4e,address,physaddr,PGSIZE,USERPML4PERMISSION);
		}
		temp = temp->next;
	}
	}
	else if(tf1->err_no==7)
	{
	copy_address = address-address%PGSIZE;
	temp_pte = (pte_t*)pml4e_walk(cur_proc->pml4e,address,0,USERPML4PERMISSION);
	if(*temp_pte&~COW){
	temp_page =(struct Page*) (pages+(katopa(ptetoka(*temp_pte))/PGSIZE));
//	copy_address = address-address%PGSIZE;
        if(temp_page->page_ref==1)
	{
		*(temp_pte) = *(temp_pte) | USERPML4PERMISSION | 0x100;
		*(temp_pte) = *(temp_pte) & ~COW;
		loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
	}
	else
	{
		temp_page->page_ref--;
		copy_page = page_alloc();
		memcopy((char*)copy_address,(char*)copy_page,PGSIZE);
		map_region(cur_proc->pml4e,copy_address,katopa(copy_page),PGSIZE,USERPML4PERMISSION);
		loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
	}
	}
		
	}
	else{
//	kprintf("Segmentation Fault\n");
	//kprintf("faulting address->%x\n",address);
	cur_proc->state = ENV_KILLED;
	sched();
//	reset_os();	
	while(1);
	}
}

void reset_os()
{
 uint64_t address = (uint64_t)(&idt);
        uint16_t size_idt = (uint16_t)(sizeof(idt));
        int my_variable = 0;
	struct Page *temp;
	uint64_t freeing_address;
	/*
//        int i = 922222895;
        struct smap_t {
                uint64_t base, length;
                uint32_t type;
        }__attribute__((packed)) *smap;*/
        struct process *newproc1,*newproc2,*newproc3;
//        cls();
//        while(--i>0);
/*        while(modulep[0] != 0x9001) modulep += modulep[1]+2;
        for(smap = (struct smap_t*)(modulep+2); smap < (struct smap_t*)((char*)modulep+modulep[1]+2*4); ++smap) {
                if (smap->type == 1 && smap->length != 0) {
                   kprintf("Available Physical Memory [%x-%x]\n", smap->base, smap->base + smap->length);
                }
        }
        kprintf("tarfs in [%p:%p]\n", &_binary_tarfs_start, &_binary_tarfs_end);*/
        set_all_handlers();
        setup_idtr(address,size_idt);
        npages_determine(134205440);
        set_consts((uint64_t)PHYBASE,(uint64_t)PHYFREE);
        mm_init();
        loadcr3(katopa((uint64_t)pml4e),0,0);
        my_variable++;
        newproc1 = (struct process*)process_setup(0,0,"bin/newhello");
        curproc_count++;
        newproc2 = process_setup(0,0,"bin/sacrifice");
        curproc_count++;
        newproc3 = process_setup(0,0,"bin/pragathi");
        proc_status(newproc1);
        proc_status(newproc2);
        proc_status(newproc3);
        cur_proc = newproc1;
	temp = free_list;
	while(temp!=NULL)
	{
//		freeing_address =
//	uint64_t address;
  //      struct Page *temp;
//        temp = free_list;
//        free_list = free_list->next;
//        temp->page_ref = 1;
        freeing_address = (temp-pages)*PGSIZE + KERNOFFSET;
	memset(freeing_address,PGSIZE,'\0');
        //printf("alloc count--->%d\n",
//        alloccount++;
        //memset((uint64_t)temp,PGSIZE,'\0');
  //      return address;
	temp= temp->next;
	}
        exception_stack = page_alloc();
        first_sched();
        while(1){}
}
