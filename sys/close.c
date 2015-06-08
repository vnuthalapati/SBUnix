#include<sys/kernlib.h>
#include<sys/sched.h>
#include<sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/operations.h>
int kclose(int fd)
{
	struct process *myproc = cur_proc;
	struct file_desc * temp_desc;
	struct file *temp_file;
//	struct pipereadlist *temp_prl;
//	struct pipewritelist *temp_pwl;
	temp_desc = (struct file_desc*)myproc->fd_page+fd;
	if(temp_desc->fd_no!=0 && temp_desc->fd_no!=1 && temp_desc->fd_no!=2 && temp_desc->fd_no>0 && myproc->id>0)
	{
		temp_desc->fd_no = -1;
		temp_file = (struct file*)temp_desc->file_address;
		if(temp_file->type ==1)
		{
			if(temp_desc->perm==0)
				temp_file->read_ref--;
			if(temp_desc->perm==1)
				temp_file->write_ref--;
			if(temp_file->read_ref==0 && temp_file->write_ref!=0)
			{
				//check in the write queue
				check_write_queue();
				
			}
			if(temp_file->write_ref==0 && temp_file->read_ref!=0)
			{
				//check in the read queue
				check_read_queue();
			}
			return 0;
		}
		if(temp_file->type ==0)
		{
			temp_desc->fd_no = -1;
			temp_desc->offset = 0;
		}
		/*if(temp_file->type==2)
		{
			
		}*/
		return 0;
	}
	else
		return -1;
}

int silent_close(int fd)
{
        struct process *myproc = cur_proc;
        struct file_desc * temp_desc;
        struct file *temp_file;
//      struct pipereadlist *temp_prl;
//      struct pipewritelist *temp_pwl;
        temp_desc = (struct file_desc*)myproc->fd_page+fd;
        if(temp_desc->fd_no!=0 && temp_desc->fd_no!=1 && temp_desc->fd_no!=2 && temp_desc->fd_no>0)
        {
                temp_desc->fd_no = -1;
                temp_file = (struct file*)temp_desc->file_address;
                if(temp_file->type ==1)
                {
                        if(temp_desc->perm==0)
                                temp_file->read_ref--;
                        if(temp_desc->perm==1)
                                temp_file->write_ref--;
                        if(temp_file->read_ref==0 && temp_file->write_ref!=0)
                        {
                                //check in the write queue
                                check_write_queue();

                        }
                        if(temp_file->write_ref==0 && temp_file->read_ref!=0)
                        {
                                //check in the read queue
                                check_read_queue();
                        }
                        return 0;
                }
                return 0;
        }
        else
                return -1;
}

void check_read_queue()
{
	struct pipereadlist *traverser,*temp = pipe_read_list;
	struct file_desc *temp_desc;
	struct file *temp_file;
	struct process *myproc;
	uint64_t *rax;
	while(temp!=NULL)
        {
                myproc = temp->proc;
                temp_desc = (struct file_desc*)(myproc->fd_page)+temp->wait_fdes;
                temp_file = (struct file*)(temp_desc->file_address);
		if(temp_file->read_ref!=0 && temp_file->write_ref==0)
		{
			myproc->state = ENV_RUNNABLE;
			rax = (uint64_t*)myproc->kstack;
                        rax = rax-8;
                        *rax = 0;
			traverser = pipe_read_list;
                        if(traverser == temp)
			{
                                pipe_read_list = pipe_read_list->next;
//				break;
			}
                        else{
                                while(traverser->next != temp)
                                        traverser = traverser->next;
                                traverser->next = temp->next;
//				break;
                        }
		}
	temp = temp->next;
	}
}

void check_write_queue()
{
	struct pipewritelist *traverser,*temp = pipe_write_list;
        struct file_desc *temp_desc;
        struct file *temp_file;
        struct process *myproc;
        uint64_t *rax;
        while(temp!=NULL)
        {
                myproc = temp->proc;
                temp_desc = (struct file_desc*)(myproc->fd_page)+temp->wait_fdes;
                temp_file = (struct file*)(temp_desc->file_address);
                if(temp_file->write_ref!=0 && temp_file->read_ref==0)
                {
                        myproc->state = ENV_RUNNABLE;
                        rax = (uint64_t*)myproc->kstack;
                        rax = rax-8;
                        *rax = temp->const_requested_bytes-temp->requested_bytes;
                        traverser = pipe_write_list;
                        if(traverser == temp)
                                pipe_write_list = pipe_write_list->next;
                        else{
                                while(traverser->next != temp)
                                        traverser = traverser->next;
                                traverser->next = temp->next;
                        }
                }
        temp = temp->next;
        }
}
