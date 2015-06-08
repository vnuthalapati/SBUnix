#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[], char *envp[])
{
	__asm volatile("movq $42, %%rax\n\t""int $0x80" :::"%rax");
	return 0;
}
