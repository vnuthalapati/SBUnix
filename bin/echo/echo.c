#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
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
int main(int argc,char *argv[],char *envp[])
{
	int fl=0,i=0;
	char *ps1 = "vivek";
	if(argc>=2)
	{
		//printf("argv1 is--->%s\n",argv[1]);
		if((!strngcmp(argv[1],"$PATH")) || (!strngcmp(argv[1],"$PS1")))
        	{
                	int z=0;
                       	if(!strngcmp(argv[1],"$PATH"))
                       	{
				//printf("entered path loop\n");
                        	while(!fl)
                                {
                                	if(*envp[z]=='P' && *(envp[z]+1)== 'A' && *(envp[z]+2) == 'T' && *(envp[z]+3) == 'H' && *(envp[z]+4) == '=')
                                        {
				//	printf("entered path loop\n");
                                        	printf("%s\n",envp[z]);
                                                fl = 1;
                                        }
                                        z++;
                                }

                        }
             		if(!strngcmp(argv[1],"$PS1"))
           		{
                		printf("%s\n",ps1);
                	}
         	}                       
	
		else if(argc>=2)
		{
			i =1;
			while(i<argc)
			{
				printf("%s ",argv[i]);
				i++;
			}
			printf("\n");
		}
	}
	else
		printf("\n");
	return 0;
}
