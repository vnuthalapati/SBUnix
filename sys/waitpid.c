#include<sys/kernlib.h>
#include<sys/sched.h>
uint64_t kwaitpid(uint64_t pid, int *status, int options)
{
	//sleep_time = sleep_time/(4018143160);
        //sleep_time = sleep_time *10;
        cur_proc->state = ENV_PROC_WAIT;
        struct waitlist  *temp = wait_list;
//	struct waitlist *prev1 = wait_list;
	int i=0;
	struct waitlist *traverser;
	struct waitlist *new = (struct waitlist*)kmalloc(sizeof(struct waitlist));
	new->proc = cur_proc;
        new->waiting_on = pid;
        new->proc->state = ENV_PROC_WAIT;
        new->next = wait_list;
	wait_list = new;
	temp = wait_list;
	while(temp!=NULL)
	{
		for(i=0;i<total_procs;i++)
                {
                        if(temp->waiting_on == exit_procs[i][0])
                        {
                                temp->proc->state = ENV_RUNNABLE;
				traverser = wait_list;
				if(traverser == temp)
				{
					wait_list = temp->next;
					break;
				}
				else
				{
				while(traverser->next!=temp)
					traverser = traverser->next;
				traverser->next = temp->next;
				break;
				}
                        }


                }
                temp = temp->next;

        }
        sched();
	return 0;
}
