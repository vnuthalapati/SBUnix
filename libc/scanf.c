#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
//int tostring(char a[]);
int scanf(const char *format, ...)
{
	va_list val;
//	char* s;
//	int x ;
	int l=0;	
	char * buf,A[1024],B[1024],C[1024],D[1024],E[1024],*string='\0',*new='\0',*new1='\0',*new2='\0';
	char * temp_new1,*temp_new2;
	while(l<1024)
	{
	B[l]='\0';
	l++;
	}
	l=0;
	while(l<1024)
	{
A[l]='\0';
l++;
	}
	l=0;
	  while(l<1024)
        {
C[l]='\0';
l++;
        }
	l=0;
       while(l<1024)
        {
D[l]='\0';
l++;
        }
	l=0;
       while(l<1024)
        {
E[l]='\0';
l++;
        }

//	size_t readsize=0;
	int cha[100];
	int ret=0,num1=0,num=0,k=0,flag=0,z=0;
	int *x,*y;//g=1;
	buf = B;
//	char dummy;
	string = A;
	new=C;
	new1=D;
	new2=E;
	//int value[30];
	int counter=0,i=0,j;
	va_start(val, format);
	while(*format) 
	{
		if(*format=='%')
		{
			format++;
			switch(*format)
			{
				case 's':
					//printf("inside s\n");
					while(z<1024)
					{	
					B[z]='\0';
					z++;
					}
				
					string = va_arg(val,char*);
					*string	= '\0';
				//	while(*buf != '\n')
				//	{
						read(0,buf,1024);
						while(*buf!='\n'){
						*(string)= *(buf);
						string++;
						buf++;
					//	readsize++;
					}
					*(string) = '\0';
					//printf("string is--:%s\n",string);
					format++;
				break;
				case 'c':
					//printf("inside c\n");
					//*new='\0';
				//	g= 1;
					new = va_arg(val,char*);
				//	*string='\0';
					*new = '\0';
					//read(0,buf,1);
				//	while(*buf != '\n')
                                        {
                                                read(0,buf,2);
					//	if(g==1)
						while(*buf!='\n'){
                                                *(new) = *buf;
						buf++;
						}
					//	g++;
                                          //      readsize++;
                                        }

				//	printf("buf is-->%c",*buf);
	//				*(new) = *buf;
					*(new+1) = '\0';
					//printf("string is--:%s\n",string);
					//read(0,&dummy,1);
					format++;
				break;
				case 'd':
			//	char * temp_new1;
				//	*x=0;
					while(z<1024)
                                        {
                                        B[z]='\0';
                                        z++;
                                        }
					y = va_arg(val,int*);
					*y=0;
                                       // while(*buf != '\n')
                                       // {
				temp_new1 = new1;
                                                read(0,buf,1024);
						while(*buf!='\n'){
                                                *(temp_new1) = *buf;
						temp_new1++;
                                                buf++;
                                                }

                                               // *(new1+readsize) = *buf;
                                               // readsize++;
                                        
                                        *(temp_new1) = '\0';
			//		printf("%s\n",new1);
					if(new1[0]=='-')
                                                {
                                                k++;
                                                }

					while(new1[k]!='\0')
					{
						
						num = num*10 + new1[k] - 48;
						k++;
					}
					//printf("num--->%d,k--->%d\n",num,k);
					//printf("%d\n",num);
					num1=num;
					if(new1[0]=='-')
					{
					//	num=-num;
					
				/*	x[0]='-';
					
					*(x+1)=num;*/
					int temp=num1;
					//printf("%d\n",temp);
					num1=0-temp;
					//printf("%d\n",num);
					*y=num1;
					}
					else{
					*y=num1;
					}
			//		printf("in scanf--->%d\n",num1);
					format++;
				break;
				case 'x':
				//	*x=0;
		
                                        x = va_arg(val,int*);
					*x=0;
					while(z<1024)
                                        {
                                        B[z]='\0';
                                        z++;
                                        }
                                       /* while(*buf != '\n')
                                        {
                                                read(0,buf,1);
                                                *(new2+readsize) = *buf;
                                                readsize++;
                                        }*/	temp_new2 = new2;
						read(0,buf,1024);
                                                while(*buf!='\n'){
                                                *(temp_new2) = *buf;
                                                temp_new2++;
                                                buf++;
                                                }

                                        *(temp_new2) = '\0';
					while(new2[counter]!='\0'&& !flag)
					{
					switch (new2[counter])
                                {
                                case 'F':
                                cha[counter]=15;
                                break;

				case 'f':
				cha[counter]=15;
				break;
case 'E':
        cha[counter]=14;
        break;
case 'e':
	cha[counter]=14;
        break;
case 'D':
        cha[counter]=13;
        break;
case 'd':
        cha[counter]=13;
        break;
case 'c':
        cha[counter]=12;
        break;
case 'b':
        cha[counter]=11;
        break;
case 'a':
        cha[counter]=10;
        break;
case 'C':
        cha[counter]=12;
        break;
case 'B':
        cha[counter]=11;
        break;
case 'A':
        cha[counter]=10;
        break;
case '9':
        cha[counter]=9;
        break;
case '8':
        cha[counter]=8;
        break;
case'7':
        cha[counter]=7;
	break;

case '6':
        cha[counter]=6;
        break;
case '5':
        cha[counter]=5;
        break;
case '4':
        cha[counter]=4;
        break;
case '3':
        cha[counter]=3;
        break;
case '2':
        cha[counter]=2;
        break;
case '1':
        cha[counter]=1;
        break;
case '0':
        cha[counter]=0;
        break;
default:
	flag=1;
	counter--;
	break;
	}
counter++;
}
//cha[k]='\0';
num=cha[counter-1];
j=16;
                                        for(i=counter-2;i>=0;i--)
                                        {
                                                num =num+cha[i]*j ;
                                                j=j*16;
                                        }
                                      *x=num;
                                        format++;
                                        break;

			}
		}
	}
	va_end(val);
	format = NULL;
	return ret;	
}
