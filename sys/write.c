#include<sys/kernlib.h>
#include<sys/sbunix.h>
#include<sys/sched.h>
size_t kwrite(int fd,uint64_t add, size_t num)
{
	struct file_desc *check_desc = (struct file_desc*)cur_proc->fd_page;
	int new_fd = fd;
        fd = (check_desc+fd)->fd_no;
	if(fd==1)
	{
		int x=0;
		while(x<num){
		writedisp(1, (const char*)add+x, num);	
		x++;
		}
		return x;
	}
	if(fd!=0 && fd!=1 && fd!=2)
        {
       //         int x=0;
                struct file_desc *temp = ((struct file_desc*)(cur_proc->fd_page));
                struct file * temp_file;
         //       char *read_start,*buf = (char*)add;
                /*while(fd!=temp->fd_no)
                {
                        temp++;
                }*/
		temp = temp+new_fd;
                temp_file = (struct file*)temp->file_address;
                if(temp_file->type == 0)
                {
			return -1;//failed to write
                }
                if(temp_file->type == 1 && temp->perm==1)
                {
                        struct pipewritelist * temp_pwl = (struct pipewritelist*)(kmalloc(sizeof(struct pipewritelist)));
                        struct process *myproc = cur_proc;
                        temp_pwl->proc = myproc;
                        temp_pwl->wait_fdes = fd;
                        temp_pwl->requested_bytes = num;
			temp_pwl->const_requested_bytes = num;
                        temp_pwl->copy_address = add;
                        temp_pwl->next = NULL;
                        insert_to_write(temp_pwl);
                        traverse_write_list();
                        traverse_read_list();
			traverse_write_list();
			if(myproc->state == ENV_RUNNABLE)
                        {
                                return 0;//change to return the number of bytes written
                        }
                        else
                        {
                                sched();
                        }
		}
		else 
			return -1;
	}
	return 0;
}
