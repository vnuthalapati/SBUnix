#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	uint64_t num=0;
	if(argc>=3)
	{
		if(*(argv[1])=='-'&&*(argv[1]+1)=='9')
		{
			while(*(argv[2]+i)!='\0')
        	        {
	                        num = (*(argv[2]+i)-48)+num*10;
	                        i++;
	                }
			__asm volatile("movq $43, %%rax\n\t""movq %0,%%rdi\n\t""int $0x80" ::"r"(num):"%rax");		
		}
	}
	return 0;
}
