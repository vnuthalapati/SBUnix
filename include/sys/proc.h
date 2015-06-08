#include<sys/pmap.h>

#define nprocs 10
int curproc_count;
uint64_t kern_rsp;
struct trap_frame {
uint64_t rsp;
uint64_t r15;
uint64_t r14;
uint64_t r13;
uint64_t r12;
uint64_t r11;
uint64_t r10;
uint64_t r9;
uint64_t r8;
uint64_t rsi;
uint64_t rdi;
uint64_t rbp;
uint64_t rdx;
uint64_t rcx;
uint64_t rbx;
uint64_t rax;
uint64_t err_no;
uint64_t rip;
uint64_t cs; 
uint64_t eflags;
uint64_t ursp;
uint64_t ss;
};
struct process* totalprocs[10];
struct process* process_setup(uint64_t physbase,uint64_t physfree,char *filename);
//int procid;
struct trap_frame ctf;
void proc_status(struct process *proc);
void free_proc(struct process *myproc);
struct vma_area {
uint64_t vma_start;
uint64_t vma_end;
uint64_t perms;
//struct vma_area *prev;
struct vma_area *next;
};


struct process {

char proc_name[100];
int status;
int id;
int ppid;
pml4e_t *pml4e;
struct trap_frame tf;
int state;
uint64_t fd_page;
int fd_count;
//struct process *prev;
struct process *next;
uint64_t kstack;
uint64_t ustack;
char cwd[100];
uint64_t ppf;
int position;
struct vma_area *mm_struct;
};

struct process *procs,*head;
struct process *cur_proc,*prev;
enum{
	ENV_IDLE = 0,
	ENV_WAIT,
	ENV_RUNNABLE,
	ENV_RUNNING,
	ENV_NOT_RUNNABLE,
	ENV_SLEEP,
	ENV_KILLED,
	ENV_PROC_WAIT,
	ENV_PIPE_READ,
	ENV_PIPE_WRITE
};
uint64_t exit_procs[10000][2];
        //exit_procs[total_procs][1] = num;


struct Elf {
	uint32_t e_magic;	
	uint8_t e_elf[12];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
};

struct Proghdr {
	uint32_t p_type;
        uint32_t p_flags;
	uint64_t p_offset;
	uint64_t p_va;
	uint64_t p_pa;
	uint64_t p_filesz;
	uint64_t p_memsz;
	uint64_t p_align;
};

struct Secthdr {
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint64_t sh_addr;
	uint64_t sh_offset;
	uint64_t sh_size;
	uint64_t sh_link;
	uint64_t sh_info;
	uint64_t sh_addralign;
	uint64_t sh_entsize;
};

struct process * proc_create(char *filename);
uint64_t find_elf(char *filename);
void allocate_phys_memory(struct process *myproc,uint64_t size,uint64_t va,uint64_t perm);
void proc_setup_table(struct process * myproc,char *filename);
void elf_copy(struct process * myproc,char *filename);
void setup_stack(struct process *myproc);
struct process* process_setup_exec(uint64_t physbase,uint64_t physfree,char *filename);
/*
struct vma_area {
uint64_t vma_start;
uint64_t vma_end;
uint64_t perms;
struct vma_area *prev;
struct vma_area *next;
}
*/
uint64_t total_procs;
