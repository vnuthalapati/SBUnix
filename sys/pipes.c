#include<sys/kernlib.h>
int kpipe(int *filedes)
{
//	myproc->fd_count++;
	struct process * myproc = cur_proc;
        struct file *temp = (struct file*)kmalloc(sizeof(struct file));
    //    struct file *prev_file;
        struct file_desc * temp_desc;
        myproc->fd_count++;
        temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
        temp_desc->file_address = (uint64_t)temp;
        temp_desc->offset = 0;
        temp_desc->perm = 0;
        temp_desc->fd_no = myproc->fd_count;
	filedes[0] = temp_desc->fd_no;
	myproc->fd_count++;
        temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
        temp_desc->file_address = (uint64_t)temp;
        temp_desc->offset = 0;
        temp_desc->perm = 1;
        temp_desc->fd_no = myproc->fd_count;
	temp->offset = 0;
	temp->start_address = page_alloc();
	temp->type = 1;
	temp->read_ref++;
	temp->write_ref++;
	filedes[1] = temp_desc->fd_no;
        return 0;//change this appropriately
} 
