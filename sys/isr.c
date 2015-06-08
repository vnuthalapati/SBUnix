#include<sys/sbunix.h>
#include<sys/defs.h>
#include<sys/kernlib.h>
#include<sys/gdt.h>
#include<sys/sched.h>
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr128();
extern void common_handler()
{
//	uint64_t address;
	kprintf("Segmentation Fault\n");
//	__asm volatile("movq %%cr2,%0":"=r"(address)::"cc","memory");
//	kprintf("fault at--->%x\n",address);
	cur_proc->state = ENV_KILLED;
        sched();
	//reset_os();
	while(1);
	
}
extern void trap_handler(struct trap_frame *tf1) {
//	int writedisp(int fd, const char* add, int size);	
	//uint64_t address=tf1->rax;
	//kprintf("rax is--->%d\n",address);
	if(tf1->rax==1)
	{	
	/*	int fd,count;
		fd = tf1->rdi;
		count = tf1->rdx;
		char *buf = (char *)tf1->rsi;
		cur_proc->tf.rsp = tf1->rsp-8;
                //tss.rsp0 = exception_stack;
                if(tf1->rdi == 1){
        //      char *buf = (char *)tf1->rsi;
                tf1->rax=writedisp(1, buf, 1);
                }else{
                tf1->rax = kwrite(fd,(uint64_t)buf,count);
                }
                //tss.rsp0 = cur_proc->kstack;*/
		int fd,count;
                fd = tf1->rdi;
                count = tf1->rdx;
                char *buf = (char *)tf1->rsi;
        //      if(tf1->rdi == 1){
        //      char *buf = (char *)tf1->rsi;
        //      tf1->rax=writedisp(1, buf, 1);
        //      }else{
		tss.rsp0 = exception_stack;
                tf1->rax = kwrite(fd,(uint64_t)buf,count);
		tss.rsp0 = cur_proc->kstack;
	
	}
	else if(tf1->rax==3)
	{
		tf1->rax = kclose(tf1->rdi);
	}
	else if(tf1->rax==42)
        {
                kps();
        }
	else if(tf1->rax == 12)
	{
		tf1->rax = kbreak(tf1->rdi);
	}
	else if(tf1->rax == 33)
        {
                tf1->rax = kdup2(tf1->rdi,tf1->rsi);
        }
	else if(tf1->rax == 57)
	{
		cur_proc->tf.rsp = tf1->rsp-8;
		kfork();
	}
	else if(tf1->rax == 0)
	{	
		/*cur_proc->tf.rsp = tf1->rsp-8;
		int a = tf1->rdi;
		uint64_t val = tf1->rdx;
		uint64_t add = tf1->rsi;
		//      tss.rsp0 = exception_stack;
                tf1->rax = kread(a,add,val);
		*/
		cur_proc->tf.rsp = tf1->rsp-8;
                int a = tf1->rdi;
                uint64_t val = tf1->rdx;
                uint64_t add = tf1->rsi;
		tss.rsp0 = exception_stack;
                tf1->rax = kread(a,add,val);
              	tss.rsp0 = cur_proc->kstack;

	}
	else if(tf1->rax == 35)
	{
		cur_proc->tf.rsp = tf1->rsp-8;
		uint64_t time = tf1->rsi;
		ksleep(time);

	}
	else if(tf1->rax == 60)
        {
                cur_proc->tf.rsp = tf1->rsp-8;
                uint64_t num = tf1->rdi;
                kexit(num);

        }
	else if(tf1->rax == 61)
        {
                cur_proc->tf.rsp = tf1->rsp-8;
                uint64_t pid = tf1->rdi;
		int dummy;
                kwaitpid(pid,&dummy,0);

        }
	else if(tf1->rax == 39)
	{
		uint64_t pid;
		pid=kpid();
		tf1->rax = pid; 
//		__asm volatile("movq %0,%%rax"::"r"(pid):"cc","memory");

	}
	else if(tf1->rax == 110)
        {
                uint64_t ppid;
                ppid=kppid();
                tf1->rax = ppid;
//                __asm volatile("movq %0,%%rax"::"r"(ppid):"cc","memory");

        }
	else if(tf1->rax == 59)
        {
        //        uint64_t ppid;
          //      ppid=kppid();
		char **argc;
		char **envs;
		char *fname = (char*)(tf1->rdi);
                tf1->rax = 0;
		cur_proc->tf.rsp = tf1->rsp-8;
		argc = (char**)tf1->rsi;
		envs = (char**)tf1->rdx;
		kexecve(fname,argc,envs);
		tf1->rax = -1;
  //              __asm volatile("movq %0,%%rax"::"r"(ppid):"cc","memory");

        }
	else if(tf1->rax == 2)
	{	
		const char *pathname = (char*)tf1->rdi;
		int flags = (int)tf1->rsi;
		tf1->rax = kopen(pathname,flags);
		

	}
	 else if(tf1->rax == 43)
        {
//		cur_proc->tf.rsp = tf1->rsp-8;

                uint64_t pid = tf1->rdi;
//                int flags = (int)tf1->rsi;
                kkill(pid);


        }

	else if(tf1->rax == 22)
	{
		int *fds;
		fds = (int*)tf1->rdi;
		tf1->rax = kpipe(fds);
//		kprintf("file ids  are %d\n",fds[0]);
//		kprintf("file ids  are %d\n",fds[1]);


	}
	 else if(tf1->rax == 78)
        {

                int fd=(int)tf1->rdi;
                uint64_t temp=(uint64_t)tf1->rsi;
        //      kprintf("user address in isr before %x\n",temp);
                int count = (int)tf1->rdx;
                tf1->rax = kgetdents(fd,temp,count);
        //      kprintf("user address in isr after getdents %x\n",temp);
        //      struct dirent *c = (struct dirent*)temp;
        //      kprintf("nameof entry is %s\n",c->d_name);
        
        
        }
        else if(tf1->rax == 80)
        {

                char *path =(char*)tf1->rdi;
                tf1->rax = change_dir(path);

        }
        else if(tf1->rax == 79)
        {
                uint64_t temp = tf1->rdi;
                uint64_t count  = tf1->rsi;
                tf1->rax = current_dir(temp,count);
        }
	else if(tf1->rax == 32)
	{
		tf1->rax = kdup(tf1->rdi);
	}
	 else if(tf1->rax == 8)
        {
               int fd1 =(int) tf1->rdi;
                uint64_t buf  = tf1->rsi;
		int  opt = (int)tf1->rdx;
              tf1->rax =  klseek(fd1,buf,opt);
        }

	//else if(tf1->rax == 14)
        //{
	//	__asm volatile("movq %%cr2,%0":"=r"(address)::"cc","memory");
        //  kprintf("in fault handler\n");     
        //}
	//printf("%s\n",buf);
}
