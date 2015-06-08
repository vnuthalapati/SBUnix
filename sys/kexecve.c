#include<sys/kernlib.h>
#include<sys/sbunix.h>
#include<sys/sched.h>
#include<sys/string.h>
int kexecve(const char *filename, char *const argv[], char *const envp[])
{	
	char *finame = (char*)filename;
	//kprintf("finame is %s\n",finame);
	int i=0;
	struct process * myproc = process_setup_exec(0,0,finame);
	if(myproc!=NULL)
	{	
	uint64_t temp_page = page_alloc();
	char * char_dest = (char*)temp_page;
	uint64_t * int_dest = (uint64_t*)temp_page;
	uint64_t load_address,end_load_address,start_load_address;
	int no_args=0;
	int j=0,no_envp=0;
	char *temp;//*test_char;
	loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
	myproc->id = cur_proc->id;
	cur_proc->id = -1;
/*	while(j<50)
		myproc->proc_name[j++]='\0';
	j = 0;*/
	//stringcpy(myproc->proc_name,argv[0]);
	/*while(argv[0][j]!='\0')
	{
		myproc->proc_name[j] = argv[0][j];
		j++;
	}
	myproc->proc_name[j]='\0';*/
	j = 0;
	
	while(argv[i]!=NULL)
        {
                i++;
        }
	//myproc->id = cur_proc->id;
	if(argv[i-1][0]=='&')
	{	
		struct waitlist  *temp = wait_list;
        	struct waitlist  *traverser;
//		kprintf("entered\n");
		myproc->position = 1;
		 while(temp!=NULL)
        	{
                for(i=0;i<total_procs;i++)
                {
                        if(temp->waiting_on == myproc->id)
                        {
                                temp->proc->state = ENV_RUNNABLE;
                                traverser = wait_list;
                                if(traverser == temp){
                                        wait_list = temp->next;
					break;
				}
                                else{
                                while(traverser->next!=temp)
                                        traverser = traverser->next;
                                traverser->next = temp->next;
				break;
				}
                        }
                }
                temp = temp->next;
        	}
	}

	else
	{
		myproc->position = cur_proc->position;
	}
	i=0;
	while(cur_proc->cwd[i]!='\0'){
                myproc->cwd[i]=cur_proc->cwd[i];
                i++;
        }
        myproc->cwd[i]='\0';
	i=0;
	while(argv[i]!=NULL)
	{
	no_args++;
	//kprintf("%s\n",argv[i]);
	i++;
	
	}
	while(envp[j]!=NULL)
	{
	no_envp++;
	j++;
	}
//	kprintf("no of args is--->%d\n",no_args);
	//while(1);
	*int_dest = no_args;
	int_dest++;
	char_dest = (char*)((uint64_t)int_dest);
	i=0;
	while(argv[i]!=NULL)
	{
		temp = (char*)argv[i];
		while(*temp!='\0')
		{
			*char_dest = *temp;
			char_dest++;
			temp++;
		}
		//char_dest++;
		*char_dest = '\0';
		char_dest++;
		i++;
	}
	*char_dest = '\0';
	char_dest++;
	j=0;
	while(envp[j]!=NULL)
	{
		temp = (char*)envp[j];
                while(*temp!='\0')
                {
                        *char_dest = *temp;
                        char_dest++;
                        temp++;
                }
                //char_dest++;
                *char_dest = '\0';
                char_dest++;
                j++;
	}
	
	loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
	memcopy((char*)temp_page,(char*)((char*)myproc->ustack-(char_dest-(char*)temp_page)-56),(uint64_t)(char_dest-(char*)temp_page));
	load_address = (uint64_t)((char*)myproc->ustack-(char_dest-(char*)temp_page)-56);
	temp = (char*)((uint64_t)load_address+8);
	end_load_address = load_address - 8;
	start_load_address = end_load_address - 32 - no_args*8 - no_envp*8;
	start_load_address = start_load_address-start_load_address%8;
	int_dest = (uint64_t*)start_load_address;
	
	myproc->ustack = start_load_address;
	*int_dest = (uint64_t)no_args;
	int_dest = int_dest+1;
	temp = (char*)((uint64_t)load_address+8);
	for(i=0;i<no_args+no_envp+1;i++){
//        kprintf("no of args is--->%s\n",temp);
	*int_dest = (uint64_t)temp;
	int_dest++;
        while(*temp !='\0'){
        temp++;
        }
        temp++;
        }
	setup_stack(myproc); 
//	myproc->id = cur_proc->id;
	memcopy((char*)cur_proc->fd_page,(char*)myproc->fd_page,PGSIZE);
	cur_proc->state = ENV_KILLED;
	sched();
	return 0;
	}
	else 
		return -1;
//	return 0;	
}
//struct process* process_setup(uint64_t physbase,uint64_t physfree,int number)
