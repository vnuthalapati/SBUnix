//#include<sys/sbunix.h>
#include<stdarg.h>
#include<sys/defs.h>
#include<stdio.h>
#include<stdlib.h>
int printf(const char *format, ...) {
        va_list val;
        char* s;
        char c;
        char A[50];
	char F[30];
        char *ch;
        int xi,printed=0;
        int i, rem, len = 0, n;
         char *temp;
        int value[30];
        char cha[30];
        int counter=0,index=0,a=0,q=0;
	uint64_t quo=16,base=16;
        va_start(val, format);
        while(*format) {
		for(q=0;q<50;q++)
		A[q]='\0';
                if(*format=='%')
                {
                        format++;
                        switch(*format)
                                {
                                 case 's':
                                s = va_arg(val,char*);
                                while(*s!='\0')
                                        {
                                        write(1,s, 1);
                                        s++;
                                        }
                                format++;
                                break;
			        case 'p':
                                F[0]='0';
                                F[1]='x';
                                F[2]='\0';
                                ch=F;
                                while(*ch!='\0')
                                {
                                        write(1,ch,1);
                                        ch++;
                                }
				quo=16;
              //                  num=0;
                                a=0;
                                index=0;
                                cha[30]='\0';
                                uint64_t num1 = va_arg(val,uint64_t);
				if(num1>15) {
				uint64_t prevquo = quo;
                                while(quo<num1 && quo>0)
                                {
				prevquo = quo;
                                quo=quo*base;
                                index++;
                                }
				if(quo==0){
				quo = prevquo;
				}else{
				index++; }
		//		printf("after loop");
                                for(counter=0;counter<=index;counter++)
                                {
                                a=num1/quo;
                                num1=num1%quo;
                                quo=quo/base;
                                value[counter]=a;
                                }
				}else{
				value[0] = num1;
				}
                                for(counter=0;counter<=index;counter++)
                                {
                                switch (value[counter])
                                {
                                case 15:
                                cha[counter]='F';
                                break;
                                case 14:
                                cha[counter]='E';
                                break;
				case 13:
        			cha[counter]='D';
        			break;
				case 12:
        			cha[counter]='C';
        			break;
				case 11:
        			cha[counter]='B';
        			break;
				
				case 10:
        			cha[counter]='A';
        			break;
				case 9:
        			cha[counter]='9';
        			break;
				case 8:
       	 			cha[counter]='8';
        			break;
				case 7:
        			cha[counter]='7';
        			break;
				case 6:
        			cha[counter]='6';
        			break;
				case 5:
        			cha[counter]='5';
        			break;
				case 4:
        			cha[counter]='4';
        			break;
				case 3:
        			cha[counter]='3';
        			break;
				case 2:
        			cha[counter]='2';
        			break;
				case 1:
        			cha[counter]='1';
        			break;
				case 0:
        			cha[counter]='0';
        			break;
				}
				}
				for(counter=0;counter<=index;counter++)
				{
				write(1,&cha[counter],1);
				}
				format++;
				break;
                                case 'd':
				rem = 0;
				len = 0;
                                xi = va_arg(val,int);
                                if(xi<0)
                                {
                                char c='-';
                                write(1,&c,1);
                                xi=-xi;
                                }
                                n=xi;
                                if(n!=0)
                                {
                                        while (n != 0)
                                        {
                                        len++;
                                        n /= 10;
                                        }
                                }
                                else
                                        {
                                        len=1;
                                        }
                                for (i = 0; i < len; i++)
                                {
                                rem = xi% 10;
                                xi = xi / 10;
                                A[len - (i + 1)] = rem + '0';
                                  }
                                A[len]='\0';
                                temp = A;
                                while(*temp!='\0')
                                        {
                                        write(1,temp,1);
                                        temp++;
                                        }

                                format++;
                                break;
                                case 'c':
                                c = (char)va_arg(val,int);
                                write(1,&c, 1);
                                format++;
                                break;
                                case 'x':
			//	quo=1;
				quo=16;
			//	num=0;
                                a=0;
                                index=0;
                                cha[30]='\0';
                         /*       num=(uint64_t)va_arg(val,uint64_t);
                                while(num>quo)
                                {
                                quo=quo*16;
                                index++;
                                }
                                quo=quo/16;
                                for(counter=0;counter<=index;counter++)
                                {
                                a=num/quo;
                                        num=num%quo;
                                quo=quo/16;
                                value[counter]=a;
                                   }*/
				 uint64_t num2 = va_arg(val,uint64_t);
				if(num2>15) {
                                uint64_t prevquo1 = quo;
                                while(quo<num2 && quo>0)
                                {
                                prevquo1 = quo;
                                quo=quo*base;
                                index++;
                                }
                                if(quo==0)
				{
                                quo = prevquo1;
				}else {
				index++;
				}
			//	index++;
                //              printf("after loop");
                                for(counter=0;counter<=index;counter++)
                                {
                                a=num2/quo;
                                num2=num2%quo;
                                quo=quo/base;
                                value[counter]=a;
                                }
				}else{
				value[0] = num2;
				}
                                for(counter=0;counter<=index;counter++)
                                {
                                switch (value[counter])
                                {
                                case 15:
                                cha[counter]='F';
                                break;
				case 14:
        			cha[counter]='E';
        			break;
				case 13:
			        cha[counter]='D';
			        break;
				case 12:
			        cha[counter]='C';
			        break;
				case 11:
        			cha[counter]='B';
        			break;
				case 10:
        			cha[counter]='A';
        			break;
				case 9:
        			cha[counter]='9';
        			break;
				case 8:
        			cha[counter]='8';
        			break;
				case 7:
        			cha[counter]='7';
        			break;
				case 6:
        			cha[counter]='6';
        			break;
				case 5:
        			cha[counter]='5';
			        break;
				case 4:
			        cha[counter]='4';
			        break;
				case 3:	
			        cha[counter]='3';
			        break;
				case 2:
			        cha[counter]='2';
			        break;
				case 1:
				cha[counter]='1';
        			break;
				case 0:
			        cha[counter]='0';
			        break;
				}
//printf("%d\n",value[counter]);
				}
				for(counter=0;counter<=index;counter++)
				{
				write(1,&cha[counter],1);
//printf("%c\n",cha[counter]);
				}

				format++;
				break;
                 		}
	//	update_cursor(x,y);
                }
                else{
                write(1,format, 1);
               // ++printed;
                ++format;
                }
//	update_cursor(y,x);
        }

        return printed;
} 
