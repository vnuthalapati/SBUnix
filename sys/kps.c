#include <sys/pmap.h>
#include <sys/tarfs.h>
#include <sys/sbunix.h>
#include <sys/tarfshandling.h>
#include <sys/kernlib.h>
#include <sys/string.h>
void kps()
{
	struct process *temp = head;
//	int first = 1;
	kprintf("PID\tCMD\n");
	
	do
	{
		if(temp->state == ENV_RUNNABLE||temp->state==ENV_RUNNING||temp->state==ENV_SLEEP||temp->state == ENV_WAIT||temp->state == ENV_PROC_WAIT||temp->state == ENV_PIPE_READ||temp->state == ENV_PIPE_WRITE)
		{
//			if(strngcmp(temp->proc_name,"bin/sbush") && strngcmp(temp->proc_name,"bin/pragathi"))
			kprintf("%d\t%s\n",temp->id,temp->proc_name);
		}
		temp = temp->next;
//		if(temp==head)
//		first = 0;
	}while(temp!=head);
//	kprintf("\n");
	//return 0;
}
