#include<sys/kernlib.h>
#include<sys/timer.h>
#include<sys/sched.h>
void ksleep(uint64_t sleep_time)
{
//	sleep_time = sleep_time;
//	sleep_time = sleep_time *10;
	cur_proc->state = ENV_SLEEP;
        struct sleeplist  *temp = sleep_list;
        if(temp == NULL){
        struct sleeplist *new = (struct sleeplist*)kmalloc(sizeof(struct sleeplist));
        new->proc = cur_proc;
        new->requested_sleep_time = sleep_time;
      	new->timecount = counter;
	new->proc->state = ENV_SLEEP;
        new->next = NULL;
        temp = new;
        sleep_list=new;
        }else{
        while(temp->next!=NULL){
                temp = temp->next;
        }
        struct sleeplist *new = (struct sleeplist*)kmalloc(sizeof(struct sleeplist));
        new->proc = cur_proc;
        new->requested_sleep_time = sleep_time;
       // new->buf  = add;
	new->proc->state = ENV_SLEEP;
	new->timecount = counter;
        new->next = NULL;
        temp->next = new;
        }
        sched();	
}

void awaken()
{
	struct sleeplist *temp = sleep_list;
	if(temp !=NULL){
		while(temp!=NULL){
			if(temp->proc !=NULL){
			if(counter - temp->timecount >= temp->requested_sleep_time){
				temp->proc->state = ENV_RUNNABLE;
				temp->requested_sleep_time = 0;
				temp->proc = NULL;

			}
			}
			temp = temp->next;
		}
	}		
}
