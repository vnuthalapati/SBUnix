#include<sys/string.h>
void stringcpy(char *str,char *ten){
char *s=str;
char *t=ten;
int i=0;
while((s[i]=t[i])!='\0')
{
i++;
}
}

int strngcmp(char *s,char *t)
{
int i=0,slen=0,tlen=0;
char temp1;
char temp2;
for(i=0;s[i]!='\0';i++)
{
        slen++;
}
for(i=0;t[i]!='\0';i++)
{
        tlen++;
}
if(slen!=tlen){
return -1;
}
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

int scmp(char *s,char *t)
{
int i=0;//,slen=0,tlen=0;
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

int stringcat(char *s,char *t)
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
return 0;
}


