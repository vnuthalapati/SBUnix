#include <sys/pmap.h>
#include <sys/sbunix.h>
#include <sys/proc.h>
//uint64_t curr_free=0;
void test();
void free_page(uint64_t va,uint64_t address)
{
	struct Page * dec_page = pages+address/PGSIZE;
//	struct Page *temp = free_list;
	dec_page->page_ref--;
	
	if(dec_page->page_ref==0)
	{
		//kprintf("freeing address is-->%x\n",address);
		dec_page->next = NULL;
		memset(va,PGSIZE,'\0');
		dec_page->next = free_list;
		free_list = dec_page;
	/*	while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next = dec_page;*/
	}
}
uint64_t katopa(uint64_t kernaddress)
{
	uint64_t ka = (uint64_t)kernaddress;
	uint64_t pa = (ka - KERNOFFSET);
	return pa;
}

void npages_determine(uint64_t size) {

	npages = size/4096;
	//printf("npages is--->%d\n",npages);

}
uint64_t boot_alloc(size_t size)
{
	uint64_t temp = 0;
	if(KERNFREE % 4096!=0) {
		KERNFREE = KERNFREE + 4096;
		KERNFREE = KERNFREE - KERNFREE%4096;
	}
	temp = KERNFREE;
	KERNFREE = KERNFREE + size;
	if(KERNFREE % 4096!=0){
		KERNFREE = KERNFREE + 4096;
		KERNFREE = KERNFREE - KERNFREE%4096;
	}
	//memset(temp,PGSIZE,'\0');
	return temp;

}
void set_consts(uint64_t phybase,uint64_t phyfree)
{
	PHYBASE = phybase;
	PHYFREE = phyfree;
	//	ERNBASE = phybase + KERN;
	KERNFREE = phyfree + KERNOFFSET;
}
/*
   void settables(uint64_t phyfree)
   {	
   curr_free = phyfree + KERNBASE;
   curr_free = curr_free + 4096;
   curr_free = curr_free - curr_free%4096;
   init_cr3 = curr_free;
   pml4e = (pml4e_t *)curr_free;
   curr_free = curr_free + 4096;
   pdpe = (pdpe_t *)curr_free;
   curr_free = curr_free + 4096;
   pgdir = (pgdir_t *)curr_free;
   curr_free = curr_free + 4096 +4096;
   pte = (pte_t *)curr_free;
   curr_free = curr_free + 8388608;
   }*/
static int alloccount = 0;

void mm_init()
{
	pages = (struct Page*)boot_alloc(npages * sizeof(struct Page));
	//	map_region((uint64_t)pages,katopa((uint64_t)pages),npages * sizeof(struct Page));
	pml4e = (pml4e_t *)boot_alloc(PGSIZE);
	procs = (struct process *)boot_alloc(PGSIZE);
	page_init();
	//pml4e = (pml4e_t*)boot_alloc(PGSIZE);
	//map_region(pml4e,(uint64_t)pages,katopa((uint64_t)pages),npages * sizeof(struct Page));
	map_region(pml4e,KERNOFFSET,0,134205440,PML4PERMISSION);
	//printf("between after kernmapping--->%d\n",alloccount);
//	map_region(pml4e,0xffffffff800b8000,0xb8000,PGSIZE,PML4PERMISSION);
	//printf("after b8000 mapping--->%d\n",alloccount);
}

void map_region(pml4e_t * temp_pml4e,uint64_t va,uint64_t pa,size_t size,uint64_t perm)
{
	uint64_t pa_end;
	uint64_t va_end;
	uint64_t va_index;
	uint64_t pa_index;
	pte_t * temp_pte;
	//printf("va is--->%x\n",va);
	va = va - va%PGSIZE;
	pa = pa - pa%PGSIZE;
	pa_end = pa+size;
	va_end = va+size;
	//	uint64_t va_end = va + size;
	if(va_end%4096 != 0)
		va_end = (va_end + PGSIZE) - (va_end%PGSIZE);
	if(pa_end%4096 != 0)
		pa_end = (pa_end + PGSIZE) - (pa_end%PGSIZE);
	//printf("va after editing  is--->%x\n",va);
	//printf("va_end  is--->%x\tsize is--->%x",va_end,size);
	for(va_index = va,pa_index = pa ; va_index < va_end ; va_index = va_index+PGSIZE,pa_index = pa_index+PGSIZE)
	{
		//	if(va_index == KERNOFFSET)
		//printf("pa_index is--->%x\n",pa_index);
		temp_pte = (pte_t*)pml4e_walk(temp_pml4e,va_index,1,perm|0x2);
		if((uint64_t)temp_pte<KERNOFFSET)
		kprintf("temp_pte--->%p\n",temp_pte);
		*(temp_pte) = (pa_index & 0x0000FFFFFFFFFFFF) | perm | 0x100;
		//	if(va_index == 0xb8000)
		//printf("pa_index is--->%x\n",pa_index);
	}


}

void page_init()
{
	uint64_t index = 0;
	for(index = 0 ; index < npages ; index++)
	{
		if(index == 0)
			(pages+index)->page_ref = 1;
		else if(index * PGSIZE+KERNOFFSET >= KERNBASE && index*PGSIZE+KERNOFFSET < KERNFREE)
			(pages+index)->page_ref = 1;
		else if(index * PGSIZE+KERNOFFSET >= 0xFFFFFFFF800b8000 && index*PGSIZE+KERNOFFSET < 0xFFFFFFFF800b8000+PGSIZE)
			(pages+index)->page_ref = 1;
		else
		{
			(pages+index)->page_ref = 0;
			(pages+index)->next = free_list;
			free_list = pages+index;
		}
	}
}
uint64_t page_alloc()
{
	//	static int alloccount = 0;
	uint64_t address;
	struct Page *temp;
	temp = free_list;
	free_list = free_list->next;
	temp->page_ref = 1;
	address = (temp-pages)*PGSIZE + KERNOFFSET;
	memset(address,PGSIZE,'\0');
	//kprintf("alloc count--->%d\n",alloccount);
	alloccount++;
	//memset((uint64_t)temp,PGSIZE,'\0');
	return address;
}

void memset(uint64_t address, uint64_t size, char c)
{
	int i=0;
	char *temp=(char*)address;
	for(i=0;i<size;i++)
	{
		*(temp+i)=c;
	}

}


uint64_t ptetoka(uint64_t inaddress)
{
	if(inaddress == 0)
		return 0;
	uint64_t outaddress;
	outaddress = inaddress & 0xFFFFFFFFFFFFF000;
	return outaddress+KERNOFFSET;
}
pte_t * pml4e_walk(pml4e_t* temp_pml4e,uint64_t va,int create,uint64_t perm)
{
	uint64_t offsetpml4 = (va & PML4MASK)>>PML4SHIFT;
	pml4e_t * temp2pml4e = (pml4e_t*)((temp_pml4e + (offsetpml4)));
	pdpe_t * temp_pdpe = (pdpe_t*)(ptetoka((uint64_t)*temp2pml4e));
	uint64_t temp;
	if(!create)
	{
		if(temp_pdpe == NULL)
		{
			return NULL;
		}
	}
	if(create)
	{
		if(temp_pdpe == NULL)
		{
	//		printf("pdpe alloc\n");
			temp = page_alloc();
			*temp2pml4e = (katopa((uint64_t)temp) & 0x0000FFFFFFFFFFFF) | perm;
			temp_pdpe = (pdpe_t*)temp;

		}


		//pdpe_walk(temp_pdpe,va,create);
	}

	//printf("\npdpe is--->%x\tpml4e offset is--->%x\n",temp_pdpe,offsetpml4);
	return pdpe_walk(temp_pdpe,va,create,perm);
}

pte_t * pdpe_walk(pdpe_t* temp_pdpe,uint64_t va,int create,uint64_t perm)
{
	uint64_t offsetpdpe = (va & PDPEMASK)>>PDPESHIFT;
	pdpe_t * temp2pdpe = (pdpe_t*)((temp_pdpe + (offsetpdpe)));
	pgdir_t * temp_pgdir = (pgdir_t*)(ptetoka((uint64_t)*temp2pdpe));
	uint64_t temp;
	if(!create)
	{
		if(temp_pgdir == NULL)
		{
			return NULL;
		}
	}
	if(create)
	{
		if(temp_pgdir == NULL)
		{
			//printf("pgdir alloc\n");
			temp = page_alloc();
			*temp2pdpe = (katopa(temp) & 0x0000FFFFFFFFFFFF) | perm;
			temp_pgdir = (pgdir_t*)temp;

		}


		//pdpe_walk(temp_pdpe,va,create);
	}
	//printf("pgdir is--->%x\tpdpe offet is--->%x\n",temp_pgdir,offsetpdpe);
	return pgdir_walk(temp_pgdir,va,create,perm);
}

pte_t * pgdir_walk(pgdir_t* temp_pgdir,uint64_t va,int create,uint64_t perm)
{
	uint64_t offsetpgdir = (va & PGDIRMASK)>>PGDIRSHIFT;
	pgdir_t * temp2pgdir = (pgdir_t*)((temp_pgdir + (offsetpgdir)));
	pte_t * temp_pte = (pte_t*)(ptetoka((uint64_t)*temp2pgdir));
	uint64_t temp;
	if(!create)
	{
		if(temp_pte == NULL)
		{
			return NULL;
		}
	}
	if(create)
	{
		if(temp_pte == NULL)
		{
	//		if(va == 0xb8000)
	//		printf("pt alloc\n");
			temp = page_alloc();
			*temp2pgdir = (katopa(temp) & 0x0000FFFFFFFFFFFF) | perm;
			temp_pte = (pte_t*)temp;

		}


		//pdpe_walk(temp_pdpe,va,create);
	}
	//printf("pte is--->%x\tpte offset is--->%x\n",(temp_pte+((va & PTEMASK)>>PTESHIFT)),((va & PTEMASK)>>PTESHIFT));
	return (pte_t*)(temp_pte+((va & PTEMASK)>>PTESHIFT));
}
/*
   void copytables(uint64_t phybase,uint64_t phyfree)
   {
   uint64_t count;
   uint64_t KERNSTART = KERNBASE + (uint64_t)phybase;
   uint64_t KERNEND = KERNBASE + (uint64_t)phyfree;
   uint64_t index = 0;
//uint64_t physfreeptr = (uint64_t)phyfree;
uint64_t physbaseptr = (uint64_t)phybase;
uint64_t offsetpml4;
uint64_t offsetpdpe;
uint64_t offsetpgdir;
uint64_t offsetpte;
//uint64_t offset;
uint64_t physbaseindex;
KERNSTART = KERNSTART - KERNSTART%4096;
KERNEND = KERNEND + 4096;
KERNEND = KERNEND - KERNEND%4096;
//curr_free = curr_free + 4096;
//	curr_free = curr_free -curr_free%4096;
physbaseptr = physbaseptr - physbaseptr%4096;
physbaseindex = physbaseptr;
index = KERNSTART;
count = 0;
index = 0xb8000;
offsetpml4      = (index & PML4MASK)>>PML4SHIFT;
offsetpdpe      = (index & PDPEMASK)>>PDPESHIFT;
offsetpgdir     = (index & PGDIRMASK)>>PGDIRSHIFT;
offsetpte       = (index & PTEMASK)>>PTESHIFT;
//offset                = (index & OFFSETMASK);
//       printf("VA->%x\tpml4offset->%x\tpdpeoffset->%x\tpgdiroffset->%x\tpteoffset->%x\n",index,offsetpml4,offsetpdpe,offsetpgdir,offsetpte);
 *(pml4e + (offsetpml4))         = (katopa((uint64_t)pdpe) & 0x0000FFFFFFFFFFFF) | PML4PERMISSION;
 *(pdpe + (offsetpdpe))          = (katopa((uint64_t)pgdir) & 0x0000FFFFFFFFFFFF) | PDPEPERMISSION;
 *(pgdir + (offsetpgdir))        = (katopa((uint64_t)pte) & 0x0000FFFFFFFFFFFF) | PGDIRPERMISSION;
 *(pte + (offsetpte))            = (physbaseindex & 0x0000FFFFFFFFFFFF) | PTEPERMISSION;
 count++;
 for(index = KERNSTART,physbaseindex = physbaseptr ; index<KERNEND ; index = index+4096,physbaseindex = physbaseindex+4096)
 {
 offsetpml4 	= (index & PML4MASK)>>PML4SHIFT;
 offsetpdpe 	= (index & PDPEMASK)>>PDPESHIFT;
 offsetpgdir 	= (index & PGDIRMASK)>>PGDIRSHIFT;
 offsetpte 	= (index & PTEMASK)>>PTESHIFT;
//offset		= (index & OFFSETMASK);
//		printf("VA->%x\tpml4offset->%x\tpdpeoffset->%x\tpgdiroffset->%x\tpteoffset->%x\n",index,offsetpml4,offsetpdpe,offsetpgdir,offsetpte);
 *(pml4e + (offsetpml4)) 	= (katopa((uint64_t)pdpe) & 0x0000FFFFFFFFFFFF) | PML4PERMISSION;
 *(pdpe + (offsetpdpe)) 		= (katopa((uint64_t)pgdir) & 0x0000FFFFFFFFFFFF) | PDPEPERMISSION;
 *(pgdir + (offsetpgdir))	= (katopa((uint64_t)pte) & 0x0000FFFFFFFFFFFF) | PGDIRPERMISSION;
 *(pte + (offsetpte))		= (physbaseindex & 0x0000FFFFFFFFFFFF) | PTEPERMISSION;
 count++;
 if(count%512 == 0)
 {	
 pte = pte + 512;
 }
 if(count%26214 == 0)
 {
 pgdir = pgdir + 512;
 }
//	printf("in copy pte+offset is->%x\n",*(pte + (offsetpte)));
//physbaseptr = physbaseptr + 
}


}
 */
void loadcr3(uint64_t address,uint64_t phybase,uint64_t phyfree)
{
	/*	uint64_t index = KERNBASE+(uint64_t)(phybase);
		index = index - index%4096;
		uint64_t offsetpml4;
		uint64_t offsetpdpe;
		uint64_t offsetpgdir;
		uint64_t offsetpte;
		uint64_t offset;
		uint64_t KERNSTART = KERNBASE + (uint64_t)phybase;
		uint64_t KERNEND = KERNBASE + (uint64_t)phyfree;
		uint64_t *pdpebase,*pgdirbase,*ptebase,*finaladdress;
	//KERNSTART = KERNSTART - KERNSTART%4096;
	KERNEND = KERNEND + 4096;
	KERNEND = KERNEND - KERNEND%4096;
	//index = KERNSTART;
	//uint64_t count = 0;
	uint64_t printindex = 0;
	//printf("kernstart is->%x\tphysbaseptr is->%x\n",KERNSTART,physbaseptr);
	for(index = KERNSTART ; index<KERNEND ; index = index+4096)
	//address = address + 4096;
	//address = address - address%4096;
	//index = 0x;
	//index = KERNSTART+4096;
	{
	offsetpml4      = (index & PML4MASK)>>PML4SHIFT;
	//offsetpml4 = 0x1FF;
	offsetpdpe      = (index & PDPEMASK)>>PDPESHIFT;
	offsetpgdir     = (index & PGDIRMASK)>>PGDIRSHIFT;
	offsetpte       = (index & PTEMASK)>>PTESHIFT;
	offset          = (index & OFFSETMASK);
	//printf("VA->%x\tpml4offset->%x\tpdpeoffset->%x\npgdiroffset->%x\n",index,offsetpml4,offsetpdpe,offsetpgdir);
	//		printf("pml4e is pointing to->%p\n",pml4e);
	pdpebase 	= (uint64_t*)((pml4e + (offsetpml4))); 
	//printf("pdpebase is->%p\n",pdpebase);
	pgdirbase 	=(uint64_t*)((uint64_t*)(*pdpebase & 0x0000FFFFFFFFF000) + offsetpdpe);
	//printf("pgdirbase is->%p\n",pgdirbase);
	ptebase  	= (uint64_t*)((uint64_t*)(*pgdirbase & 0x0000FFFFFFFFF000) + offsetpgdir);
	//printf("ptebase is->%p\n",ptebase);
	finaladdress    = ((uint64_t*)((uint64_t*)(*ptebase  & 0x0000FFFFFFFFF000)+ offsetpte));
	//	printf("VA->%x\t",index);
	printindex = (*finaladdress& 0x0000FFFFFFFFF000) + offset;
	//	printf("PA->%x\n",printindex);
	//	count++;
	}
	printf("PA-->%x\n",printindex);
	address = address + 4096;
	address = address - address%4096;
	address = (address & 0x0000FFFFFFFFF000);*/
//	printf("address is--->%d\n",address);
	__asm volatile("movq %0,%%cr3"::"r"(address):);
//	pte_t *temp = (pte_t*)(pml4e_walk(pml4e,0xb8000,0));
//	printf("The pa is--->%x\n",(uint64_t)(*temp));
	//__asm volatile("movq %%cr3,%0":"=r"(address)::);
	//printf("address is %x\n",address);
	test();
//	printf("returned from test");
	//	printf("pml4e is loaded at->%x\n",katopa((uint64_t)pml4e));
	//	printf("cr3 loaded with %x\n",address);
}
void test() {
	uint64_t a = 0,b=0;
	__asm volatile("movq %%rax,%0":"=r"(a)::"rax","cc","memory");
	__asm volatile("movq %%rbx,%0":"=r"(b)::"rbx","cc","memory");
}
