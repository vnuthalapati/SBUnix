#include<sys/kernlib.h>
#include<sys/sched.h>
#include<sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/operations.h>
//#include <sys/file.h>
void insert_to_read(struct pipereadlist *temp_prl)
{
	temp_prl->proc->state = ENV_PIPE_READ;
	temp_prl->next = pipe_read_list;
	pipe_read_list = temp_prl; 
}

void insert_to_write(struct pipewritelist *temp_pwl)
{
	temp_pwl->proc->state = ENV_PIPE_WRITE;
	temp_pwl->next = pipe_write_list;
	pipe_write_list = temp_pwl;
}

int traverse_read_list()
{
	struct pipereadlist *traverser,*temp = pipe_read_list;
	struct file *temp_file;
	struct file_desc *temp_desc;
	struct process *myproc,*temp_proc = cur_proc,*temp_cur_proc;
	char * to,*from;
	uint64_t count=0;
	uint64_t temp_page,*rax;
	while(temp!=NULL)
	{
		myproc = temp->proc;
		temp_desc = (struct file_desc*)(myproc->fd_page)+temp->wait_fdes;
		temp_file = (struct file*)(temp_desc->file_address);
		if(temp_file->offset>0)
		{
			loadcr3(katopa((uint64_t)(myproc->pml4e)),0,0);
			count = 0;
			to = (char*)(temp->copy_address);
			from = (char*)temp_file->start_address;
			temp_cur_proc = cur_proc;
                        cur_proc = myproc;
			while(count<temp_file->offset && count<temp->requested_bytes)
			{	
			//	if(*from == '\0'){
			//	break;
			//	}
				*to = *from;
				to++;
				from++;
				count++;
				
			}
			cur_proc = temp_cur_proc;
			//kprintf("count value is %d\n",count);
			temp->copy_address = (uint64_t)to;
			
			myproc->state = ENV_RUNNABLE;
			rax = (uint64_t*)myproc->kstack;
			rax = rax-8;
			*rax = count;
			temp_page = page_alloc();
			memcopy((char*)temp_file->start_address+count,(char*)temp_page,PGSIZE-count);
			memset((uint64_t)temp_file->start_address,PGSIZE,'\0');
			memcopy((char*)temp_page,(char*)temp_file->start_address,PGSIZE);
			temp_file->offset = temp_file->offset-count;
			//delete temp node form the list
			traverser = pipe_read_list;
			if(traverser == temp)
				pipe_read_list = pipe_read_list->next;
			else{
				while(traverser->next != temp)
					traverser = traverser->next;
				traverser->next = temp->next;
			}
			
		}
		else
		{
			check_read_queue();
		}
		loadcr3(katopa((uint64_t)(temp_proc->pml4e)),0,0);
		temp = temp->next;
	}
//kprintf("traverse read count %d\n",count);
return count;
}

void traverse_write_list()
{
	
	struct pipewritelist *traverser,*temp = pipe_write_list;
        struct file *temp_file;
        struct file_desc *temp_desc;
        struct process *myproc,*temp_proc = cur_proc;
        char * to,*from;
        uint64_t count;
        //uint64_t temp_page;
        while(temp!=NULL)
        {
                myproc = temp->proc;
                temp_desc = (struct file_desc*)(myproc->fd_page)+temp->wait_fdes;
                temp_file = (struct file*)(temp_desc->file_address);
                if(temp_file->offset<PGSIZE && temp->requested_bytes>0)
                {
                        loadcr3(katopa((uint64_t)(myproc->pml4e)),0,0);
                        count = 0;
                        from = (char*)(temp->copy_address);
                        to = (char*)(temp_file->start_address)+temp_file->offset;
                        while(count<PGSIZE-temp_file->offset && count<temp->requested_bytes)
                        {
                                *to = *from;
                                to++;
                                from++;
                                count++;

                        }
                        temp->copy_address = (uint64_t)to;
             //           myproc->state = ENV_RUNNABLE;
//                        memcopy(temp_file->start_address+count,temp_page,PGSIZE-count);
//                        memset(temp_file->start,'\0',PGSIZE);
//                        memcopy(temp_page,temp_file->start_address);
                        temp_file->offset = temp_file->offset+count;
			temp->requested_bytes = temp->requested_bytes-count;
			if(temp->requested_bytes == 0)
			{
				myproc->state = ENV_RUNNABLE;
				traverser = pipe_write_list;
                       		if(traverser == temp)
                                	pipe_write_list = pipe_write_list->next;
                        	else
				{
                                	while(traverser->next != temp)
                                        	traverser = traverser->next;
                                	traverser->next = temp->next;
                        	}
			}

                }
		else
		{
			//check_write_queue();//see if any problem arises
		}
                loadcr3(katopa((uint64_t)(temp_proc->pml4e)),0,0);
                temp = temp->next;
        }
}
