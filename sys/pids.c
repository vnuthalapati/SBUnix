#include<sys/kernlib.h>
int kpid(){
int pid;
pid =  cur_proc->id;
return pid;
}

int kppid(){
int ppid;
ppid = cur_proc->ppid;
return ppid;
}
