#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[], char * envp[])
{
//	int i=0;
/*	int fds[2];
	pipe(fds);
	int pid=fork();
	char *buf = (char *) malloc(50);
//	while(i<1000)
//	{
	if(pid>0)
	{
	close(fds[1]);
	dup2(fds[0],0);
	close(fds[0]);
	read(0,buf,1024);
	printf("%s\n",buf);
//	close(fds[0]);
//	pid = fork();
	}
	else
	{
	close(fds[0]);
	write(fds[1],"hello professor\0",16);
//	close(fds[1]);
	}
//	i++;
//	}*/
	int fd1;
        fd1 = open("test.txt",1);
        printf("fd1 is %d\n",fd1);
	/*uint64_t *temp = (uint64_t*)0x67891273123121;
	*temp = 20;*/
	return 0;
}
