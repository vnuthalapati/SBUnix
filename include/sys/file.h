#include<sys/pmap.h>
#include<sys/defs.h>
//#include<sys/kernlib.h>
struct file_desc
{	
//	int type;
	int fd_no;
	uint64_t file_address;
	uint64_t offset;
	int perm;
};
//type 0 is for files
//type 1 is for pipes
struct file
{
	char name[30];
	int type;
	uint64_t start_address;
	uint64_t size;
	uint64_t offset;
	struct file *next;
	struct dirent *dir;
	int read_ref;
	int write_ref;
}*file_list;

struct pipereadlist{
        struct process *proc;
        uint64_t wait_fdes;
        uint64_t requested_bytes;
        //uint64_t const_requested_bytes;
        uint64_t copy_address;
//      uint64_t requested_sleep_time;
        struct pipereadlist *next;
}*pipe_read_list;

struct pipewritelist{
        struct process *proc;
        uint64_t wait_fdes;
        uint64_t requested_bytes;
        uint64_t const_requested_bytes;
        uint64_t copy_address;
//      uint64_t requested_sleep_time;
        struct pipewritelist *next;
}*pipe_write_list;

void insert_to_read(struct pipereadlist *temp_prl);
void insert_to_write(struct pipewritelist *temp_pwl);
int traverse_read_list();
void traverse_write_list();
/*
struct directory{
	char name[30];
	uint64_t start_address;
	uint64_t size;
	uint64_t offset;
	struct dirent *dir;
	struct directory *next;
	int read_ref;
}*directory_list;
*/
struct dirent
{
        long d_ino;
        long d_off;
        unsigned short d_reclen;
        char d_name[256];
	struct dirent *next;
}*dirent_list;	


struct kdirent
{
        long d_ino;
        long d_off;
        unsigned short d_reclen;
        char d_name [256];
};





