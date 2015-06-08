#include<sys/kernlib.h>
#include<sys/sched.h>
#include<sys/sbunix.h>
void kkill(uint64_t pid)
{
	struct process *temp = head;
	do
	{
		if(temp->id==pid&&temp->state!=ENV_KILLED&&pid!=1&&pid!=3)
		{
			kprintf("%d\n",pid);
			kprintf("%s\n",temp->proc_name);
			temp->state = ENV_KILLED;
			break;
		}
		temp = temp->next;		
	}while(temp!=head);
	//sched();
}
