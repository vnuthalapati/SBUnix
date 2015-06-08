#include<stdlib.h>
#include<stdio.h>
struct dir
{
int fd;
struct dirent *d;
//int offset;
};
int main(int argc,char *argv[],char *envp[]){
//printf("entered ls\n");
int i=0;//,count=0,var=0,j=0;
//char temp[100];
struct dir *mydir;
    struct dirent *myfile;
	char ty[100];
	for(i=0;i<100;i++){
		ty[i]='\0';
	}
	char *stry = ty;
	getcwd(stry,90);
	if(stry[0]!='\0'){
//	printf("cwd is %s\n",stry);
	}
	i=0;
/*	while(stry[i]!='\0'){
		if(stry[i]=='/')
		{
			count++;
		}
		i++;
	}*/
//	i=0;
	//printf("count val is %d\n",count);
    mydir =(struct dir*)opendir(stry);
    while((myfile = readdir(mydir)) != NULL)
    {
       // printf("%d",mystat.st_size);
	/*ij=0;
	i=0;
	while(myfile->d_name[i]!='\0'){
		 printf("%s\n",myfile->d_name);
	   	if(myfile->d_name[i]=='/'){
		var++;
		}
		if(var==count){
		temp[j]=myfile->d_name[i];
	//	printf("%c\n",myfile->d_name[i]);
		j++;
		}
	i++;
	}
	temp[j]='\0';
	//j=0;*/
	char *temp,*ptr;
	temp  = myfile->d_name;
	ptr = temp;
	while(*temp!='\0')
	{
		if(*temp=='/')
		{
			ptr = temp+1;
		}
		temp++;
	}	
        printf("%s  ",ptr);
    }
	printf("\n");
    closedir(mydir);
return 0;
}

