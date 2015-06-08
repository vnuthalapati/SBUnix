#include<sys/kernlib.h>
#include<sys/sbunix.h>
//#include<sys/proc.h>

void kfork()
{
	struct process *myproc = cur_proc;
	struct process *new_proc = proc_create(""); 
	struct vma_area *new_mm_struct;
        uint64_t va_end,va,va_index;
	uint64_t bit,offset1,offset2;
	//int i =0;
	uint64_t * rax,*ptr;
	struct Page *temp_page;
	struct file_desc *traverser_file_desc;
	struct file *temp_file;
	int h,i=0;
	pte_t * temp_pte,*new_temp_pte;
	struct vma_area *temp_mem_struct  = myproc->mm_struct;
	pml4e_t * mypml4e = (pml4e_t*)page_alloc();
       	new_proc->pml4e = mypml4e;
	while(myproc->cwd[i]!='\0'){
                new_proc->cwd[i]=myproc->cwd[i];
                i++;
        }
        new_proc->cwd[i]='\0';
	i=0;
	new_proc->pml4e[0x1ff] = myproc->pml4e[0x1ff];
	while(myproc->proc_name[i]!='\0'){
        new_proc->proc_name[i] = myproc->proc_name[i];
        i++;
        }
	new_proc->proc_name[i]='\0';
	
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
//				kprintf("%x\t%x",va_index,*temp_pte);
				if(*temp_pte&~READ)
				*temp_pte = (uint64_t)*temp_pte & READ;
				else
				*temp_pte = ((uint64_t)*temp_pte & READ)|COW;
				
	//			loadcr3(katopa(myproc->pml4e,0,0);
				loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
				temp_page =(struct Page*) (pages+(katopa(ptetoka(*temp_pte))/PGSIZE));
				temp_page->page_ref = temp_page->page_ref+1;
				
				new_temp_pte = (pte_t*)pml4e_walk(new_proc->pml4e,va_index,1,USERPML4PERMISSION);
				*new_temp_pte = *temp_pte;
				new_temp_pte = (pte_t*)pml4e_walk(new_proc->pml4e,va_index,0,USERPML4PERMISSION);
			//	kprintf("%x\t%x\n",va_index,*new_temp_pte);
			}
		}
		temp_mem_struct = temp_mem_struct->next;
	}
//	new_proc->pml4e[0x1ff] = myproc->pml4e[0x1ff];
	//physaddr = 
	new_proc->kstack = page_alloc()+PGSIZE-8;
//	for(i=0;i<15;i++);
//	page_alloc();
//	i = 0;
	map_region(new_proc->pml4e,new_proc->kstack-PGSIZE+8,katopa(new_proc->kstack-PGSIZE+8),PGSIZE,USERPML4PERMISSION);
	memcopy((char*)(myproc->kstack-PGSIZE+8),(char*)(new_proc->kstack-PGSIZE+8),4096);
	new_proc->fd_page = page_alloc();
	memcopy((char*)(myproc->fd_page),(char*)(new_proc->fd_page),4096);
	for(h=0;h<PGSIZE/sizeof(struct file_desc);h++)
	{
		traverser_file_desc = (struct file_desc*)new_proc->fd_page + h;
		if(traverser_file_desc->fd_no!=0 && traverser_file_desc->fd_no!=1 && traverser_file_desc->fd_no!=2 && traverser_file_desc->fd_no>0)
		{
			temp_file = (struct file*)traverser_file_desc->file_address;
			if(temp_file->type == 1)
			{
				if(traverser_file_desc->perm==0)
					temp_file->read_ref++;
				if(traverser_file_desc->perm==1)
					temp_file->write_ref++;
			}
			if(temp_file->type==0)
                        {
                                traverser_file_desc->offset = 0;
                        }
		}
	}
	new_proc->fd_count = myproc->fd_count;
//	new_proc->state = my;
	//cur_proc->tf.rsp = tf1->rsp-8;	
	new_proc->ustack = myproc->ustack;
	
	//map_region(new_proc->pml4e,USTACK-PGSIZE,physaddr,PGSIZE,USERPML4PERMISSION);	
//	new_proc->tf.rsp =  myproc->tf.rsp;
	{offset1 = (new_proc->kstack & STACKMASK1);
	offset2 = ((uint64_t)myproc->tf.rsp & STACKMASK2);
	new_proc->tf.rsp = offset1|offset2;
	ptr = (uint64_t*)(new_proc->tf.rsp);
	*ptr = (uint64_t)(ptr+1);
	//offset2 = ((uint64_t*)(myproc->tf.rsp) & STACKMASK2);
	//*new_proc->tf.rsp = (uint64_t)offset1+offset2;
	}
	 new_proc->tf.r15 =  myproc->tf.r15;
	 new_proc->tf.r14 =  myproc->tf.r14;
	 new_proc->tf.r13 =  myproc->tf.r13;
	 new_proc->tf.r12 =  myproc->tf.r12;
	 new_proc->tf.r11 =  myproc->tf.r11;
	 new_proc->tf.r10 =  myproc->tf.r10;
	 new_proc->tf.r9 =  myproc->tf.r9;
	 new_proc->tf.r8 =  myproc->tf.r8;
	 new_proc->tf.rsi =  myproc->tf.rsi;
	 new_proc->tf.rdi =  myproc->tf.rdi;
	 new_proc->tf.rbp =  myproc->tf.rbp;
	 new_proc->tf.rdx =  myproc->tf.rdx;
	 new_proc->tf.rcx =  myproc->tf.rcx;
	 new_proc->tf.rbx =  myproc->tf.rbx;
	 new_proc->tf.rax =  myproc->tf.rax;
	 new_proc->tf.rip =  myproc->tf.rip;
	 new_proc->tf.cs =  myproc->tf.cs;
	 new_proc->tf.eflags =  myproc->tf.eflags;
	 new_proc->tf.ursp =  myproc->tf.ursp;
	 new_proc->tf.ss =  myproc->tf.ss;
	temp_mem_struct =  myproc->mm_struct;

	while(temp_mem_struct != NULL){
		new_mm_struct = new_proc->mm_struct;
		if(new_mm_struct == NULL){
		struct vma_area *new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
		new->next = NULL;
		new->vma_start = temp_mem_struct->vma_start;
		new->vma_end = temp_mem_struct->vma_end;
		new_proc->mm_struct = new;
		}else{
			while(new_mm_struct->next!=NULL){
				new_mm_struct = new_mm_struct->next;
			}
			struct vma_area *new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
	                new->next = NULL;
        	        new->vma_start = temp_mem_struct->vma_start;
                	new->vma_end = temp_mem_struct->vma_end;
			new_mm_struct->next = new;
              	  //	new_mm_struct = new;
		}
		temp_mem_struct = temp_mem_struct->next;
	}
	rax = (uint64_t*)myproc->kstack;
	*(rax-8)=new_proc->id;
	rax = (uint64_t*)new_proc->kstack;
        *(rax-8)=0;
	new_proc->ppid = myproc->id;
//	return new_proc->id;

}
