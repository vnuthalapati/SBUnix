#include<sys/kernlib.h>
#include<sys/sched.h>
#include<sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/operations.h>

int kdup(uint64_t oldfd)
{
		struct process *myproc = cur_proc;
                struct file_desc *temp_desc = (struct file_desc*)myproc->fd_page+oldfd;
                struct file *temp = (struct file*)temp_desc->file_address;
                int perms = temp_desc->perm;
//                kclose(newfd);
                temp_desc->fd_no = -1;
		myproc->fd_count++;
                temp_desc = (struct file_desc*)myproc->fd_page+myproc->fd_count;
                if((temp->type==0||temp->type==2) && perms==1)
                        return -1;
                temp_desc->fd_no = oldfd;
                temp_desc->perm = perms;
                temp_desc->file_address = (uint64_t)temp;
		return myproc->fd_count;
}
