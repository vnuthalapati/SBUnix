#include<sys/sbunix.h>
#include<sys/kernlib.h>
#define NO 0
extern void update_cursor(int row, int col);
int shift_flag=0;
int esc_flag=0;
int ctrl_flag=0,ctrl_flag2=0;
//extern int writedisp(int fd, const char* add, int size);
unsigned char kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,
};
static uint8_t shiftmap[256] =
{
NO, 033, '!', '@', '#', '$', '%', '^', 
'&', '*', '(', ')', '_', '+', '\b', '\t',
'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
'O', 'P', '{', '}', '\n', NO, 'A', 'S',
'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
'"', '~', NO, '|', 'Z', 'X', 'C', 'V',
'B', 'N', 'M', '<', '>', '?', NO, '*', 
NO, ' ', NO, NO, NO, NO, NO, NO,
NO, NO, NO, NO, NO, NO, NO, '7', 
'8', '9', '-', '4', '5', '6', '+', '1',
'2', '3', '0', '.',
};
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}
static inline void outb(uint16_t port, uint8_t val)
{
__asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
extern void kbd_handler()
{
	outb(0x20,0x20);
//	int ctrl_flag2=0;
	unsigned char scancode = inb(0x60);
	unsigned char val;
	val = kbdus[scancode];
//	printf("val is %x\n",val);
	if(scancode==0x2A || scancode==0xB6)
	{	
		shift_flag=1;
	}
/*	if(scancode==0x01)
	{      
	//	printf("pressed");
		esc_flag=1;
	}
	if(scancode==0x81)
	{	
	//	printf("released");
		esc_flag=0;
	}
	//left ctrl=0x1D
	//left alt=0x38
	if(scancode==0x1D || scancode==0x38)
	{
		ctrl_flag2=1;
	//	printf("ctrl pressed");
	}*/
	if(shift_flag==1)
	{
		val=shiftmap[scancode];
	}
	if(scancode== 0xAA || scancode==0x36)
	{
		shift_flag=0;
//		printf("shift released");
	}
	//left alt=0xB8
	//left ctrl=0x9D
/*	if(scancode== 0x9D || scancode==0xB8)
	{
//		ctrl_flag=0;
		ctrl_flag2=0;
//	printf("in release");
	}*/
	if (scancode & 0x80){}
	if((scancode!=0x2A) && !(scancode & 0x80) && (scancode!=0x1D) && (scancode!=0x38))
	{
//	printf("esc flag value is %d\n",esc_flag);	
/*	if(ctrl_flag2==1)
        	{
		//ctrl_flag2=0;
        	volatile char *vi=(volatile char*)0xB8F9C;
        	*vi='^';
        	*(vi+1)=0x30;
			if(val == '\n'){
			val = 'n';
			}
        	*(vi+2)=val;
        	*(vi+3)=0x30;
        	}
	else if(esc_flag==1)
		{
	//	printf("entered condition\n");
		 volatile char *vi=(volatile char*)0xB8F9C;
                *vi='e';
                *(vi+1)=0x30;
		 *(vi+2)='s';
                *(vi+3)=0x30;
		}
	else{
		if(val=='\b')
		{
		 volatile char *vi=(volatile char*)0xB8F9C;
                *vi='\\';
                *(vi+1)=0x30;
                *(vi+2)='b';
                *(vi+3)=0x30;
		}
		else if(val=='\t')
		{
		 volatile char *vi=(volatile char*)0xB8F9C;		
                *vi='\\';
                *(vi+1)=0x30;
                *(vi+2)='t'; 
                *(vi+3)=0x30;
		}
		else if(val=='\n')
		{
                 volatile char *vi=(volatile char*)0xB8F9C;
                *vi='\\';
                *(vi+1)=0x30;
                *(vi+2)='n';
                *(vi+3)=0x30;
		}
		else if(val=='\r')
                {
                 volatile char *vi=(volatile char*)0xB8F9C;
                *vi='\\';
                *(vi+1)=0x30;
                *(vi+2)='r';
                *(vi+3)=0x30;
                }
		else{
		volatile char *vi=(volatile char*)0xB8F9C;
	//	printf("in else");
		kprintf("%c",val);
		*vi=val;
                *(vi+1)=0x30;
                *(vi+2)=' ';
                *(vi+3)=0x30;
		}
	}
	}*/
	if(val=='\b')
	{
	if(curr_pos>0)
	kprintf("%c",val);
	else
	curr_pos=0;
	}
	else
	{
	kprintf("%c",val);
	}
	input(val);
	
}

}	
