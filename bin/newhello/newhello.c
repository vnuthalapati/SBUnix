#include<stdio.h>
#include<sys/defs.h>
#include<stdlib.h>
//void write2(int fd,const void *buf, uint64_t count);

struct dir
{
int fd;
struct dirent *d;
//int offset;
};

void innerpeace(int x)
{
	int a=12,b=23,d=34;
	//char c='Y';
	//char *v = (char*)0xFFFFFFFF80002000;
	//char *v = "h";	
	//*v = 's';
	//v = v+1;
	//*v = '\0';
	//write2(1,v,1);
	a = a+b;
	b = b+d;
	d = d-1;
//	c = (char*)malloc(30);
  //      *c = 'Y';
//        printf("%c",c);
}
void tempfunc()
{
}
int main(int argc, char* argv[], char* envp[]) {
//       printf("Hello World!\n");
        int a = 10,b=100;//,x=1,pos=0;
//	int pid;
//	int i=0;
//	char *args[] = {"hello","world","new",'\0'};
//	char *envs[] = {"old","pragathi","radha",'\0'};
//	int A[100];
	//int *w=A;
	//char c='Y';
        a = a+b;
        b = b-a;
//	char A[100];
//	char B[100];
//	int count1=0,count2=0;
//	char C[100];
//	char *f = C;
	//innerpeace(a);
//	printf("it is me");
//	a = 0;
/*	char *c;
	c = (char*)malloc(3700);
	while(i<3699){
		*(c+i)='h';
		i++;

	}
//	*
//	c = 'K';
	//int fds[2];
	int fids[2];
	int pid;//,j=1,k=0;
//	char sy = 'm';
	pipe(fids);
	pid = fork();
	if(pid>0)
	{
		read(fids[0],B,100);
		char *sup = B;
		printf("read value is %s\n",sup);

	}else{
		printf("i am child\n");
		write(fids[1],c,3699);
	}*/
/*
	 char *c;
        int fd[2],pid;
        c = (char*)malloc(5000);
        char *k = (char*)malloc(5000);
        while(i<4999)
        {
        *(k+i) = 'y';
        i++;
        }
        //scanf("%s",c);
        //printf("data in malloced->%s\n",c);
        pipe(fd);
        pid = fork();
//      pipe(fd);
        if(pid>0)
        {
        //close(fd[1]);
        read(fd[0],c,4999);
        printf("data read is--->%s\n",c);
        }
        else
        {
        //int k = 0;
        printf("in childi--->%d\n",i);
        printf("second\n");
//      while(i<4299)
        {
        //printf("inside writer loop\n");
        write(fd[1],k,4999);
        //printf("after write\n");
        i++;
        }
        printf("in childi--->%d\n",i);
        }*/
	char *args[] = {"bin/second/",'\0'};
	char *envs[] = {"PATH=bin",'\0'};	
	//argv[1] = "bin/second/";
	execve("bin/sbush",args,envs);

//	execve("bin/ls",envp);
	// int i=0;
//        global_var++;
//      printf("value of glov is %d\n",global_var);
/*        struct dirent *cap = (struct dirent*)malloc(sizeof(struct dirent));
        struct dir *an = (struct dir*)malloc(sizeof(struct dir));
//         struct dir *and = (struct dir*)malloc(sizeof(struct dir));
         printf("opening directory\n");
        an = (struct dir*)opendir("bin/first/");
        if(an!=NULL){
        printf("The file desc is-->%d\n",an->fd);
        
        while((cap=(struct dirent*)readdir(an))!=NULL)
        {
        printf("The directory name is-->%s\n",cap->d_name);
        }
        }

*/
/*	char *sy=(char*)malloc(8000);
	printf("Before Writing\n");
	while(k<7900){
	if(k%79==0)
	j=j*-1;
	//else continue;
	if(j==1)
	{
		sy[i]='p';
	}
	else
	{
		sy[i]='a';

	}
	i++;
	k++;
	}*/

/*	char *sy="hello world";
	printf("after populating\n");
*/	
	/* printf("opening file\n");
      a = open("bin/first/test.txt",2);
       printf("The fiile desc is-->%d\n",a);
      while(x!=0)
        {
        x=read(a,&C[pos],1);
        pos = pos+x+1;
      // printf("bytes read is %s\n",C);
        }
	printf("read done\n");
	printf("bytes read is %s\n",C);*/
//	pipe(fds);
/*	pipe(fids);
	int g=0;
	printf("pipes created\n");*/
//	printf("file ids  are %d\n",fds[0]);
//	printf("file ids  are %d\n",fds[1]);
//	pid = fork();
//	printf("fork called\n");
///	if(pid>0)
/*	{
		waitpid(pid,&a,1);
		read(fds[0],A,100);
		char *st = A;
		printf("first parent %s\n",st);*/
/*		pid2 = fork();
     	   	if(pid2>0)
        	{
		// write(fids[1],sy,4);
	//	waitpid(pid2,&a,1);
	//	char B[100]={'\0'};
		//i=0;
	//	read(fids[0],B,100);
	//	while(B[0]!='\0'){
		close(fids[1]);
		dup2(fids[0],0);
		//waitpid(pid2,&a,0);	
                g=read(0,B,20);
		while(g!=0)
		{
		printf("bytes read is %d\n",g);
                char *so = B;
                printf("second parent %s\n",so);
		for(a=0;a<20;a++)
		B[a]='\0';
		g = read(0,B,20);
		}
		printf("done with reading\n");
		//close(fids[0]);
	//	i++;
	//	}
       // printf("I am Parent\n");


        	}
		else{
		close(fids[0]);
		dup2(fids[1],1);
		execve("bin/hello",args,envs);
	         write(1,sy,11);
		write(1,sy,11);
		write(1,sy,11);
		write(1,sy,11);
		//close(fids[1]);
	//	*sy = '\0';
	//	 write(fids[1],sy,1);
		//waitpid(getppid(),&a,1);
	//	 read(fids[0],B,6);
               // char *so = B;
               // printf("second child %s\n",so);
                printf("i am second child my id is %d\n",getpid());
  //      printf("I am Child");

        	}*/

//	printf("I am Parent\n");	

/*	}else{

		write(fds[1],f,100);
		printf("i am first child my id is %d\n",getpid());
//	printf("I am Child");
	}*/
/*	pid2 = fork();
	if(pid2>0)
	{
		read(fids[0],B,6);
                char *so = B;
                printf("second parent %s\n",so);
       // printf("I am Parent\n");


	}else{
	 write(fids[1],sy,6);
                printf("i am second child my id is %d\n",getpid());
  //      printf("I am Child");

	}*/
//	printf("opening file\n");
//	a = open("bin/first/test.txt",2);
//	 printf("The fiile desc is-->%d\n",a);
/*	while(x!=0)
	{
	x=read(a,&A[pos],10);
	pos = pos+x+1;
//	printf("bytes read is %s\n",A);
	}*/
//	printf("bytes read is %s\n",A);
//	printf("The fiile desc is-->%d\n",a);
//	while(1);
//	execve("dummy",args,envs);
/*	pid = fork();
	if(pid>0)
	{
//	while(1){
	printf("waiting on--->%d,pid is--->%d\n",pid,getpid());
	waitpid(pid,&a,0);
	printf("i am parent\n");
//while(1);
//	printf("in parent %d\n",getpid());
	}
//	}
	
	else
	{
//	while(1){
//	waitpid(1,w,0);
	printf("i am child,my id is--->%d,parent id is--->%d\n",getpid(),getppid());
	//printf("in child process id is %d\n",getpid());
//	printf("in child process parent id is %d\n",getppid());
	}*/
	//}
	
//	printf("%c",c);
//	c = (char*)malloc(30);
//        *c = 'Y';
/*	char A[1000];
	char *c=A;
	scanf("%s",c);
       printf("%s\n",c);*/
//	int num;
	/*scanf("%x",&num);
	printf("in decimal format is%d\n",num);
	printf("in hexadecimal format is%x\n",num);*/
/*	char k;
	scanf("%c",&k);
	printf("%c\n",k);*/
//	tempfunc();
	
	//printf("first\n");
	//waitpid(1,&x,0);
//	printf("printed after wait");
//	sleep(1);
/*	int f;
	scanf("%d",&f);
	printf("%d\n",f);*/
/*	while(1)
	{
	//char *m = "e";
	//for(i=0;i<5;i++)
        //write2(1,"e",1);
	//printf("e");
	a = a+1;
	innerpeace(a);
	//printf("one\n");
	//printf("%d\n",a);
	};*/
//	while(1)
	{

//	printf("first process\n");

	}
      return 0;
}
/*
void write2(int fd,const void *buf, uint64_t count)
{
uint64_t ret;
uint64_t address = (uint64_t)buf;
uint64_t fd1=(uint64_t)fd;
__asm volatile ("movq $0x01, %%rax\n\t""movq %2, %%rdi\n\t""movq %1,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(address),"r"(fd1),"r"(count):"%rax","%rdi","%rsi","%rdx","cc", "memory");
//return ret;
}*/


