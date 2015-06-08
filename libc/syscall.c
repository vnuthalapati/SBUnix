#include<stdio.h>
#include<stdlib.h>
#include<syscall.h>
char temp_address[1024];
int stringcmp(char *s,char *t);
struct mylist
{
	unsigned long address;
	unsigned long size;
	int status;
	struct mylist *next;
};
void strcpy(char *s,char *t);
struct timeval {
long int tv_sec;
long int tv_usec;
};

struct rusage {
    struct timeval ru_utime;
    struct timeval ru_stime;
    long   ru_maxrss;
    long   ru_ixrss;
    long   ru_idrss;
    long   ru_isrss;
    long   ru_minflt;
    long   ru_majflt;
    long   ru_nswap;
    long   ru_inblock;
    long   ru_oublock;
    long   ru_msgsnd;
    long   ru_msgrcv;
    long   ru_nsignals;
    long   ru_nvcsw;
    long   ru_nivcsw;
};

struct dir
{
int fd;
struct dirent *d;
//int offset;
};
int curs=0;
int retvalue=0;
int reclen=0;
int fd_open=0;
//int a=10;
void * umyalloc(unsigned long size,int create);
static struct mylist *list=&(struct mylist){.address=0,.size=0,.status = 0,.next=NULL};
typedef unsigned long time_t;
struct timespec {
     time_t tv_sec;
     long tv_nsec;
};

ssize_t write(int fd,const void *buf, size_t count)
{
ssize_t ret;
uint64_t address = (uint64_t)buf;
uint64_t fd1=(uint64_t)fd;
__asm volatile ("movq $0x01, %%rax\n\t""movq %2, %%rdi\n\t""movq %1,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(address),"r"(fd1),"r"(count):"%rax","%rdi","%rsi","%rdx","cc", "memory");
return ret;
}
int open(const char *pathname,int flags)
{
//int ret_open1;
uint64_t ret_open;
uint64_t address = (uint64_t)pathname;
uint64_t flag=(uint64_t)flags;
__asm volatile ("movq $0x02, %%rax\n\t""movq %1, %%rdi\n\t""movq %2,%%rsi\n\t""movq $0x777,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret_open):"r"(address),"r"(flag):"%rax","%rdi","%rsi","%rdx","cc","memory");
//__asm__("movq $0x05, %%rax\n\t""movq %0, %%rbx\n\t""movq %1,%%rdx\n\t""int $0x80" :"=r"(ret):"r"(address),"r"(flag): "%rax","%rbx","%rdx");
//ret_open1=(int)ret_open;
return(int)ret_open;
}

int close(int fd)
{
uint64_t ret_close;
//uint64_t address = (uint64_t)pathname;
uint64_t fd1=(uint64_t)fd;
__asm volatile ("movq $0x03, %%rax\n\t""movq %1, %%rdi\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret_close):"r"(fd1): "%rax","%rdi","cc","memory");
//__asm__("movq $0x05, %%rax\n\t""movq %0, %%rbx\n\t""movq %1,%%rdx\n\t""int $0x80" :"=r"(ret):"r"(address),"r"(flag): "%rax","%rbx","%rdx");
return (int)ret_close;
}
unsigned int alarm(unsigned int seconds)
{
uint64_t ret;
uint64_t sec;
sec=(uint64_t)seconds;
__asm volatile("movq $0x25, %%rax\n\t""movq %1,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(sec): "cc","%rax","%rdi","memory");
return (unsigned int)ret;

}
void exit(int result)
{
uint64_t res=(uint64_t)result;
__asm ("movq $0x3c, %%rax\n\t""movq %0, %%rdi\n\t""int $0x80" ::"r"(res): "%rax","%rdi","cc","memory");
//__asm ("movq $0x01, %%rax\n\t""movq $0x00, %%rbx\n\t""int $0x80" ::: "%rax","%rbx");
}

unsigned int sleep(unsigned int seconds)
{
uint64_t ret;
uint64_t sec=seconds;
//sec=(uint64_t)seconds;
//struct timespec ts = { tv_sec: (long int) seconds, tv_nsec: 0 };
//uint64_t sec=(uint64_t)&ts;
unsigned int ret2;
__asm volatile("movq $0x23, %%rax\n\t""movq %1,%%rdi\n\t""movq %1,%%rsi\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(sec):"%rax","%rdi","%rsi","cc","memory");
//ret2=(unsigned int)ret;
if(ret==0)
{
ret2=(unsigned int)ret;
}
else
{
}
return ret2;
}

pid_t getpid(void)
{
uint64_t ret;
__asm volatile("movq $0x27, %%rax\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret)::"%rax","cc","memory");
return (pid_t)ret; 
}

pid_t getppid(void)
{
uint64_t ret;
__asm volatile ("movq $0x6E, %%rax\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret)::"%rax","cc","memory");
return (pid_t)ret;
}

pid_t fork(void)
{
uint64_t dupid;
__asm volatile ("movq $0x39, %%rax\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(dupid)::"%rax","cc","memory");
return (pid_t)dupid;
}

ssize_t read(int fd, void*buf, size_t count)
{
	uint64_t ret;
	uint64_t fd2=fd;
	char *temp=(char *)buf;
	uint64_t buf1=(uint64_t)temp;
	uint64_t count1=(uint64_t)count;
	__asm volatile("movq $0x0, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(fd2),"r"(buf1),"r"(count1):"%rax","%rdi","%rsi","%rdx","cc","memory");
	return (ssize_t)ret;
}


off_t lseek(int fildes, off_t offset, int whence)
{
 	uint64_t ret;
        uint64_t fd2=fildes;
       // char *temp=(char *)buf;
        uint64_t buf1=(uint64_t)offset;
        uint64_t count1=(uint64_t)whence;
        __asm volatile("movq $0x08, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(fd2),"r"(buf1),"r"(count1):"%rax","%rsi","%rdx","%rdi","cc","memory");
        return (off_t)ret;

}

void *malloc(size_t size)
{
 int size2;
        size2 = size%8;
        if(size2>0){
        size = size+8;
	size = size-size%8;
        }

return (void*)umyalloc(size,0);
}
void * umyalloc(unsigned long size,int create)
{	
//	a=5;
//	void *ret3;
	 int size2;
        size2 = size%8;
        if(size2!=0){
        size = size+8;
	size = size-size%8;
        }
	if(create)
	{	
		unsigned long address;
		unsigned long ret;
		__asm volatile("movq $0x0c, %%rax\n\t""movq $0x0,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret)::"%rax","%rdi","cc","memory");
		address = (unsigned long)ret+size;
		__asm volatile("movq $0x0c, %%rax\n\t""movq %0,%%rdi\n\t""int $0x80"::"r"(address):"%rax","%rdi","cc","memory");
		
		return (void*)ret;
	}
	else
	{
	//	int flag=0;
		unsigned long ret;
		struct mylist *temp;
		//= (struct mylist*)myalloc(sizeof(struct mylist),1);
		//struct mylist *prev = (struct mylist*)myalloc(sizeof(struct mylist),1);
		temp = list;
		//prev = temp;
		while(temp != NULL)
		{
			//printf("%d\n",(int)temp->size);
			if(temp->size > size && temp->status == 0)
			{
				//printf("inside\n");
				ret = temp->address;
				temp->status = 1;
				return (void*)ret;
				
			}
			//prev = temp;
			temp = temp->next;
		}
//		if(!flag)
		{
			//printf("inside not flag\n");
			unsigned long ret,address;
			//,retaddress;
			int count=1;
			//struct mylist *temp = (struct mylist*)myalloc(sizeof(struct mylist),1);
			struct mylist *new = (struct mylist*)umyalloc(sizeof(struct mylist),1);
			temp = list;
			__asm volatile("movq $0x0c, %%rax\n\t""movq $0x0,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret)::"%rax","%rdi","cc","memory");
			//printf("current brk--->%d\n",(int)ret);
			while(temp->next != NULL)
			{
				
				temp = temp->next;
				count++;
			}
			//temp = list;
			//printf("counter--->%d\n",count);
			new->address = ret;
			new->size = size;
			new->status = 1;
			new->next = NULL;
			temp->next = new;
		//	 printf("first new--->%d\tnew->address--->%d\n",new,new->address);	
			//brkaddress = ret;
			//test = brkaddress;
			//*test =212;
			//temp = temp->next;
			//printf("after new--->%lu,new address--->%lu\n",temp->address,new->address,address);
			//temp = list;
			//while(temp!= NULL)
			//{
			//	printf("temp->address 123---->%lu,test address--->%lu\n",((temp->next)->address),test);
			//	temp = temp->next;
			//}
			//printf("temp->address---->%lu",temp->address);
			//retaddress = ret;
			address = ret+size;
		//	printf("newaddress--->%d\n",new);
			__asm volatile ("movq $0x0c, %%rax\n\t""movq %0,%%rdi\n\t""int $0x80"::"r"(address):"%rax","%rdi","cc","memory");
		//	printf("second new--->%d\tnew->address--->%d\n",new,new->address);
		//	printf("brk after inc--->%d\n",(int)ret);
		//	__asm ("movq $0x0c, %%rax\n\t""movq %0,%%rdi\n\t""syscall"::"r"(address):"%rax","%rdi");
//			printf("return address--->%d\n",ret);
			return (void*)ret;
		}
//		else{
//		return (void*)ret;
//		}
	}
}

void free(void * ptr)
{ 	
	//printf("value in a is %d",a);
	unsigned long add = (unsigned long)ptr;
	unsigned long address = add;
	//printf("add is--->%lu,star add is--->%lu\n",add,add);
	struct mylist *temp; //= (struct mylist*)umyalloc(sizeof(struct mylist),1);
//	printf("ptr is--->%lu,address->%lu\n",(unsigned long)ptr,address);
	temp = list;
	//printf("ptr is--->%lu,address->%lu\n",(unsigned long)ptr,address);
	while(temp!=NULL){
	//printf("temp->address---->%lu",temp->address);
	
	temp = temp->next;
	//printf("temp->address---->%lu",temp->address);
	if(temp->address==address)
	break;
	//printf("freeing\n");
	}
	temp->status = 0;

}
/*unsigned long break(unsigned long address)
{
	uint64_t ret;
	uint64_t address1=(uint64_t)address;
	__asm volatile ("movq $0x0c, %%rax\n\t""movq %1,%%rdi\n\t""syscall\n\t""movq %%rax,%0":"=r"(ret):"r"(address):"cc","memory");	
	return (unsigned long)ret;
}*/

int brk(void *end_data_segment)
{
 	uint64_t ret;
        uint64_t address1=(uint64_t)end_data_segment;
        __asm volatile ("movq $0x0c, %%rax\n\t""movq %1,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(address1):"%rax","%rdi","cc","memory");
        return (int)ret;

}

//static int count = 0;
void *opendir(const char *name)
{
/*implement getcwd and then append the name rreceived to it and send that name to open.*/
struct dir *dir1=(struct dir*)malloc(sizeof(struct dir));
int fd1;
fd1=open(name,O_RDONLY|O_DIRECTORY);
if(fd1>0){
fd_open=fd1;
dir1->fd=fd1;
return (void*)dir1;
}else{
return NULL;
}

}

int closedir(void *dir)
{
struct dir *dir2;
int i=0;
//dir2=(struct dir*)(sizeof(struct dir*)*30);
dir2=(struct dir*)dir;
if(dir2)
{
i=close(dir2->fd);
free(dir2);
}
return i;
}



struct dirent *readdir(void *dir2)
{
struct dir *dir1=(struct dir*)dir2;
uint64_t dir3=(uint64_t)dir1->fd;
struct dirent *d;
uint64_t ret1;
if(fd_open==(int)dir1->fd)
{
//printf("curser value is  %d\n",curs);
curs=curs+reclen;
//printf("curser value is  %d\n",curs);
//printf("curser value is  %d\n",curs);
}
  if(curs>=retvalue || curs==0)
{

 __asm volatile("movq $0x4E, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq $0x400,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret1):"r"(dir3),"r"(temp_address):"%rax","%rdi","%rsi","%rdx","cc","memory");
retvalue=(int)ret1;
curs=0;
//}
//printf("retvalue used is %d\n",retvalue);
}
if(retvalue==1||retvalue==0)
{
return NULL;
}

            d = (struct dirent *)(temp_address+curs);
    //   printf("returned curs value is %d\n",curs);
            reclen=d->d_reclen;
	//	printf("reclen value is %d\n",reclen);
                if(d!=NULL){
                return d;
                }else{
return NULL;
}

//return NULL;
}


void strcpy(char *s,char *t)
{
int i=0;
while((s[i]=t[i])!='\0')
{
i++;
}
}


char *getcwd(char *buf, size_t size)
{
uint64_t dir3=(uint64_t)buf;
uint64_t temp2=(uint64_t)size;
uint64_t ret1;
 __asm volatile("movq $0x4F, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret1):"r"(dir3),"r"(temp2):"%rax","%rdi","%rsi","cc","memory");
if(ret1==-1){
printf("Buffer size is not sufficient");
return NULL;
}else{
return (char*)dir3;
}
}

int chdir(const char *path)
{
uint64_t dir3=(uint64_t)path;
uint64_t ret1;
 __asm volatile("movq $0x50, %%rax\n\t""movq %1,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret1):"r"(dir3):"%rax","%rdi","cc","memory");
return (int)ret1;
}
int execve(const char *filename, char *const argv[], char *const envp[])
{
	char A[50],D[50];
        char *buf = A;
         uint64_t dupid;
        char *newname =D;
        int i=2,j=0,fd;
        char *args[4];
        fd=open(filename,0);
        read(fd,buf,50);
        if(buf[0]=='#' && buf[1]=='!'){
                while(buf[i]!='\n'){
                newname[j]=buf[i];
                i++;
                j++;
                }
                newname[j]='\0';
                j=0;
                args[0] = (char*) malloc(50);
                while(newname[j]!='\0'){
                args[0][j]=newname[j];
                j++;
                }
                args[0][j]='\0';
                j=0;
                args[1] = (char*)malloc(50);
                while(filename[j]!='\0'){
                args[1][j]=filename[j];
                j++;
                }
                args[1][j]='\0';
                j=0;
                args[2]=NULL;
                __asm volatile("movq $0x3B, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(dupid):"r"(newname),"r"(args),"r"(envp):"%rax","%rdi","%rsi","%rdx","cc","memory");
                j=0;

        }else{
	
//        uint64_t dupid;
        __asm volatile("movq $0x3B, %%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(dupid):"r"(filename),"r"(argv),"r"(envp):"%rax","%rdi","%rsi","%rdx","cc","memory");
}  
      return dupid;
}

pid_t waitpid(pid_t pid, int *status, int options)
{
        struct rusage ru;
        uint64_t dupid,pid1=(uint64_t)pid,dupru=(uint64_t)&ru,dupstatus=(uint64_t)status,dupoptions=(uint64_t)options;
        __asm volatile("movq $0x3D,%%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""movq %3,%%rdx\n\t""movq %4,%%r10\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(dupid):"r"(pid1),"r"(dupstatus),"r"(dupoptions),"r"(dupru):"%rax","%rdi","%rsi","%rdx","%r10","cc","memory");
        //free(ru);
        return (pid_t)dupid;
}

int pipe(int filedes[2])
{
        uint64_t fd = (uint64_t)filedes,ret;
        __asm volatile("movq $0x16,%%rax\n\t""movq %1,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(fd):"%rax","%rdi","cc","memory");
        return (int)ret;
}
int dup(int oldfd)
{
        uint64_t ofd = (uint64_t)oldfd;
        uint64_t ret;
        __asm volatile("movq $0x20,%%rax\n\t""movq %1,%%rdi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(ofd):"%rax","%rdi","cc","memory");
        return (int)ret;
}
int dup2(int oldfd, int newfd)
{
        uint64_t ofd = (uint64_t)oldfd,nfd=(uint64_t)newfd;
        uint64_t ret;
        __asm volatile("movq $0x21,%%rax\n\t""movq %1,%%rdi\n\t""movq %2,%%rsi\n\t""int $0x80\n\t""movq %%rax,%0":"=r"(ret):"r"(ofd),"r"(nfd):"%rax","%rsi","%rdi","cc","memory");
        return (int)ret;
}
/*
void write2(int fd,const void *buf, uint64_t count)
{
uint64_t ret;
uint64_t address = (uint64_t)buf;
uint64_t fd1=(uint64_t)fd;
__asm volatile ("movq $0x01, %%rax\n\t""movq %2, %%rdi\n\t""movq %1,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(address),"r"(fd1),"r"(count):"%rax","%rdi","%rsi","%rdx","cc", "memory");
//return ret;
}
*/
int stringcmp(char *s,char *t)
{
int i=0;
char temp1;
char temp2;
for(i=0;s[i]!='\0';i++)
{
temp1=s[i];
temp2=t[i];
	if(temp1>temp2)
	{
	return 1;
	}
	else if(temp1<temp2)
	{
	return -1;
	}
}
return 0;
}
