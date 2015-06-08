#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[],char *envp[])
{
	int num=0,i=0;
	if(argc<2)
	printf("Time Invalid");
	else
	{
		while(*(argv[1]+i)!='\0')
		{
			num = (*(argv[1]+i)-48)+num*10;
			i++;
		}
		//printf("num is-->%d\n",num);
		sleep(num);
	}
	return 0;
	//sleep(
}
