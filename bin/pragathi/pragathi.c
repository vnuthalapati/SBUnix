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

void outerpeace(int x)
{
        int a=12,b=23,c=34;
//	char q='M';
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
        int a = 10,b=100;
//	char q='M';
        a = a+b;
        b = b-a;
        //innerpeace(a);
        //printf("it is me\n");
//	char *st = "proc 1";
//	q = (char*)malloc(30);
  //      *q = 'M';
//        printf("%c",q);
//        q = (char*)malloc(30);
//        *q = 'P';
 //       printf("%c",*q);
/*        a = 0;
	char A[100];
	char *ru=A;
	scanf("%s\n",ru);
	printf("ru value is %s\n",ru);*/
       // while(1)
        {
//	char *m = "x";
        //write2(1,"x",1);
	// printf("n");
        a = a+1;
	
//	printf("three\n");
//	printf("%s\n",st);
//        outerpeace(a);
        };
	while(1);
	//printf("all killed\n");
      return 0;
}

