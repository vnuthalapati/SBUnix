#include<stdio.h>
#include<stdlib.h>
#include<sys/defs.h>
/*void write2(int fd,const void *buf, uint64_t count)
{
uint64_t ret;
uint64_t address = (uint64_t)buf;
uint64_t fd1=(uint64_t)fd;
__asm volatile ("movq $0x01, %%rax\n\t""movq %2, %%rdi\n\t""movq %1,%%rsi\n\t""movq %3,%%rdx\n\t""int $0x80\n\t""movq %%rax,%0" :"=r"(ret):"r"(address),"r"(fd1),"r"(count):"%rax","%rdi","%rsi","%rdx","cc", "memory");
//return ret;
}*/
struct dir
{
int fd;
struct dirent *d;
//int offset;
};

void outerpeace(int x)
{
        int a=12,b=23,c=34;
//	char q='P';
        //char *v = (char*)0xFFFFFFFF80003000;

        //char *v = "y";
	//write2(1,v,1);
//	v = v+1;
//	*v = '\0';
        a = a+b;
        b = b+c;
        c = c-1;
//	q = (char*)malloc(30);
  //      *q = 'M';
//        printf("%c",q);
}
int main(int argc, char* argv[], char* envp[]) {
//       printf("Hello World!\n");
        int a = 10,b=100;//i=0;
	char *sy="hello world";
//	char q='P';
        a = a+b;
        b = b-a;
	write(1,sy,11);
	//printf("after write 1\n");
        write(1,sy,11);
        write(1,sy,11);
        write(1,sy,11);
	//char *args[] = {"hello","world","new",'\0'};
        //innerpeace(a);
        //printf("it is me\n");
//	char *st = "proc 1";
//	q = (char*)malloc(30);
   //     *q = 'M';
       // printf("%c",q);
	a = 0;
      //  char A[100];
    //    char *ru=A;
//        scanf("%s",ru);
  //      printf("ru value is %s\n",ru);	
//        q = (char*)malloc(30);
//        *q = 'P';
//        printf("%c",*q);
//	printf("in process hello");
//        a = 0;
        //while(1)
/*	while(i<argc){
	printf("received arguments %s\n",argv[i]);
	printf("args of envp %s\n",envp[i]);
	i++;
        }*/
	//char *filename ="/bin/hello";
	//execve(filename,args,envp);
	/*struct dirent *cap = (struct dirent*)malloc(sizeof(struct dirent));
        struct dir *an = (struct dir*)malloc(sizeof(struct dir));
//         struct dir *and = (struct dir*)malloc(sizeof(struct dir));
         printf("opening directory\n");
        an = (struct dir*)opendir("bin/first/");
        if(an!=NULL){
        printf("The file desc is-->%d\n",an->fd);

        while((cap=(struct dirent*)readdir(an))!=NULL)
        {
        printf("The second process is-->%s\n",cap->d_name);
        }
        }*/
	
	/*
	
//	char *m = "x";
        //write2(1,"x",1);
	// printf("n");
        a = a+1;
//i	printf("two\n");
//	printf("%s\n",st);
//        outerpeace(a);
        };*/
//	while(1){
//	printf("two\n");
//	}
	//while(1)	
	//waitpid(4,&a,0);
//	printf("Hello\n");
/*	write(1,sy,11);
                write(1,sy,11);
                write(1,sy,11);
                write(1,sy,11);		*/
	//waitpid(1,&a,0);
//	printf("after 3rd has finished\n");
      return 0;
}

