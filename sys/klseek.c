#include<sys/kernlib.h>
#include<sys/sbunix.h>
#include<sys/tarfshandling.h>
#include<sys/string.h>
uint64_t klseek(int fildes, uint64_t offset, int whence)
{
	struct file_desc *temp_desc = (struct file_desc*)cur_proc->fd_page + fildes;
	struct file * temp_file = (struct file*)temp_desc->file_address;
	if(whence == 0)
	{
		if(temp_file->type == 0)
		{
			temp_desc->offset = offset;	
		}
	}
	if(whence == 1)
	{
		if(temp_file->type == 0)
		{
			temp_desc->offset = temp_desc->offset+offset;
		}
	}
	return temp_desc->offset;
}
