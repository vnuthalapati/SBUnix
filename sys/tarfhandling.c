#include <sys/tarfs.h>
#include <sys/proc.h>
#include <sys/sbunix.h>
#include <sys/tarfshandling.h>
#include<sys/string.h>
//uint64_t octaltodecimal(char *s);
int strngcmp(char *s,char *t);
int gc=0;
struct posix_header_ustar* traverse(char *filename)
{
	struct posix_header_ustar *phu;
	uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
	int i=0;
	uint64_t bound=0,prev=fsstart;
	bound = fsstart;
	phu = (struct posix_header_ustar*) (fsstart);
	while((strngcmp(phu->name,""))){
	bound = 0;
	bound = octaltodecimal((phu)->size);
	if(bound%512!=0){
	bound = bound + 512;
	bound = bound-bound%512;
	}
	prev = prev + sizeof(struct posix_header_ustar) + bound;
	phu = (struct posix_header_ustar*)(prev);
	i++;
	if((strngcmp((char*)(phu->name),filename))==0){
	//	kprintf("entered this loop %s\n",phu->typeflag);
		return (phu+1);
		
	}
	}
//	kprintf("file name in traverse function is--->%s\n",(phu+1)->name);
	return NULL;
//	printf("first file name is--->%s\n",(phu)->name);

}

uint64_t octaltodecimal(char *sy){
	uint64_t i=0,j = 0,sum=0;
	//;
	//int decbase = 10;
	int digit;
	char a[100];
	char *rev=a;
	int len = 0;
	while(*(sy+len) != '\0')
	len++;
	for(i = 0; i<len ; i++)
	{
		*(rev+i) = *(sy+len-i-1); 
	}
//	printf("s--->%s\trev--->%s",s,rev);
	for(i = 0; i<len ; i++)
	{
		digit = *(rev+i)-48;
		for(j=0;j<i;j++)
		digit = digit * 8;
		sum = sum + digit;
	}	
	return sum;
}
struct posix_header_ustar* traverse_file(char *filename)
{
        struct posix_header_ustar *phu;
        uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
        int i=0;
        uint64_t bound=0,prev=fsstart;
        bound = fsstart;
        phu = (struct posix_header_ustar*) (fsstart);
	 if((strngcmp((char*)(phu->name),filename))==0){
        //       kprintf("entered this loop %s\n",phu->name);
               // break;
                return phu;
        }

//	kprintf("before while loop\n");
        while((strngcmp(phu->name,""))){
        bound = 0;
        bound = octaltodecimal((phu)->size);
        if(bound%512!=0){
        bound = bound + 512;
        bound = bound-bound%512;
        }
        prev = prev + sizeof(struct posix_header_ustar) + bound;
        phu = (struct posix_header_ustar*)(prev);
        i++;
//	 kprintf("in traverse returned is---%s\n",phu->name);
	//kprintf("filemane in traverse--->%s\n",phu->name);
        if((strngcmp((char*)(phu->name),filename))==0){
        //        kprintf("entered this loop %s\n",phu->name);
               // break;
		return phu;
        }
        }
  //      kprintf("in traverse file name is--->%s\n",(phu)->name);
        return NULL;
//      printf("first file name is--->%s\n",(phu)->name);

}

struct posix_header_ustar* traverse_file_content(char *filename)
{
        struct posix_header_ustar *phu;
        uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
        int i=0;
        uint64_t bound=0,prev=fsstart;
        bound = fsstart;
        phu = (struct posix_header_ustar*) (fsstart);
        while((strngcmp(phu->name,""))){
        bound = 0;
        bound = octaltodecimal((phu)->size);
        if(bound%512!=0){
        bound = bound + 512;
        bound = bound-bound%512;
        }
        prev = prev + sizeof(struct posix_header_ustar) + bound;
        phu = (struct posix_header_ustar*)(prev);
        i++;
        if((strngcmp((char*)(phu->name),filename))==0){
        //        kprintf("entered this loop %s\n",phu->name);
               // break;
		return phu+1;
        }
        }
      //  kprintf("in traverse file content--->%s\n",(phu)->name);
        return NULL;
//      printf("first file name is--->%s\n",(phu)->name);

}

struct posix_header_ustar* traverse_directory(char *filename)
{
        struct posix_header_ustar *phu;
        uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
        int i=0;
        uint64_t bound=0,prev=fsstart;
        bound = fsstart;
        phu = (struct posix_header_ustar*) (fsstart);
	if((strngcmp((char*)(phu->name),filename))==0){
        //        kprintf("entered this loop %s\n",phu->name);
               // break;
        //      gc++;
                char d[1];
                d[0]='0';
                if(scmp((char*)phu->typeflag,d)==0){
                phu = phu+2;
                return (struct posix_header_ustar*)phu;
                }
                struct posix_header_ustar* phu2 = (struct posix_header_ustar*)(phu+1);
                return (struct posix_header_ustar*)phu2;
                }
        
        while((strngcmp(phu->name,""))){
        bound = 0;
        bound = octaltodecimal((phu)->size);
        if(bound%512!=0){
        bound = bound + 512;
        bound = bound-bound%512;
        }
        prev = prev + sizeof(struct posix_header_ustar) + bound;
        phu = (struct posix_header_ustar*)(prev);
        i++;
//	kprintf("in traverse returned is---%s\n",phu->name);
        if((strngcmp((char*)(phu->name),filename))==0){
                //kprintf("entered this loop %s\n",phu->name);
               // break;
	//	gc++;
		char d[1];
	        d[0]='0';
		uint64_t temp6;
        	if(scmp((char*)phu->typeflag,d)==0){
		 bound = 0;
	        bound = octaltodecimal((phu)->size);
        	if(bound%512!=0){
	        bound = bound + 512;
	        bound = bound-bound%512;
        	}
       	 	temp6 = (uint64_t)phu+sizeof(struct posix_header_ustar) + bound;
		return (struct posix_header_ustar*)temp6;
        	}
		struct posix_header_ustar* phu2 = (struct posix_header_ustar*)(phu+1);
                return (struct posix_header_ustar*)phu2;
		}
        }
	
        
//      	kprintf("in traverse returned is---\n");
        return NULL;
//      printf("first file name is--->%s\n",(phu)->name);

}

