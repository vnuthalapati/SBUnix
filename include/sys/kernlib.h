#include<sys/defs.h>
#include<sys/proc.h>
#include<sys/file.h>
void* kmalloc(size_t size);
void free(void *add);
struct mylist
{
        unsigned long address;
        unsigned long size;
        int status;
        struct mylist *next;
};
int kdup(uint64_t oldfd);
uint64_t kbreak(uint64_t addr);
void fault_handler(struct trap_frame *tf1);
void kfork();
uint64_t kwaitpid(uint64_t pid, int *status, int options);
void kexit(int num);
char standardin[2048];
int curr_pos;
struct readlist{
struct process *proc;
uint64_t buf;
uint64_t requested_bytes;
struct readlist *next;
}*read_wait_list;
int kread(int fd,uint64_t add,uint64_t num);
int kopen(const char* pathname, int flags);
void input(char c);
struct sleeplist {
struct process *proc;
uint64_t timecount;
uint64_t requested_sleep_time;
struct sleeplist *next;
}*sleep_list;
void check_write_queue();
void clear_queues(struct process *myproc);
void kkill(uint64_t pid);
void check_read_queue();
int kclose(int fd);
int kdup2(int old,int newfd);
int silent_close(int fd);
struct waitlist{
	struct process *proc;
	uint64_t waiting_on;
//	uint64_t requested_sleep_time;
	struct waitlist *next;
}*wait_list;
int kexecve(const char *filename, char *const argv[], char *const envp[]);
void ksleep(uint64_t sleep_time);
void awaken();
int kppid();
int kpid();
void kps();
size_t kwrite(int fd,uint64_t add, size_t num);
int kpipe(int *filedes);
int kgetdents(int fd,uint64_t temp,int count);
int current_dir(uint64_t temp,uint64_t count);
int change_dir(char *path);
uint64_t klseek(int fildes, uint64_t offset, int whence);
//int index;
//int count;
/*struct pipereadlist{
        struct process *proc;
        uint64_t wait_fdes;
	uint64_t requested_bytes;
	uint64_t copy_address;
//      uint64_t requested_sleep_time;
        struct pipereadlist *next;
}*pipe_read_list;

struct pipewritelist{
        struct process *proc;
        uint64_t wait_fdes;
	uint64_t requested_bytes;
	uint64_t copy_address;
//      uint64_t requested_sleep_time;
        struct pipewritelist *next;
}*pipe_write_list;8*/
