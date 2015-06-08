#include<sys/kernlib.h>
#include<sys/sbunix.h>
#include<sys/tarfshandling.h>
#include<sys/string.h>
void stringcpy(char *str,char *ten);
int strngcmp(char *s,char *t);
uint64_t fds[500][500][2];
int inode;
int first_check =1;
int total_offset;

void filter_dirents(struct file *temp,int fd)
{	
	int i=0,first_time =1;

//	char *name = (char*)temp->name;
	int dash =0,var=0,j=0;
	if(temp->name[0]!='\0'){
	char *name = (char*)temp->name;
	if(temp->name!='\0'){
	while(name[i]!='\0'){
		if(name[i]=='/')
		{		
		dash++;
		}
		i++;
	}
	}
	}
//	kprintf("dash value is %d\n",dash);
	struct dirent *new = (struct dirent*)temp->dir;
	struct dirent  *prev3 = (struct dirent*)kmalloc(sizeof(struct dirent*));
	prev3 = new;
	while(new!=NULL)
	{	

		j=0;
		var =0;
		while(new->d_name[j]!='\0'){
			if(new->d_name[j]=='/')
			{
				var++;
			}
			if(var>dash)
			{
				break;
			}
			j++;
		}
		new->d_name[j++]='\0';	
//		kprintf("eliminated dirent name is %s\n",new->d_name);
		if(first_time==1)
		{
		first_time =0;
		}else{
		if( strngcmp((char*)prev3->d_name,(char*)new->d_name)==0)
		{
		//kprintf("prev name is is %s\n",prev3->d_name);
		prev3->next = new->next;
	//	kprintf("new  name is %s\n",new->d_name);	
		}
		else{
	//	kprintf("prev name is is %s\n",prev3->d_name);
		prev3 = new;
	//	kprintf("prev name is is %s\n",prev3->d_name);
		}
		}
	//	prev3 =new;
		new = new->next;
	}
}
void insert_dirents(struct file *temp,int fd)
{	
	int i=0;
//	char A[1];
//	A[0]='0';
	char *name  = temp->name;
//	kprintf("reached dirents function %s\n",name);
	struct dirent *prev = (struct dirent*)kmalloc(sizeof(struct dirent));
	//temp->dir = prev;
	struct posix_header_ustar *phu=(struct posix_header_ustar*)kmalloc(sizeof(struct posix_header_ustar));
	phu=(struct posix_header_ustar*)traverse_directory(name);
	while(scmp((char*)name,phu->name)==0){
	if(first_check==1){
	struct dirent *new = (struct dirent*)kmalloc(sizeof(struct dirent));
	i=0;
	while(phu->name[i]!='\0')
	{
		new->d_name[i]=phu->name[i];
		i++;
	}
	new->d_ino = inode++;
	new->d_reclen = sizeof(struct kdirent);
	new->next = NULL;
	fds[cur_proc->id][fd][0]=(uint64_t)(new);
	temp->dir  = new;
	prev = temp->dir;
	first_check =0;
	}else{
	struct dirent *new = (struct dirent*)kmalloc(sizeof(struct dirent));
	i=0;
	while(phu->name[i]!='\0')
        {
                new->d_name[i]=phu->name[i];
                i++;
        }
        new->d_ino = inode++;
        new->d_reclen = sizeof(struct kdirent);
        new->next = NULL;
        prev->next = new;
	prev = new;
	}
	phu=(struct posix_header_ustar*)traverse_directory(phu->name);
	}
	first_check = 1;
	filter_dirents(temp,fd);

}


void insert_dirents_root(struct file *temp,int fd){
int i=0;
        char *name  =(char*)kmalloc(sizeof(200));;
//	 kprintf("reached dirents function %s\n",name);
        struct dirent *prev = (struct dirent*)kmalloc(sizeof(struct dirent));
        struct posix_header_ustar *phu;//=(struct posix_header_ustar*)kmalloc(sizeof(struct posix_header_ustar));
//	uint64_t bound=0,prev1=fsstart;
         uint64_t fsstart = (uint64_t)&_binary_tarfs_start;
	uint64_t bound=0,prev1=fsstart;
         phu = (struct posix_header_ustar*) (fsstart);
         while(phu->name[i]!='\0'){
                name[i] = phu->name[i];
                i++;
        }
        name[i]='\0';
        i=0; 
//	kprintf("before while lop%s\n",phu->name);
//	phu=(struct posix_header_ustar*)traverse_directory(name);
//	kprintf("before while lop%s\n",phu->name);
	while(strngcmp(phu->name,"")){
        if(first_check==1){
        struct dirent *new = (struct dirent*)kmalloc(sizeof(struct dirent));
        i=0;
        while(phu->name[i]!='\0')
        {
                new->d_name[i]=phu->name[i];
                i++;
        }
        new->d_ino = inode++;
        new->d_reclen = sizeof(struct kdirent);
        new->next = NULL;
        fds[cur_proc->id][fd][0]=(uint64_t)(new);
        temp->dir  = new;
        prev = temp->dir;
        first_check =0;
        }else{
        struct dirent *new = (struct dirent*)kmalloc(sizeof(struct dirent));
        i=0;
        while(phu->name[i]!='\0')
        {
                new->d_name[i]=phu->name[i];
                i++;
        }
        new->d_ino = inode++;
        new->d_reclen = sizeof(struct kdirent);
        new->next = NULL;
        prev->next = new;
        prev = new;
        }
	bound = 0;
        bound = octaltodecimal((phu)->size);
        if(bound%512!=0){
        bound = bound + 512;
        bound = bound-bound%512;
        }
        prev1 = prev1 + sizeof(struct posix_header_ustar) + bound;
        phu = (struct posix_header_ustar*)(prev1);
//	kprintf("phu name is %s\n",phu->name);
       // phu=(struct posix_header_ustar*)traverse_directory(phu->name);
        }
        first_check = 1;
//	kprintf("after while loop\n");
        filter_dirents(temp,fd);
}
int kgetdents(int fd,uint64_t temp,int count)
{	
	total_offset = 0;
	int i=0;
	//struct file_desc *temp_ds = (struct file_desc*)(cur_proc->fd_page)+fd;
//	struct file *new =(struct file*)temp_ds->file_address;
//	kprintf("directory identified is %s\n",new->name);
	struct kdirent *one =(struct kdirent*)temp;
//	struct dirent *new2 = new->dir;
//	uint64_t addr = fds[cur_proc->id][fd][0];
	if(fds[cur_proc->id][fd][0]!=0){
	struct dirent *new2 = (struct dirent*)fds[cur_proc->id][fd][0];
	while(new2!=NULL)
	{	
		one->d_ino = new2->d_ino;
		one->d_off = new2->d_off;
		one->d_reclen = new2->d_reclen;
		i=0;
		while(new2->d_name[i]!='\0')
        	{
                one->d_name[i]=new2->d_name[i];
                i++;
        	}
		one->d_name[i]='\0';
	//	one->d_name =new2->d_name;
	//	kprintf("name in kgetdents  %s\n",one->d_name);
		total_offset =total_offset+new2->d_reclen;
		one++;
		new2=new2->next;
		if(total_offset>=count){
		fds[cur_proc->id][fd][0]=(uint64_t)new2;
		break;
		}
		if(new2==NULL){
                fds[cur_proc->id][fd][0]=0;
                }

	}
	}
//	struct dirent *d  =(struct dirent*)temp;	
//	kprintf("in getdents %s\n",d->d_name);
//	struct posix_header_ustar* phu = (struct posix_header_ustar*)traverse_file("bin/hello/");
//	kprintf("typeflag value is %d\n",phu->typeflag);	
//	fds[cur_proc->id][fd][0] = fds[cur_proc->id][fd][0]+ count;
	return total_offset;
}
int kopen(const char *pathname, int flags)
{
	struct process * myproc = cur_proc;
//	struct file *temp = file_list;
//	struct file *prev_file;
	struct file_desc * temp_desc;
//	struct posix_header_ustar *phu1;
	struct posix_header_ustar *phu1;
//	uint64_t content_address;
	char *temp_pathname;
	char Ar[200];
	char *pa = Ar;
	int i=0;
	//kprintf("in kopen pathname->%s\n",pathname);
	if(flags == 0x10000 || flags == 0)
	{
	}else{
	kprintf("Not Allowed to create or write\n");
	return -1;
	}
	if(pathname[0]!='\0' && flags == 0x10000){
	temp_pathname = (char*)pathname;
	 phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
	}
	else if(pathname[0]!='\0' && flags != 0x10000){
	        temp_pathname = (char*)pathname;
	         phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
			if(phu1==NULL){
				for(i=0;i<200;i++)
                                {
                                        Ar[i]='\0';
                                }
				i=0;
				current_dir((uint64_t)Ar,200);
				stringcat(pa,temp_pathname);
				temp_pathname = (char*)kmalloc(sizeof(100));
				while(pa[i]!='\0'){
				temp_pathname[i]= pa[i];
				i++;
				}
				temp_pathname[i]='\0';
			//	kprintf("temp name is %s\n",temp_pathname);
				phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
				if(phu1==NULL){
				return -1;
				}
			}
        }
	else if(pathname[0]=='\0' && flags==0x10000){
	temp_pathname = (char*)kmalloc(sizeof(10));
        temp_pathname[0]='\0';
       // temp_pathname[1] ='\0';
	phu1 = NULL;
	}else{
	return -1;
	}
//	prev_file = temp;
	
//	phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
	if(phu1==NULL && flags != 0x10000){
//	kprintf("entered this phu null\n");
	return -1;
	}
	 char A[1];
                A[0]='5';

	if(flags == 0x10000)
	{
		if(phu1!=NULL){
                if((scmp((char*)phu1->typeflag,A)!=0)){
                        return -1;
                }
                }
	}

	
      //  kprintf("after traversing--->%s\n",phu1->name);
//	if(flags!= 0x10000){
  //      content_address = (uint64_t)traverse_file_content(temp_pathname);
//	}

	if(flags == 0x10000)
	{	

	//	if((phu1!=NULL)){
//		char A[1];
//        	A[0]='5';
		struct file *temp = file_list;
		struct file *prev_dir;
		prev_dir = temp;		
		while(temp!=NULL){
		if(!strngcmp(temp->name,temp_pathname))
                {
                        myproc->fd_count++;
                        temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                        temp_desc->file_address = (uint64_t)temp;
			struct file *fresh = (struct file*)temp;
                        temp_desc->offset = 0;
                        temp_desc->perm = flags;
                        temp_desc->fd_no = myproc->fd_count;
			fds[cur_proc->id][temp_desc->fd_no][0] = (uint64_t)(fresh->dir);
                        return myproc->fd_count;
                }
                prev_dir = temp;
                temp = temp->next;
        	}
	
		if(prev_dir!=NULL&&phu1!=NULL)
        	{
                temp = (struct file*)kmalloc(sizeof(struct file));
                //string copy
//              kprintf("after traversing--->%s\n",phu1->name);
                stringcpy((temp->name),(phu1->name));
                //settype
               // temp->start_address = content_address;
		temp->type = 2;
//		insert_dirents(temp);
                temp->size = octaltodecimal(phu1->size);
                prev_dir->next = temp;
                temp->next = NULL;
	//	insert_dirents(temp,myproc->fd_count);
//		kprintf("file name is %s\n",temp->dir->d_name);
                myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
                temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
//		kprintf("before insert dirents\n");
		insert_dirents(temp,temp_desc->fd_no);
                return temp_desc->fd_no;
                //fd, return part left
        	}

		if(prev_dir==NULL&&phu1!=NULL)
        	{
                temp = (struct file*)kmalloc(sizeof(struct file));
        //      prev_file = temp;
                file_list = temp;
            //    kprintf("before copy--->%s\n",phu1->name);
                stringcpy((char*)temp->name,(char*)phu1->name);
                //string copy
                //settype
//                kprintf("after copy-->%s\n",temp->name);
               // temp->start_address = content_address;
//		insert_dirents(temp);
                temp->size = octaltodecimal(phu1->size);
              //  prev_file->next = temp;
                temp->next = NULL;
	//	insert_dirents(temp,myproc->fd_count);
		temp->type = 2;
		//kprintf("file name is %s\n",temp->dir->d_name);
                myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
                temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
	//	kprintf("before insert dirents\n");
		insert_dirents(temp,temp_desc->fd_no);
                return temp_desc->fd_no;
        	}
       		if (phu1==NULL && temp_pathname[0]=='\0' && prev_dir!=NULL)
		{
	//	kprintf("reached this condition\n");
		temp = (struct file*)kmalloc(sizeof(struct file));
                //string copy
	            //  kprintf("after traversing--->%s\n",temp_pathname);
               // stringcpy((temp->name),temp_pathname);
                //settype
//                temp->start_address = content_address;
		temp->name[0]='\0';
                temp->type = 2;
//              insert_dirents(temp);
//		temp->name[0]='\0';
                temp->size = 0;
                prev_dir->next = temp;
                temp->next = NULL;
        //      insert_dirents(temp,myproc->fd_count);
//              kprintf("file name is %s\n",temp->dir->d_name);
                myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
                temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
          //      kprintf("before insert dirents\n");
                insert_dirents_root(temp,temp_desc->fd_no);
                return temp_desc->fd_no;
		}
		if (phu1==NULL && temp_pathname[0]=='\0' && prev_dir==NULL)
                {
		temp = (struct file*)kmalloc(sizeof(struct file));
        //      prev_file = temp;
                file_list = temp;
               // kprintf("before copy--->%s\n",phu1->name);
                //stringcpy((char*)temp->name,(char*)temp_pathname);
                //string copy
                //settype
		temp->name[0]='\0';
//                kprintf("after copy-->%s\n",temp->name);
               // temp->start_address = content_address;
//              insert_dirents(temp);
                temp->size = 0;
              //  prev_file->next = temp;
                temp->next = NULL;
        //      insert_dirents(temp,myproc->fd_count);
                temp->type = 2;
                //kprintf("file name is %s\n",temp->dir->d_name);
                myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
                temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
            //    kprintf("before insert dirents\n");
                insert_dirents_root(temp,temp_desc->fd_no);
                return temp_desc->fd_no;
			
		}		
	return -1;
	}	
	else{

	struct file *temp = file_list;
        struct file *prev_file;
	prev_file = temp;
	
uint64_t content_address = (uint64_t)traverse_file_content(temp_pathname);
//	kprintf("received filename--->%s\n",temp_pathname);
		while(temp!=NULL)
		{
		if(!strngcmp(temp->name,temp_pathname))
		{
			myproc->fd_count++;
			temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//			myproc->fd_count++;
			temp_desc->file_address = (uint64_t)temp;
			temp_desc->offset = 0;
			temp_desc->perm = flags;
			temp_desc->fd_no = myproc->fd_count;
			return myproc->fd_count;
		}
		prev_file = temp;
		temp = temp->next;
		}
	//kprintf("before traversing--->%s\n",temp_pathname);	
//	if(flags || O_DIRECTORY){
//	phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
//	return phu1;	
//	}else{
//	phu1 = (struct posix_header_ustar*)traverse_file(temp_pathname);
	//kprintf("after traversing--->%s\n",phu1->name);
//	content_address = (uint64_t)traverse_file_content(temp_pathname);
		if(prev_file!=NULL&&phu1!=NULL)
		{
		temp = (struct file*)kmalloc(sizeof(struct file));
		//string copy
//		kprintf("after traversing--->%s\n",phu1->name);
		stringcpy((temp->name),(phu1->name));		
		//settype
		temp->start_address = content_address;
		temp->size = octaltodecimal(phu1->size);
		prev_file->next = temp;
		temp->next = NULL;
		myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
		temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
                return temp_desc->fd_no;
		//fd, return part left
		}
		if(prev_file==NULL&&phu1!=NULL)
		{
		temp = (struct file*)kmalloc(sizeof(struct file));
	//	prev_file = temp;
		file_list = temp;
//		kprintf("before copy--->%s\n",phu1->name);
		stringcpy((char*)temp->name,(char*)phu1->name);
                //string copy
                //settype
//		kprintf("after copy-->%s\n",temp->name);	
                temp->start_address = content_address;
                temp->size = octaltodecimal(phu1->size);
              //  prev_file->next = temp;
                temp->next = NULL;
                myproc->fd_count++;
                temp_desc = (struct file_desc*)(myproc->fd_page)+myproc->fd_count;
//                      myproc->fd_count++;
                temp_desc->file_address = (uint64_t)temp;
		temp_desc->fd_no = myproc->fd_count;
                temp_desc->offset = 0;
                temp_desc->perm = flags;
                return temp_desc->fd_no;
		}
	//	else
		return -1;

	}
//	return myproc->fd_count;
}



