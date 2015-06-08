#include <sys/timer.h>
#include <sys/sbunix.h>
//#include <sys/proc.h>
#include <sys/sched.h>
#include <sys/kernlib.h>
//#include <sys/interrupt.h>
//extern uint64_t final_rsp;
//static int counter=0;
int sta=1;
static inline void outb(uint16_t port, uint8_t val)
{
__asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

//inline void outportb(unsigned int port,unsigned char value)
//{
//__asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value):"cc","memory");
//}
void timerprinter();
void writetimer();
volatile char *v = (volatile char*)0xFFFFFFFF800B8F96;
static void outportb(int port, uint8_t data)
{
__asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}

void timer_init(){
	//uint64_t wait = 0;i
	uint64_t dup_freq_div = freq_div;
	uint8_t lo = (uint8_t)(dup_freq_div & 0xFF);
	uint8_t hi = (uint8_t)((dup_freq_div>>8) & 0xFF);
	outportb(0x43,0x36);
	//while(wait<184444444)
	//wait++;
	//wait = 0;
	//printf("after 1\n");
	outportb(0x40,lo);
	//while(wait<184444444)
        //wait++;
        //wait = 0;
	//printf("after 2\n");
	outportb(0x40,hi);
	//printf("after 3\n");
	//while(wait<184444444)
        //wait++;
        //wait = 0;
//	return 1;
}

extern void timer_handler(struct trap_frame *tf1){
	//printf("in the handler");
//	uint64_t final_rsp;
	//int curid=0,value=0,i=0;
	total_time++;
	outb(0x20,0x20);
//	char *ptr = (char*)0xFFFFFFFF80002000;
//	char *ptr2 = (char*)0xFFFFFFFF80003000;
	//cur_proc = procs;
//	final_rsp = cur_proc->tf.rsp;
	//if(total_time%18 == 0)
	{
//	counter++;
	/*	if(sta == 1){
			sta = sta*-1;
			cur_proc = procs;
		}else {
			cur_proc = procs +1;
			sta=sta*-1;
		}*/
		
		cur_proc->tf.rsp = tf1->rsp-8;
	//	final_rsp = cur_proc->tf.rsp;
                cur_proc->tf.r15 = tf1->r15;
                cur_proc->tf.r14 = tf1->r14;
                cur_proc->tf.r13 = tf1->r13;
                cur_proc->tf.r12 = tf1->r12;
                cur_proc->tf.r11 = tf1->r11;
                cur_proc->tf.r10 = tf1->r10;
                cur_proc->tf.r9 = tf1->r9;
                cur_proc->tf.r8 = tf1->r8;
                cur_proc->tf.rsi = tf1->rsi;
                cur_proc->tf.rdi = tf1->rdi;
                cur_proc->tf.rbp = tf1->rbp;
                cur_proc->tf.rdx = tf1->rdx;
                cur_proc->tf.rcx = tf1->rcx;
                cur_proc->tf.rbx = tf1->rbx;
                cur_proc->tf.rax = tf1->rax;
                cur_proc->tf.rip = tf1->rip;
                cur_proc->tf.cs = tf1->cs;
                cur_proc->tf.eflags = tf1->eflags;
                cur_proc->tf.ursp = tf1->ursp;
                cur_proc->tf.ss = tf1->ss;
		//tf1->rax = 0;
	//	__asm volatile("movq %0,%%rsp"::"r"(kern_rsp):"memory","cc","%rsp");
	/*	if(sta == 1){
                      sta = sta*-1;
                     cur_proc = procs;
//			kprintf("%s\n",ptr);
        	   }else {
                        cur_proc = procs+1;
                        sta=sta*-1;
//			kprintf("%s\n",ptr2);
                }*/
		/*
		curid = cur_proc->id;
		for(i = 0;i<3;i++){
			
			if(totalprocs[i]->id > curid && totalprocs[i]->state == ENV_RUNNABLE){
			cur_proc->state = ENV_RUNNABLE;
			cur_proc = totalprocs[i];
			value = 1;
			break;
		}}
		if(value!=1){
			for(i = 0;i<3;i++){

                        if(totalprocs[i]->state == ENV_RUNNABLE){
			cur_proc->state = ENV_RUNNABLE;
                        cur_proc = totalprocs[i];
                        value = 1;
                        break;
                }
		}		
		}*/
//		awaken();
		if(total_time%18==0){
		counter++;
		timerprinter();}
//		sched();}
//		printf("%s\n",ptr);
		awaken();	
		sched();
	//	final_rsp = cur_proc->tf.rsp;
		//timerprinter();
	//	if(final_rsp)
	//	timerprinter();
		//a  = 1;
	//	__asm volatile("movq %0,%%rsp"::"r"(cur_proc->tf.rsp):"memory","cc","%rsp");
	}
	//printf("tf.rsp--->%x\r",tf1.rsp);
//	sched();	
//	return 0;
}

void timerprinter()
{
	int rem,len,xi,i,n;
	char A[1024],*temp;
//	int *ptr_counter = (int*);
//	counter = *ptr_counter;
	rem = 0;
        len = 0;
	xi = counter;
        n = counter;
        if(n!=0)
        {
		while (n != 0)
                {
	                len++;
     	                n /= 10;
                }
        }
	else
        {
                len=1;
        }
        for (i = 0; i < len; i++)
        {
        	rem = xi% 10;
               	xi = xi / 10;
               	A[len - (i + 1)] = rem + '0';
        }
        A[len]='\0';
        temp = A;
	v = (volatile char*)0xFFFFFFFF800B8F8C;
        while(*temp!='\0')
        {
  		writetimer(temp);
                temp++;
    	}

}

void writetimer(char *add)
{
        *v = *(char*)add;
        *(v+1) = 0x8C;
	v+=2;
}
