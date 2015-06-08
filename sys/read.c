#include<sys/kernlib.h>
#include<sys/sched.h>
#include<sys/sbunix.h>
#include <sys/gdt.h>
#include <sys/operations.h>
//#include<sys/file.h>
int kread(int fd,uint64_t add,uint64_t num)
{
	int count=0,new_fd;
	struct file_desc *check_desc = (struct file_desc*)cur_proc->fd_page;
	new_fd = fd;
	if(fd>=0){
		fd = (check_desc+fd)->fd_no;
		if(fd==0&&cur_proc->position!=1){	
			cur_proc->state = ENV_WAIT;
			struct readlist *temp = read_wait_list;
			if(temp == NULL){
				struct readlist *new = (struct readlist*)kmalloc(sizeof(struct readlist));
				new->proc = cur_proc; 
				new->requested_bytes = num;
				new->buf = add;
				new->next = NULL;
				temp = new;
				read_wait_list=new;
			}
			else{
	/*	while(temp->next!=NULL){ 
			temp = temp->next;*/
			cur_proc->state=ENV_KILLED;
			sched();
	//	}
/*	struct readlist *new = (struct readlist*)kmalloc(sizeof(struct readlist));
        new->proc = cur_proc; 
        new->requested_bytes = num;
	new->buf  = add;
	new->next = NULL;*/
	//temp->next = new;
			}
			sched();
	//return 0;
		}
	//	if(fd<0)
	//		return 0;
		if(fd!=0 && fd!=1 && fd!=2)
		{	
			int x=0;
			struct file_desc *temp = ((struct file_desc*)(cur_proc->fd_page));
			struct file * temp_file;
			char *read_start,*buf = (char*)add;
			/*while(fd!=temp->fd_no)
			{
				temp++;
			}*/
			temp = temp + new_fd;
			temp_file = (struct file*)temp->file_address;
			if(temp_file->type == 0&&temp->perm == 0)
			{
				read_start = (char*)(temp_file->start_address) + temp->offset;
				x = 0;
				while(*read_start!='\0' && x<num)
				{
					*buf = *read_start;
				//	kprintf("%c",*read_start);
					buf++;
					read_start++;
					x++;
					temp->offset++;
				}
				//if(x>0)
				//x;
				return x;
				
				
			}
			else if(temp_file->type == 1&&temp->perm==0)
			{
				struct pipereadlist * temp_prl = (struct pipereadlist*)(kmalloc(sizeof(struct pipereadlist)));
				struct process *myproc = cur_proc;
				temp_prl->proc = myproc;
				temp_prl->wait_fdes = fd;
				temp_prl->requested_bytes = num;
				temp_prl->copy_address = add;
				temp_prl->next = NULL;
				insert_to_read(temp_prl);
				count = traverse_read_list();
				//kprintf("count1 value is %d\n",count);
				traverse_write_list();
				//count=traverse_read_list();
			//	kprintf("count2 value is %d\n",count);
				if(myproc->state == ENV_RUNNABLE)
				{
					return count;//change to return the number of raed
				}
				else
				{
					sched();
				}
			}
			else 
				return -1;
		}
	}
	else 
		return 0;
	//sched();
	return count;

}
void input(char c)
{
	int i = 0;
	struct readlist *temp = read_wait_list;
	struct process *myproc,*temp_cur_proc;
	if(temp!=NULL)
	{
		if(c!='\b'){	
		standardin[curr_pos] = c;
	        curr_pos++;
		if(temp->proc!=NULL)
		{
			if(temp->requested_bytes==curr_pos||c=='\n')
			{
				myproc =(struct process*) temp->proc;
				loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
				temp_cur_proc = cur_proc;
				cur_proc = myproc;
				while(i<curr_pos && standardin[i]!='\n')
				{
					*((char*)(temp->buf)+i) = standardin[i];
					standardin[i] = '\n';
					i++;
				}
				*((char*)(temp->buf)+i)='\n';
				cur_proc = temp_cur_proc;
				i=0;
				loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
				read_wait_list = temp->next;
				myproc->state = ENV_RUNNABLE;
				temp->proc=NULL;
				curr_pos = 0;

			}
		}
		}
		else if(c=='\b')
		{
		if(curr_pos>0)
		curr_pos--;
		else
		curr_pos =0;
		standardin[curr_pos] = '\0';
		}
		
	}
	else if(temp==NULL)
	{
		if(c!='\b'){
                standardin[curr_pos] = c;
                curr_pos++;}
		else if(c=='\b')
                {
                if(curr_pos>0)
                curr_pos--;
                else
                curr_pos =0;
                standardin[curr_pos] = '\0';
                }
	}
}
