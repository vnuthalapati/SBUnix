#include<sys/kernlib.h>
//#include <sys/proc.h>
#include <sys/gdt.h>
#include <sys/sched.h>
#include <sys/operations.h>
#include <sys/sbunix.h>
int i=1;
int first=1;
void sched()
{
	struct process * curr = cur_proc;
/*	int num = cur_proc-procs;
	struct process * temp = cur_proc;
	for(i=(num+1)%10 ; i != num ; i = (i+1)%10)
	{
		if((procs+i)->state == ENV_RUNNABLE)
		{
			prev = cur_proc;
			cur_proc = 
		}
	}*/
	struct process * temp,*cleaner=head;
	do
	{
		if(cleaner->state==ENV_KILLED && cleaner->status==1)
		{
			clear_queues(cleaner);
			free_proc(cleaner);
			cleaner->status = 2;
		
		}
		cleaner = cleaner->next;
		
	}while(cleaner!=head);
	temp = cur_proc->next;
	while(temp != cur_proc)
	{
		if(temp->state == ENV_RUNNABLE)
		{
			prev = cur_proc;
			if(cur_proc->state==ENV_RUNNING)
			cur_proc->state = ENV_RUNNABLE;
//			if(prev->state==ENV_KILLED)
	//		free_proc(prev);
//			cur_proc = temp;
			break;
		}
		temp = temp->next;	
	}
	if(temp == cur_proc)
	{
		prev = cur_proc;
//		cur_proc = cur_proc;
	}
	cur_proc = temp;
	curr = cur_proc;
	if(curr->state==ENV_RUNNABLE||curr->state==ENV_RUNNING)
	{
		curr->state = ENV_RUNNING;
		loadcr3(katopa((uint64_t)curr->pml4e),0,0);
		tss.rsp0 = curr->kstack;
		__asm volatile("movq %0,%%rsp"::"r"(curr->tf.rsp):"memory","cc","%rsp");
//		if(prev->state==ENV_KILLED&&prev!=curr&&prev->status==1)
		{
        //              	free_proc(prev);
			//prev->status = 0;
//			loadcr3(katopa((uint64_t)curr->pml4e),0,0);
//			prev->status = 2;
		}
		sched_asm();
		__asm volatile(POPALL:::"cc","memory");
		 __asm volatile("addq $0x8,%%rsp":::"cc","memory","%rsp");
		__asm volatile("iretq");
	}
	else{
	kprintf("not found anything\n");
	while(1);
	}
}

void first_sched()
{
        struct process * curr = cur_proc;
        uint16_t tr = 0x2b;
        {
                cur_proc->state = ENV_RUNNING;
                loadcr3(katopa((uint64_t)curr->pml4e),0,0);
                tss.rsp0 = curr->kstack;
        }
        if(first==1){
                __asm volatile("ltr %0"::"r"(tr):);
                first = 0;
                }
                __asm volatile("movq %0,%%rsp"::"r"(curr->tf.rsp):"memory","cc","%rsp");
                sched_asm();
                __asm volatile(POPALL:::"cc","memory");
                __asm volatile("addq $0x8,%%rsp":::"cc","memory","%rsp");
		 __asm volatile("iretq");

}
