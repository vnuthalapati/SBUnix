#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]);

void _start(void) {
	uint64_t address;
	int argc = 1;
	char** argv=NULL;
	char** envp=NULL;
	int res;
	   __asm("movl 8(%%rsp),%0":"=r"(argc)::"memory");
        __asm("movq %%rsp,%%rax\n\n""addq $0x10,%%rax\n\t""movq %%rax,%0":"=r"(argv)::"memory");
        address = argc*8+24;
        __asm("movq %%rsp,%%rax\n\t""addq %1,%%rax\n\t""movq (%%rax),%0":"=r"(envp):"r"(address):"memory");
        __asm("movq %%rsp,%%rax\n\t""addq %1,%%rax\n\t""movq %%rax,%0":"=r"(envp):"r"(address):"memory");
	res = main(argc, argv, envp);
	exit(res);
}
