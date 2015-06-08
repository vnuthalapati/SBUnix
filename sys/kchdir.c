#include<sys/kernlib.h>
#include<sys/tarfs.h>
#include<sys/tarfshandling.h>
#include<sys/string.h>
#include<sys/sbunix.h>
char *allcommands[200];
int ksplitter(char *command)
{
int i=0,flag=0,k=0,j=0;
//char *allcommands[200];
char *temp;
temp=(char*)kmalloc(sizeof(char)*200);
//printf("in shell--->%d\n",(uint64_t)temp);
while(!flag)
{
temp[k]=command[i];
//printf("%s\n",temp);
        if(command[i+1]=='/' || command[i]=='\0')
        {
        allcommands[j]=temp;
        //printf("%s\n",allcommands[j]);
        k=-1;
        j++;
        if(command[i]!='\0'){
        temp=(char*)kmalloc(sizeof(char)*200);
        i+=1;}
//      printf("in shell--->%d\n",(uint64_t)temp);
        }
        if(command[i]=='\0')
        {
        flag=1;
        }
k++;
i++;
}
return j-1;
}

int change_dir(char *path)
{
	int i=0,x=0,var=0,count=0,j=0,k=0,l=2;
	char *name=cur_proc->cwd;
	char B[1000];
	char *temp_cwd=B;
	while(name[i]!='\0')
	{
		temp_cwd[i] = name[i];
		i++;
	}
	temp_cwd[i]='\0';
	i=0;
	if(path[0]=='~' && path[1] =='/'){
		while(path[l]!='\0'){
			path[i]=path[l];
			i++;
			l++;
		}
		path[i]='\0';	
		i=0;
	        for(;i<1000;i++)
        	temp_cwd[i]='\0';
	}
	if((path[0]=='~' && path[1]=='\0')||path[0]=='\0'){
	
//	char *str ="bin/\0";
	i=0;
	for(;i<1000;i++)
	temp_cwd[i]='\0';
/*		i=0;
		while(str[i]!='\0'){
		temp_cwd[i] = str[i];
		i++;
		}*/
	//	temp_cwd = "";
	//	kprintf("tilt set %s\n",temp_cwd);
	}
	else
	{
		char *st = "5";
		char *dot = "..";
		char *dot2 = ".";
		char C[2];
		char *sl = C;
		C[0]='/';
		C[1]='\0';
		j=ksplitter(path);
		for(x=0;x<=j;x++){
			if(strngcmp(allcommands[x],dot)==0)
			{	
				i=0;
				count=0;
				var=0;
				while(temp_cwd[i]!='\0')
				{	
					if(temp_cwd[i]=='/')
					{
						count++;
					}
					i++;
				}
				i=0;
				if(count==1 || count==0){
                                         for(k=0;k<1000;k++){
                                                temp_cwd[k]='\0';
                                        }
                                 //       break;
                                }
				else{
					char *temp6=(char*)kmalloc(200);
					while(temp_cwd[i]!='\0')
					{	
						if(count==1){
							 for(k=0;k<1000;k++){
							        temp_cwd[k]='\0';
							}
						break;
						}
						if(temp_cwd[i]=='/')
						{
							var++;
							if(var == count-1)
							{
								break;
							}
						}
						temp6[i]= temp_cwd[i];
					i++;
					}
					temp6[i] ='/';
					i++;
					i=0;
				        while(temp6[i]!='\0'){
				        temp_cwd[i]= temp6[i];
				        i++;
			        }
			        temp_cwd[i]='\0';
//				kprintf("temp cwd is %s\n",temp_cwd);
				}
			}else if(strngcmp(allcommands[x],dot2)==0)
                        {
				
			}
			else
			{
				stringcat(temp_cwd,allcommands[x]);
				stringcat(temp_cwd,sl);
	//			kprintf("temp passed to traverse is%s\n",temp_cwd);
				struct posix_header_ustar *phu1 = (struct posix_header_ustar*)traverse_file(temp_cwd);
				if(phu1 !=NULL)
				{
					if(scmp((char*)(phu1->typeflag),st)==0){

					}else{
					return -1;
					}
				
				}
				else
				{
					//temp_cwd = cur_proc->cwd;
					return -1;
				}	

			}
		}
	}
	i=0;
	while(temp_cwd[i]!='\0'){
	name[i]= temp_cwd[i];
	i++;
	}
	//kprintf("after name set--->%s\n",name);
	name[i]='\0';
//	kprintf("in chdir curproc is %s\n",cur_proc->cwd);
	
return 0;

}


int current_dir(uint64_t temp,uint64_t count)
{	
	int i=0;
	char *name= (char*)kmalloc(count);
	for(;i<count;i++){
		name[i]='\0';
	}
	i=0;
	 while(cur_proc->cwd[i]!='\0')
        {
               // name[i] = cur_proc->cwd[i];
                i++;
        }
       // name[i]='\0';
        if(i>count)
        {
        return -1;
        }
	i=0;
	//=(char*)cur_proc->cwd
//	kprintf("curproc id  %d  cwd is %s\n",cur_proc->id,cur_proc->cwd);
	while(cur_proc->cwd[i]!='\0')
	{
		name[i] = cur_proc->cwd[i];
		i++;
	}
	name[i]='\0';
	i=0;
//	kprintf("in get cwd %s\n",name);
		
	char *s = (char*)temp;
	while(name[i]!='\0')
	{
		*s = name[i];
		s++;
		i++;
	}
	s[i]='\0';
//	char *c =(char*)temp;
//	kprintf("return cwd %s\n",c);
return 0;
}

