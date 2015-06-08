#include <sys/pmap.h>
#include <sys/tarfs.h>
#include <sys/sbunix.h>
#include <sys/tarfshandling.h>
#include <sys/kernlib.h>
//int elf_index = 1;
static int procid = 1;
struct process* process_setup(uint64_t physbase,uint64_t physfree,char *filename)
{
totalprocs[curproc_count] = (struct process*)proc_create(filename);
//kprintf("%d\n",totalprocs[curproc_count]->id);
proc_setup_table(totalprocs[curproc_count],filename);
if(totalprocs[curproc_count]->pml4e!=NULL){
loadcr3(katopa((uint64_t)totalprocs[curproc_count]->pml4e),(uint64_t)physbase,(uint64_t)physfree);
elf_copy(totalprocs[curproc_count],filename); 
setup_stack(totalprocs[curproc_count]);
return totalprocs[curproc_count];
}
else{
	totalprocs[curproc_count]->state=ENV_KILLED;
	totalprocs[curproc_count]->status=0;
	return NULL;
}
}

struct process* process_setup_exec(uint64_t physbase,uint64_t physfree,char *filename)
{
totalprocs[curproc_count] = (struct process*)proc_create(filename);
//kprintf("%d\n",totalprocs[curproc_count]->id);
proc_setup_table(totalprocs[curproc_count],filename);
if(totalprocs[curproc_count]->pml4e!=NULL){
loadcr3(katopa((uint64_t)totalprocs[curproc_count]->pml4e),(uint64_t)physbase,(uint64_t)physfree);
elf_copy(totalprocs[curproc_count],filename);

//setup_stack(totalprocs[curproc_count]);
return totalprocs[curproc_count];
}
else{
        totalprocs[curproc_count]->state=ENV_KILLED;
        totalprocs[curproc_count]->status=0;
        return NULL;
}
}



struct process * proc_create(char *filename){
/*	int i=0,index = 0;
	uint64_t proc_address;
	struct process * temp = head;
	for(i=0 ; i<nprocs ; i++)
	{
		/proif(procs[i].status==0)
		{
			index = i;
			break;
		}
		else
		continue;
	}
	
//	if(temp!=NULL)
	while(temp->next!=head)
	temp = temp->next;
	temp->next = procs+index;
	procs[index].status = 1;
	procs[index].id = procid;
	procid++;
	procs[index].state = ENV_RUNNABLE;
	procs[index].pml4e = NULL;
	procs[index].next = head;
	//procs[index].tf = (trap_frame)NULL;
	procs[index].kstack = 0;
	procs[index].ustack = 0;
	proc_address = (uint64_t)procs + sizeof(struct process)*index;
	return (struct process*)(proc_address);*/
	int i=0;
	struct process *temp,*myproc;
	temp = head;
	myproc = (struct process*)(kmalloc(sizeof(struct process)));
	myproc->status = 1;
	myproc->id = procid;
	procid++;
	myproc->state = ENV_RUNNABLE;
	while(filename[i]!='\0'){
	myproc->proc_name[i] = filename[i];
	i++;
	}
	myproc->proc_name[i]='\0';
	myproc->pml4e = NULL;
	myproc->kstack = 0;
	myproc->ustack = 0;
//	myproc->cwd = "bin/";
//	myproc->cwd[0] = 'b';
//	myproc->cwd[1] = 'i';
//	myproc->cwd[2] = 'n';
//	myproc->cwd[3] = '/';
	myproc->cwd[0] = '\0';
	myproc->next = head;
	if(temp!=NULL)
	{
		while(temp->next!=head)
			temp = temp->next;
		temp->next = myproc;
//		head = myproc;
	}
	else
	{
		head = myproc;
		myproc->next = head;
	}
	return myproc;
}
void proc_status(struct process *proc){
if(proc->status == ENV_IDLE){
	proc->state = ENV_RUNNABLE;
}
}
uint64_t find_elf(char *filename)
{
	struct posix_header_ustar *phu;
//        uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
      	// char * name;
// * size;
/*	if(position == 1)
	{
        phu = (struct posix_header_ustar*) (fsstart+2*sizeof(struct posix_header_ustar));
//+sizeof(struct posix_header_ustar)*2);
	}
	else
	{*/
	phu = (struct posix_header_ustar*) traverse(filename);
//	}
        struct Elf *myelf = (struct Elf*) phu;
       // name = (phu)->name;
//	kprintf("%s\n",name);
//	kprintf("%x\n",myelf->e_entry);
//      size = (phu)->size;
//      name = (char*) (fsstart+2*sizeof(struct posix_header_ustar));
    //    printf("first file magic is--->%d\n",myelf->e_magic);
      //  printf("first file type--->%d\n",myelf->e_type);
      //  printf("first file phoff--->%x\n",myelf->e_phoff);
     //   printf("first file phnum--->%d\n",myelf->e_phnum);
	return (uint64_t)myelf;
}

void allocate_phys_memory(struct process *myproc,uint64_t size,uint64_t va,uint64_t perm)
{
	uint64_t tempsize=0,physaddr,tempva;
	
	for(tempsize=0,tempva = va ; tempsize<size ; tempsize = tempsize+PGSIZE,tempva = tempva+PGSIZE)
	{ 
		/*struct Page * newpage = free_list;
		free_list = newpage->next;
		newpage->page_ref++;
		newpage->next = NULL;
		physaddr = (newpage - pages)*PGSIZE;*/
		physaddr = katopa(page_alloc());
//		if(myproc-procs==0)
		map_region(myproc->pml4e,tempva,physaddr,PGSIZE,perm);
	}
}

void proc_setup_table(struct process * myproc,char *filename)
{
	int i = 0;
	uint64_t physaddr,strtaddr = find_elf(filename);
	if(strtaddr!=0)
	{
		struct Elf * myelf = (struct Elf*) strtaddr;
		if(myelf->e_magic==0x0464C457F)
		{
			struct Proghdr * myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff);
			struct vma_area * temp,*new;
			struct file_desc *temp_fd;
	//	struct Page * newpage;
			pml4e_t * mypml4e = (pml4e_t*)page_alloc();
			myproc->pml4e = mypml4e;
			myproc->pml4e[0x1ff] = pml4e[0x1ff];
//			kprintf("magic number is-->%x\n",myelf->e_magic);
			loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
	//		myproc->pml4e[0] = pml4e[0];
		//	printf("\nphnum--->%d\toffset--->%d\ttype--->%d\n",myelf->e_phoff,myelf->e_phnum,myelf->e_type);
			//if(elfindex==1)
			{
			for(i=0 ; i<myelf->e_phnum ; i++)
			{
				myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff+myelf->e_phentsize*i);
				if(myproghdr->p_type == 1 && myproghdr->p_filesz <= myproghdr->p_memsz)
				{
					//if(elfindex==1)
					temp = myproc->mm_struct;
					if(temp == NULL)
					{
						new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
		                        	new->next = NULL;
						myproc->mm_struct = new;
						temp = new;
					}
					else
					{
						while(temp->next!=NULL)
						{
							temp = temp->next;
						}
						new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
						new->next = NULL;
						temp->next = new;
						temp = new;
					}
					temp->vma_start = myproghdr->p_va;
					temp->vma_end = myproghdr->p_va + myproghdr->p_memsz;
					if(myproghdr->p_flags==4||myproghdr->p_flags==5)
					{
						allocate_phys_memory(myproc,myproghdr->p_memsz,myproghdr->p_va,USERREADPERMISSION);
					}
					else
					{
						allocate_phys_memory(myproc,myproghdr->p_memsz,myproghdr->p_va,USERPML4PERMISSION);
					}
						//myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff+myelf->e_phentsize*i);
					if(myproghdr==NULL)
						break;
					//printf("\ntype--->%d\tva--->%x\tfilesz--->%d\tmemsz--->%d\n",myproghdr->p_type,myproghdr->p_va,myproghdr->p_filesz,myproghdr->p_memsz);
				}
			}
	//	if(cur_proc!=NULL)
	//		loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
		//if(elfindex==1){
			temp = myproc->mm_struct;
			while(temp->next!=NULL)
		        {
		        	temp = temp->next;
		        }
			/*
		       	new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
			        new->next = NULL;
	        temp->next = new;
		        temp = new;*/
				myproc->kstack = page_alloc()+PGSIZE-8;
			/*temp->vma_start = myproc->kstack;
			temp->vma_end = myproc->kstack-PGSIZE+8;
			*/
			//myproc->ppf =page_alloc();
			map_region(myproc->pml4e,myproc->kstack-PGSIZE+8,katopa(myproc->kstack-PGSIZE+8),PGSIZE,USERPML4PERMISSION);
			//for(i=0;i<14;i++)
		//	page_alloc();
		//	i=0;
		//	map_region(myproc->pml4e,myproc->ppf,katopa(myproc->ppf),PGSIZE,USERPML4PERMISSION);
			/* newpage = free_list;
				free_list = newpage->next;
			newpage->page_ref++;
				newpage->next = NULL;*/
			new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
		        new->next = NULL;
		        temp->next = new;
		        temp = new;
			temp->vma_start = USTACK-8*PGSIZE;
		        temp->vma_end = USTACK-8;
			physaddr = katopa(page_alloc());
			map_region(myproc->pml4e,USTACK-PGSIZE,physaddr,PGSIZE,USERPML4PERMISSION);
			//map_region(myproc->pml4e,USTACK-PGSIZE-PGSIZE,katopa(page_alloc()),PGSIZE,USERPML4PERMISSION);
		//	map_region(myproc->pml4e,USTACK-PGSIZE-PGSIZE-PGSIZE,katopa(page_alloc()),PGSIZE,USERPML4PERMISSION);
			myproc->ustack = USTACK-8;
			new = (struct vma_area*)kmalloc(sizeof(struct vma_area));
	        	new->next = NULL;
		        temp->next = new;
		        temp = new;
		        temp->vma_start = UHEAP;
		        temp->vma_end = UHEAP;
			myproc->fd_page = page_alloc();
			temp_fd = (struct file_desc*)myproc->fd_page;
			temp_fd->fd_no = 0;
			temp_fd++;
			temp_fd->fd_no = 1;
			temp_fd++;
			temp_fd->fd_no = 2;
			myproc->fd_count=3;
			}
		}
	}
	else
	{
		kprintf("Not found\n");
	}
}

void elf_copy(struct process * myproc,char *filename)
{
	int i = 0;
	if(cur_proc!=NULL)
	loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
        uint64_t strtaddr = find_elf(filename);
//	if(cur_proc!=NULL)
//		loadcr3(katopa((uint64_t)cur_proc->pml4e),0,0);
	loadcr3(katopa((uint64_t)myproc->pml4e),0,0);
        struct Elf * myelf = (struct Elf*) strtaddr;
        struct Proghdr * myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff);
//      printf("\nphnum--->%d\toffset--->%d\ttype--->%d\n",myelf->e_phoff,myelf->e_phnum,myelf->e_type);
        for(i=0 ; i<myelf->e_phnum ; i++)
        {
		myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff+myelf->e_phentsize*i);
                if(myproghdr->p_type == 1 && myproghdr->p_filesz <= myproghdr->p_memsz)
                {
         //               allocate_phys_memory(myproc,myproghdr->p_memsz,myproghdr->p_va);
                     //   myproghdr = (struct Proghdr *) (strtaddr+myelf->e_phoff+myelf->e_phentsize*i);
			memcopy((char*)(strtaddr+myproghdr->p_offset),(char*)(myproghdr->p_va),myproghdr->p_filesz);
                        //printf("\ntype--->%d\tva--->%x\tfilesz--->%d\tmemsz--->%d\n",myproghdr->p_type,myproghdr->p_va,myproghdr->p_filesz,myproghdr->p_memsz);
                }
        }
	myproc->tf.rip = myelf->e_entry;
	
}
void memcopy(volatile char *src,volatile char *dst,int size) 
{
	int count=0;
	while(count<size)
	{
        *dst=*src;
        src++;
        dst++;
        count++;
	}
}

void setup_stack(struct process *myproc) {

	uint64_t *add = (uint64_t*)myproc->kstack;
	uint64_t *temp;
	*add = 0x23;
	add = add -1;
	*add = myproc->ustack;
	add = add -1;
	*add = 0x200282;
	add = add -1;
	*add = 0x1b;
	add = add -1;
	*add  = myproc->tf.rip;
/*	add = add -1;
	*add = 0;
	add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
 	*add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
        add = add -1;
	 *add = 0;
       temp = add -1;
	*(temp) = (uint64_t)add;
	add = add -1;
	myproc->tf.rsp = (uint64_t)add;*/
	 add = add -1;
        *add = 0;
        add = add -1;
        *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
        *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
        add = add -1;
         *add = 0;
       temp = add -1;
        *(temp) = (uint64_t)add;
        add = add -1;
        myproc->tf.rsp = (uint64_t)add;

}	
	
	
