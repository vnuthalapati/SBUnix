#include<sys/sbunix.h>
#include<sys/pmap.h>
#include<sys/kernlib.h>
void* myalloc(size_t size,int create);
uint64_t address=0;
uint64_t ret_address=0;
//int counter=0;
int increment = 0;
//struct mylist *list=(struct mylist*)myalloc(sizeof(struct mylist),1);
static struct mylist *list=&(struct mylist){.address=0,.size=0,.status = 0,.next=NULL};
void* kmalloc(size_t size) 
{
int size1;
size1 = size%8;
if(size1!=0){
size = size+8;
size = size-size%8;
}
return (void*)myalloc(size,0);
}
void* myalloc(size_t size,int create) 
{	
	int size2;
	size2 = size%8;
	if(size2>0){
	size = size+8;
	size = size-size%8;
	}
	int numpages,i,rem;
	//allocating memory for structures
	if(create) {
		if(increment  == 0 || increment+size >=4096) {		
		ret_address = page_alloc();
		increment = 0;
		increment  = increment + size;
		return (void*)ret_address;
		} else {
		ret_address = ret_address +size;
		increment = increment +size;
		return (void*)ret_address;
		}

	}   
	struct mylist *temp;
	struct mylist *prev;
	prev = list;
	temp = list;
	while(temp!=NULL) {
		if(temp->status == 0 && size<=temp->size) {
//			kprintf("i am inside\n");
			struct mylist *new =(struct mylist*)myalloc(sizeof(struct mylist),1);
//			struct mylist *new2 = (struct mylist*)myalloc(sizeof(struct mylist),1);
			new->address = temp->address;
			new->size = size;
		//	new->next = new2;
			prev->next = new;
			new->status = 1;
			if(temp->size-size>0) {
			struct mylist *new2 = (struct mylist*)myalloc(sizeof(struct mylist),1);
			new->next = new2;
			new2->address = new->address+new->size;
			new2->status = 0;
			new2->next = temp->next;
			new2->size = temp->size - (new->size);
			}else {
			new->next = temp->next;
			}
			return (void*)new->address;
		}
		prev = temp;
		temp = temp->next;
	}
	temp = prev;
	if(size<=4096){
	struct mylist *new = (struct mylist*)myalloc(sizeof(struct mylist),1);
	struct mylist *new2 = (struct mylist*)myalloc(sizeof(struct mylist),1);
	temp->next = new;
	new->address = page_alloc();
	new->size = size;
	new->status = 1;
	new->next = new2;
	new2->address = new->address + new->size;
	new2->size = 4096-(new->size);
	new2->status = 0;
	new2->next = NULL;
	return (void*)new->address;
	}else{
	numpages = size / 4096;
        rem = size % 4096;
	struct mylist *new = (struct mylist*)myalloc(sizeof(struct mylist),1);
	temp->next = new;
	new->address = 0;
        struct mylist *new2 = (struct mylist*)myalloc(sizeof(struct mylist),1);	
        new->address = page_alloc();
	for(i=1;i<=numpages;i++){
		page_alloc();
	}		
        new->size = size;
        new->status = 1;
        new->next = new2;
        new2->address = new->address + new->size;
        new2->size = 4096-(rem);
        new2->status = 0;
        new2->next = NULL;
	return (void*)new->address;
	}
/*	struct mylist *temp;
	temp = list;
	if(temp->next!= NULL) {
		//if a free block is present in the list,returning that address
		while(temp->next!=NULL) {		
			if(temp->size == (unsigned long)size && temp->status == 0) {
				return (void*)temp->address;
			}
			temp = temp->next;
		}
		//Allocating a block from the existing page.
		if(counter+size<=4096) {
			struct mylist *new =(struct mylist*) myalloc(sizeof(struct mylist),1);
			new->address = (unsigned long)address;
			new->size = (unsigned long)size;
			new->status = 1;
			new->next = NULL;
			temp->next = new;
			counter = counter + (int)size;
			address = (uint64_t)new->address + (uint64_t)size;
			return (void*)new->address;
		}
		//Allocating a block from a new page since current page has no free block 
		if(counter+size>4096) {
			counter = 0;
			struct mylist *new = (struct mylist*)myalloc(sizeof(struct mylist),1);
        		new->address = (unsigned long)page_alloc();
	        	new->next = NULL;
	        	new->status = 1;
        		new->size = (unsigned long)size;
	        	temp->next = new;
        		address =(uint64_t) new->address+(uint64_t)size;
	        	counter = counter + (int)size;
	        	return (void*)new->address;
		}
		
	}
	temp = list;
	struct mylist *new =(struct mylist*) myalloc(sizeof(struct mylist),1);
	new->address = page_alloc();
	new->next = NULL;
	new->status = 1;
	new->size = size;
	temp->next = new; 
	address = new->address+size;
	counter = counter + size;
	return (void*)new->address;*/
}

void free(void *add) {
	uint64_t value = (uint64_t)add;
	struct mylist *temp = (struct mylist*)myalloc(sizeof(struct mylist),1);
	temp = list;
	while(temp->next!=NULL) {
		if(temp->address == value){
		break;
		}
		temp = temp->next;
	} 
	temp->status = 0;
}
