#include <stdio.h>
#include <stdlib.h>
//int main(int argc,char *argv[],char *envp[])
//{
/*int i=0,j=0;
char c;
//char *s=(char*)malloc(sizeof(char)*30);
//int j=0;
char c;
for(i=0;i<5;i++)
{
a1=malloc(sizeof(char)*200);
for(j=0;j<100;j++)
{
a1[j]='a';
}
free(a1);
//char *a2=malloc(sizeof(char)*100);
//free(a2);
}*/
/*scanf("%c",&c);
scanf("%d",&i);
scanf("%x",&j);
//scanf("%s",s);
printf("c value is %c\n",c);
printf("i value is %d\n",i);
printf("j value is %x\n",j);
//printf("s value is %s\n",s);
//free(a1);
//free(a2);
*/
/*struct dir *mydir;
    struct dirent *myfile;
    mydir =(struct dir*)opendir(argv[1]);
    while((myfile = readdir(mydir)) != NULL)
    {
       // stat(myfile->d_name, &mystat);    
       // printf("%d",mystat.st_size);
        printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
}

*//*
return 0;
}
*/
//int i=2145383411;
//char* s="adasdsad";
/*unsigned long x=1844;
printf("%p",&x);
//printf("%d----%d\n",i,i);
return 0;
}
*/


struct dir
{
int fd;
struct dirent *d;
};

int strngcmp(char *s,char *t);
void cd(char*,char*env[]);
void splitter(char*,char *envp[],char *ps);
void pathcheck(char *allcommands[],int num,char *env[],char *ps);
void executor(char * commands[],char * envp[], char * ps[],int num,int pssize,char *ps1);
void scriptex(int fd,char *envp[],char *ps);
char *stringcat(char *s,char *t);
//void binar(char* commands[], char * env[],char * ps[],int num,int pssize,char *ps1);

int main(int argc, char* argv[], char* envp[])
{
	int a,b,choice,p,i,fd=0;
	char C[100];
	//char currentpwd[1000];
	char *ps = C;
	ps = "";
	while(1)
	{
//	label1; 
	a=0;b=0;choice=-1;p=0,i=0;
	char c[1000]={'\0'};
	int fl =0,t=0;
	char A[200],B[200];
	//B[200]={0};
	char *command = A;
	char *path = B;
	char *path1,*temppath;
	char *coms[] = {"spawn","cd","exit","setpath","setps","sbush"};
       /* for(i=0;i<1000;i++){
    		currentpwd[i]='\0';
	}
	i=0;
	getcwd(currentpwd,1000);
	printf("%s",currentpwd);*/
	if(strngcmp(ps,""))
	printf("@");
	printf("%s",ps);
	printf("$");
	if(argc!=2){
//	argc=0;
	scanf("%s",c);
//	printf("%s",c);
		if(c[a]=='\0' || c[a]=='\n')
		{
//		goto label1:
		continue;
		}		
		while(c[a] != ' ' && c[a] != '\0')
		{ 
		*(command+a) = c[a];
		a++;
		}
	command[a] = '\0';
		while(b<6)
		{
			while((*(coms[b]+p) == command[p]) && command[p] != '\0')
			p++;
		if((*(coms[b]+p) == command[p]) && command[p] == '\0')
		{
		choice = b;
		break;
		}
		b++;
		}

	if(choice == -1)
	choice = 6;
	}
	if(argc == 2)
	choice = 5;
	switch(choice)
	{	
	case 0:
	path = c+a+1;
	//spawn(path);
	break;
	case 1:
	B[200]='\0';
	path = c+a+1;
	 path1=malloc(sizeof(char*)*200);
        while(path[i]!='\0')
        {
        path1[i]=path[i];
        i++;
        }
        temppath=path1;
	cd(temppath,envp);
	char go[100];
	char *s=go;
	for(i=0;i<100;i++)
	go[i]='\0';
	//getcwd(s,5);
	printf("%s",getcwd(s,100));
	break;
	case 2:
	exit(0);
	break;
	case 3:
	path = c+a+1;
	//printf("\npath is--->%s\n",path);
	while(!fl)
	{
		if(*envp[t]=='P' && *(envp[t]+1)== 'A' && *(envp[t]+2) == 'T' && *(envp[t]+3) == 'H' && *(envp[t]+4) == '=')
		{
		//  printf("\n%s\n",envp[t]);
               // printf("\n%s\n",path);

		envp[t] = stringcat(envp[t],":");
		envp[t] = stringcat(envp[t],path);
		fl = 1;
		}
		t++;
	}
//	printf("\n%s\n",envp[t-1]);
	break;
	case 4:
	path = c+a+1;
	path1=malloc(sizeof(char*)*200);
	while(path[i]!='\0')
	{
	path1[i]=path[i];
	i++;
	}
	ps=path1;
	//ps = path;
	break;
	case 5:
	fd=0;
	if(argc==2)
	{
	argc = 0;
	fd=open(argv[1],0);
	printf("returned fd is %d\n",fd);
	if(fd<0)
	{
	printf("Invalid filename");
	}
	else{
	scriptex(fd,envp,ps);
	}
	}
	else{
//	printf("insbush\n");
	path=c+a+1;
	fd=open(path,0);
	if(fd<0)
	{
	printf("Invalid filename\n");
	}
	else{
	scriptex(fd,envp,ps);
	}
	}
	break;
	case 6:
	if(c[a]!='\0')
	path = c+a+1;
	else
	path = '\0';
//	printf("%c\n",c[o-4]);
	if((c[0])=='.'&& (c[1])=='/')
	{
					int pid=0,z=0;
				//	printf("o value is %d\n",o);
		//			printf();
					char *st=malloc(sizeof(char)*200);
					char *p[20];
					//int done=0;
					p[0]=c+2;
					p[1]='\0';
                                        char *v=p[0];
					//printf("%s\n",v);
                                        char arr[1024];
					
                                        getcwd(arr,1024);
					z=0;
					while(arr[z]!='\0'){
					st[z]=arr[z];
					z++;
					}
					st[z]='\0';
					//st = "bin";
                                        //stringcat(st,"/");
                                        stringcat(st,v);
					pid=fork();
					if(pid==0)
					{
                                        execve(st,p,envp);
					continue;
					}
					else if(pid>0)	
					{
					int status=0;
					waitpid(pid,&status,0);
					continue;
					}
	
	}
	splitter(c,envp,ps);
	//run(command,path,envp);
	break;
	}
	
	}
return 0;
}
//to change the directory
void cd(char *pathnew,char *env[])
{
	int ret;
	if(*pathnew!='\0')
	{
//	chdir("..");
//	path="/home/stufs1/vnuthalapati/cse506/mypart2/rootfs/bin";
/*	if(*pathnew=='~' && *(pathnew+1)=='\0')
	{
		int flag=0,i=0;
while(!flag)
        {
                if(*env[i]=='H' && *(env[i]+1)== 'O' && *(env[i]+2) == 'M' && *(env[i]+3) == 'E' && *(env[i]+4) == '=')
                {
        //      chdir(env);
                pathnew = env[i]+5;
                flag = 1;
                }
                i++;
        }
ret=chdir(pathnew);

	}
	else{	*/
//	printf("path given to chdir is %s\n",pathnew);
	ret = chdir(pathnew);
	//free(path);
	//char A[1000];
	//char *p=A;
	pathnew='\0';
	if(ret==0)
	{
	//p=getcwd(A,1000);
	//printf("%s\n",p);
	}
	else 
{
	printf("Invalid directory\n");
}
//}
}
else if (*pathnew=='\0'){
/*int flag=0,i=0;
while(!flag)
        {
                if(*env[i]=='H' && *(env[i]+1)== 'O' && *(env[i]+2) == 'M' && *(env[i]+3) == 'E' && *(env[i]+4) == '=')
                {
	//	chdir(env);
                pathnew = env[i]+5;
                flag = 1;
                }
                i++;
        }*/
ret=chdir(pathnew);
}
}

void splitter(char *command,char *env[],char *ps)
{
int i=0,flag=0,k=0,j=0;
char *allcommands[200];
char *temp;
temp=(char*)malloc(sizeof(char)*200);
//printf("in shell--->%d\n",(uint64_t)temp);
while(!flag)
{
temp[k]=command[i];
//printf("%s\n",temp);
	if(command[i+2]=='|' || command[i+1]=='\0')
	{
	allcommands[j]=temp;
	//printf("%s\n",allcommands[j]);
	k=-1;
	j++;
	if(command[i+1]!='\0'){
	temp=(char*)malloc(sizeof(char)*200);
	i+=3;}
//	printf("in shell--->%d\n",(uint64_t)temp);
	}
	if(command[i+1]=='\0')
	{
	flag=1;
	}
k++;
i++;
}
pathcheck(allcommands,j,env,ps);
//}
}

void pathcheck(char *allcommands[],int num,char *env[],char *ps1)
{
int flag=0,i=0,j=0,k=0,m=0;
char *ps[200];
char *temp;
char p[200];
char *path = p;
while(!flag)
	{
		if(*env[i]=='P' && *(env[i]+1)== 'A' && *(env[i]+2) == 'T' && *(env[i]+3) == 'H' && *(env[i]+4) == '=')
		{	
		path = env[i]+5;
		flag = 1;
		}
		i++;
	}
i=0;
ps[0]=path;
temp = (char*)malloc(sizeof(char)*200);
while(1)
	{
	temp[k]=path[i];
	if(path[i+1]==':'||path[i+1]=='\0')
		{
			ps[j]=temp;
			//printf("%s\n",ps[j]);
			if(path[i+1]=='\0')
			break;
			temp = malloc(sizeof(char)*200);
			k=-1;
			j++;
			i++;
		}
	k++;
	i++;
	}
while(m<=j) 
	{
		ps[m]=stringcat(ps[m],"/");
		//printf("%s\n",ps[m]);
		m++;
	}
//printf("total commands are %d\n",num);
//printf("total directories in bin are %d\n",m);

executor(allcommands,env,ps,num,m,ps1);

}
void executor(char* commands[], char * env[],char * ps[],int num,int pssize,char *ps1)
{
	int i=0,t=0;
	int fd[num][2];
	int pid[num],x;
	char * poscom[200];
	char * temp2;
	char *temp4[200];
	char * command;
	int a,b,c,s=0,flag1;//,fl=0;
	int status = 0,done;
	i = num;
	//for(f= 0;f<num;f++)
	//printf("%s\n",commands[f]);
	while(i>=0)
	{
		for(t=0;t<pssize;t++)
		{
		temp4[t]=malloc(sizeof(char)*200);
		temp4[t]=ps[t];
		}
		if(i==num)
		{	//i--;
			if((pid[i]=fork())>0)
			{
				//printf("in sbush\n");
				waitpid(pid[i],&status,0);
				//printf("in sbush\n");
				if(status>0)
				printf("Not Found\n");
				//fprintf(stderr,"parent done %d\n",i);
				break;
				//i = -1;
			}
			else
			{
			//printf("i am first child-->%d\n",i);
			//continue;
			}
		}
		if(i!=num)
		{
			//fprintf(stderr,"here for-->%d\n",i);
			
			command=commands[i];
			//printf("command-->%s\n",command);
			if(i==num-1 && num != 1)
			{
				done = 10;
//				printf("here with hello\n");
				pipe(fd[i]);				
				if(!(pid[i]=fork())) {}
				//continue;
				if(pid[i])
				{
					dup2(fd[i][0],0);
					for(x=num-1;x>=i;x--){
					close(fd[i][0]);
					close(fd[i][1]);}
					waitpid(pid[i],&status,0);
					//printf("status is->%d\n",status);
					if(status>0)
					{
					printf("Not found\n");
					exit(0);
					}
					a=0;
					b=0;
					c=0;
					flag1=0;
					temp2=(char*)malloc(sizeof(char)*200);
					while(!flag1)
					{
						temp2[b]=command[a];
						if(command[a+1]==' '||command[a+1]=='\0')
						{
							poscom[c]=temp2;
							if(command[a+1]=='\0')
							{
								flag1=1;
							}
							temp2=(char*)malloc(sizeof(char)*200);
							b=-1;
							c++;
							a++;
						}
						a++;
						b++;
					}
					poscom[c]='\0';
					done=-1;
					s=0;
					while(1)
					{      done = 10; 
						temp4[s] = stringcat(temp4[s],poscom[0]);
//						printf("here num-1 with-->%s\n",temp4[s]);
						done=execve(temp4[s],poscom,env);
						s++;
					}
					exit(0);
				}	
			}
			if(i==0 && num != 1)
			{
//				printf("here with reader\n");
				dup2(fd[i+1][1],1);
				for(x=num-1;x>i;x--){
				close(fd[i][0]);
				close(fd[i][1]);}
				a=0;
				b=0;
				c=0;
				flag1=0;
				temp2=(char*)malloc(sizeof(char)*200);
				while(!flag1)
				{
					temp2[b]=command[a];
					if(command[a+1]==' '||command[a+1]=='\0')
					{
						poscom[c]=temp2;
						if(command[a+1]=='\0')
						{
							flag1=1;
						}
						temp2=(char*)malloc(sizeof(char)*200);
						b=-1;
						c++;
						a++;
					}
					a++;
					b++;
				}
				poscom[c]='\0';
				s=0;
				while(1)
				{       
				temp4[s] = stringcat(temp4[s],poscom[0]);
				//printf("here num-2 with-->%s\n",temp4[s]);
				done=execve(temp4[s],poscom,env);
				s++;
				}
				exit(0);
			}
			if(i==0 && num == 1)
			{
				a=0;
				b=0;
				c=0;
				flag1=0;
				temp2=(char*)malloc(sizeof(char)*200);
				while(!flag1)
				{
					temp2[b]=command[a];
					if(command[a+1]==' '||command[a+1]=='\0')
					{
						poscom[c]=temp2;
						if(command[a+1]=='\0')
						{
							flag1=1;
						}
						temp2=(char*)malloc(sizeof(char)*200);
						b=-1;
						c++;
						a++;
					}
					a++;
					b++;
				}
				poscom[c]='\0';
		/*		if((!strngcmp(poscom[0],"echo")&&!strngcmp(poscom[1],"$PATH")) ||(!strngcmp(poscom[0],"echo")&&!strngcmp(poscom[1],"$PS1")))
				{  
					int z=0; 
					if(!strngcmp(poscom[1],"$PATH"))
					{
						 while(!fl)
        					{
					                if(*env[z]=='P' && *(env[z]+1)== 'A' && *(env[z]+2) == 'T' && *(env[z]+3) == 'H' && *(env[z]+4) == '=')
                					{
                						printf("%s\n",env[z]);
                						fl = 1;
                					}
                					z++;
        					}

					}
					if(!strngcmp(poscom[1],"$PS1"))
					{
						printf("%s\n",ps1);
					}
				}*/
			//	done=-1;
				//s=0;
				//printf("\ninside--->%s\n",command);
//				else
				{
				while(1)
				{       
					temp4[s] = stringcat(temp4[s],poscom[0]);
					done=execve(temp4[s],poscom,env);
//					if(done<0)
//					break;
					s++;
				}
				}
				exit(0);
			}
			if(i != num-1 && i != 0 && num != 1)
			{
				pipe(fd[i]);
				done = 10;
				if(!(pid[i]=fork())){}
				//continue;
				if(pid[i])
				{
					//fprintf(stderr,"here for-->%s,%d,read-->%d,write--->%d\n",command,i,i,i+1);
					dup2(fd[i][0],0);
					dup2(fd[i+1][1],1);
					for(x=num-1;x>=i;x--){
					close(fd[i][0]);
					close(fd[i][1]);}
					waitpid(pid[i],&status,0);
					if(done==-1)
					exit(0);
					a=0;
					b=0;
					c=0;
					flag1=0;
					temp2=(char*)malloc(sizeof(char)*200);
					while(!flag1)
					{
						temp2[b]=command[a];
						if(command[a+1]==' '||command[a+1]=='\0')
						{
							poscom[c]=temp2;
							//free(temp2);
							if(command[a+1]=='\0')
							{
								flag1=1;
							}
							//free(temp2);
							temp2=(char*)malloc(sizeof(char)*200);
							b=-1;
							c++;
							a++;
						}
						a++;
						b++;
					}
			//		free(temp2);
					poscom[c]='\0';
				//	done=-1;
					s=0;
					while(1)
					{       
						temp4[s] = stringcat(temp4[s],poscom[0]);
						//poscom[0] = temp4[s];
						//fprintf(stderr,"before exec\n");
				done=execve(temp4[s],poscom,env);
				// printf("ret value is %d\n",done);
						//fprintf(stderr,"after exec\n");
						s++;
					}
			//		printf("command not found\n");
					exit(0);
				}
			}
			
		}
		
		//printf("i value is-->%d\n",i);
	i--;
	}
	//printf("outside loop\n");
}
//code for executing scripts
void scriptex(int fd,char *envp[],char *ps)
{
//enum { O_RDONLY = 0, O_WRONLY = 1, O_RDWR = 2, O_CREAT = 64 };
//enum { SEEK_SET = 0, SEEK_CUR = 1, SEEK_END = 2 };
ssize_t data;
int i=0,j=0,k=0,flag=0;
char *lines[30];
off_t offset=0;
char *buf=malloc(sizeof(char*)*200);
char *temp=malloc(sizeof(char*)*200);
//printf("in scriptex\n");

while(!flag)
{
	//offset++;
	//printf("%d\n",offset);
	lseek(fd,offset,1);
	data=read(fd,buf,1);
//	printf("buf is %s\n",buf);
	if(data==0)
	{
	break;
	} 
	//printf("%c",*buf);
	temp[i]=*buf;
	//printf("%c\n",temp[i]);
	if(temp[i]=='\n')
	{
	lines[j]=temp;
	*(lines[j]+i)='\0';
	//printf("%s\n",temp);
	//printf("%s",lines[j]);
	//free(temp);
	temp=malloc(sizeof(char*)*200);
	i=-1;
	j++;
	} 
	//printf("%s",lines[j]);
//	offset++;
	i++;
}
flag=0;
k=0;i=0;
char *temp2=lines[k];
if((temp2[i]=='#') && (temp2[i+1]=='!'))
{
	k++;
	//temp2=lines[k];
	while(k<=j-1)
	{
	temp2=lines[k];
//	printf("number %d, command %s, temp %s\n",k,lines[k],temp2);
		if((temp2[i]=='#')||(temp2[i]=='\0'))
		{	
		k++;
		}
		else
		{
		//printf("the command is%s\n",lines[k]);
		splitter(lines[k],envp,ps);
		k++;
		}
	}	
}
else
{
printf("Invalid script file\n");
}
}

char *stringcat(char *s,char *t)
{
int i=0,j=0;
while(s[i]!='\0')
{
j++;
i++;
}
for(i=0;t[i]!='\0';i++)
{
s[j]=t[i];
j++;
}
s[j]='\0';
return s;
}

int strngcmp(char *s,char *t)
{
int i=0;
char temp1;
char temp2;
for(i=0;s[i]!='\0';i++) 
{     
temp1=s[i];
temp2=t[i]; 
        if(temp1>temp2)
        {
        return 1;
        }
        else if(temp1<temp2) 
        {
        return -1; 
        }
}   
return 0;
}

