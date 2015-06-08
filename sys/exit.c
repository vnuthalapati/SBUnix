#include<sys/kernlib.h>
#include<sys/sched.h>
void kexit(int num)
{
	int i=0;//,first=0;
	struct waitlist  *temp = wait_list;
	int h;
	struct waitlist  *traverser;
	exit_procs[total_procs][0] = cur_proc->id;
	exit_procs[total_procs][1] = num;
	total_procs++;
	cur_proc->state = ENV_KILLED;
	while(temp!=NULL)
        {
                for(i=0;i<total_procs;i++)
                {
                        if(temp->waiting_on == exit_procs[i][0])
                        {
                                temp->proc->state = ENV_RUNNABLE;
                                traverser = wait_list;
                                if(traverser == temp)
                                        wait_list = temp->next;
				else{
                                while(traverser->next!=temp)
                                        traverser = traverser->next;
                                traverser->next = temp->next;}
                        }


                }
                temp = temp->next;

        }
	for(h=0;h<100;h++)	
	kclose(h);
	//myproc->status = 2;
	//kprintf("exitted proc is--->%d\n",exit_procs[total_procs-1][0]);	
	sched();

}

void clear_queues(struct process *myproc)
{
	int i=0;//,first=0;
        struct waitlist  *temp = wait_list;
        int h;
        struct waitlist  *traverser;
	struct process *temp_cur_proc;
        exit_procs[total_procs][0] = myproc->id;
        exit_procs[total_procs][1] = -1;
        total_procs++;
        //myproc->state = ENV_KILLED;
        while(temp!=NULL)
        {
                for(i=0;i<total_procs;i++)
                {
                        if(temp->waiting_on == exit_procs[i][0]&&temp->proc->state!=ENV_KILLED)
                        {
                                temp->proc->state = ENV_RUNNABLE;
                                traverser = wait_list;
                                if(traverser == temp)
				{
                                        wait_list = temp->next;
					break;
				}
                                else
				{
                                	while(traverser->next!=temp)
                                        	traverser = traverser->next;
	                                traverser->next = temp->next;
					break;			
				}
                        }


                }
                temp = temp->next;

        }
	temp_cur_proc = cur_proc;
	cur_proc = myproc;
        for(h=0;h<100;h++)
        kclose(h);
	cur_proc = temp_cur_proc;
	myproc->status = 2;
        //kprintf("exitted proc is--->%d\n",exit_procs[total_procs-1][0]);      
//        sched();
}

void free_proc(struct process *myproc)
{
	
	/*temp = cur_proc->mm_struct;
        while(temp != NULL)
        {
                if(temp->vma_start<=address && temp->vma_end>=address)
                {
                        physaddr = katopa(page_alloc());
                        map_region(cur_proc->pml4e,address,physaddr,PGSIZE,USERPML4PERMISSION);
                }
                temp = temp->next;
        }*/

	uint64_t page_address;
/*	int i,j,k,l;
	pdpe_t *temp_pdpe;
	pgdir_t *temp_pgdir;
	pte_t *temp_pt,*pte;*/
//	struct process *myproc = cur_proc;
  //      struct process *new_proc = proc_create();
//        struct vma_area *temp_mem_struct;
        uint64_t va_end,va,va_index;
        uint64_t bit;
        //int i =0;
//        uint64_t * rax,*ptr;
//        struct Page *temp_page;
//        struct file_desc *traverser_file_desc;
//        struct file *temp_file;
//        int h;
        pte_t * temp_pte;
        struct vma_area *temp_mem_struct  = myproc->mm_struct;	
	loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
	 while(temp_mem_struct != NULL)
        {
                va = temp_mem_struct->vma_start;
                va_end = temp_mem_struct->vma_end;
                va = va - va%PGSIZE;
                if(va_end%4096 != 0)
                        va_end = (va_end + PGSIZE) - (va_end%PGSIZE);
                for(va_index = va ; va_index < va_end ; va_index = va_index+PGSIZE)
                {
                        temp_pte = (pte_t*)pml4e_walk(myproc->pml4e,va_index,0,USERPML4PERMISSION);
                        bit = (uint64_t)(*temp_pte) & PRESENT;
                        if(bit == 1)
                        {
				page_address = *temp_pte&0xFFFFFFFFFFFFF000;
	                        free_page(va_index,page_address);
                        }
                }
                temp_mem_struct = temp_mem_struct->next;
        }
	/*
	for(i=0;i<511;i++)
	{
		temp_pdpe = (pdpe_t*)(myproc->pml4e)+i;
		if(temp_pdpe!=NULL){
		if(*temp_pdpe&PRESENT)
		{
			for(j=0;j<=511;j++)
			{
				temp_pgdir = (pgdir_t*)(ptetoka(*temp_pdpe))+j;
				if(temp_pgdir!=NULL){
				if(*temp_pgdir&PRESENT)
				{
					for(k=0;k<=511;k++)
					{
						temp_pt = (pte_t*)(ptetoka(*temp_pgdir))+k;
						if(temp_pt!=NULL){
						if(*temp_pt&PRESENT)
						{
							for(l=0;l<=511;l++)
							{
								pte = (pte_t*)(ptetoka(*temp_pt))+l;
								if(pte!=NULL){
								if(*pte&PRESENT)
								{
									page_address = *pte&0xFFFFFFFFFFFFF000;
									free_page(0,page_address);
								}
								}
							}
							page_address = *temp_pt&0xFFFFFFFFFFFFF000;
							free_page(0,page_address);
						}
						}
						
					}
					page_address = *temp_pgdir&0xFFFFFFFFFFFFF000;
                                        free_page(0,page_address);
				}
				}
			}
			page_address = *temp_pdpe&0xFFFFFFFFFFFFF000;
                	free_page(0,page_address);
		}
		}
	}*/
/*	for(i=0;i<511;i++)
	{
		temp_pdpe = (pdpe_t*)(myproc->pml4e)+i;
                if(*temp_pdpe&PRESENT)
                {
			page_address = ptetoka(*temp_pdpe);
                        free_page(page_address);
		}
	}*/
	//free_page(0,(uint64_t)myproc->fd_page);	
	//free_page(0,(uint64_t)myproc->pml4e);
	//free_page(0,myproc->kstack-PGSIZE+8);
}
