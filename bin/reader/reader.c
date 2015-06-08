#include<stdlib.h>
#include<stdio.h>
int main(int argc,char* argv[],char* envp[])
{
	char A[100];
	printf("in reader\n");
	read(0,A,100);
	printf("A is-->%s\n",A);
	return 0;
}
