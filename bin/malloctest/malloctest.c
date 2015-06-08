#include<stdlib.h>
#include<stdio.h>
int main(int argc, char * argv[], char * envp[])
{
	char * str =(char*)malloc(100);
	int i=0;
	while(i<60){
	str[i]='a';
	i++;
	}
	printf("%s\n",str);
	 printf("address is %p\n",str);
	free(str);
	char *st = (char*)malloc(50);
	i=0;
	while(i<50){
        st[i]='a';
        i++;
        }
	 printf("%s\n",st);
         printf("address is %p\n",st);
	free(st);

	
}
