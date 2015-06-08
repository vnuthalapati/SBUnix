#ifndef _PMAP_H
#define _PMAP_H

#include <sys/defs.h>
#define KERNOFFSET	0xffffffff80000000
#define KERNBASE 	0xffffffff80200000
#define PHYSBASE 	0x200000
#define PGSIZE 		4096
#define PML4MASK 	0x0000FF8000000000
#define PDPEMASK 	0x0000007FC0000000
#define PGDIRMASK 	0x000000003FE00000
#define PTEMASK		0x00000000001FF000
#define OFFSETMASK	0x0000000000000FFF
#define PML4SHIFT	39
#define PDPESHIFT	30
#define PGDIRSHIFT	21
#define PTESHIFT	12
#define PML4PERMISSION	0x013
#define PDPEPERMISSION	0x013
#define PGDIRPERMISSION	0x013
#define PTEPERMISSION	0x113
#define PML4RESERVED	0x00
#define PDPERESERVED	0x00
#define PGDIRRESERVED	0x00
#define PTERESERVED	0x00
#define USTACK         	0xef800000
#define USERPML4PERMISSION  0x017
#define USERPDPEPERMISSION  0x017
#define USERPGDIRPERMISSION 0x017
#define USERPTEPERMISSION   0x117
#define USERREADPERMISSION  0x115
#define UHEAP           0xEF81A000
#define PRESENT 	0x001
#define READ		0xFFFFFFFFFFFFFFFD
#define STACKMASK1      0xFFFFFFFFFFFFF000
#define STACKMASK2      0x0000000000000FFF
#define COW		0x0000000000000200
typedef uint64_t pml4e_t;
typedef uint64_t pdpe_t;
typedef uint64_t pgdir_t;
typedef uint64_t pte_t;

void* malloc(size_t size);
uint64_t katopa(uint64_t);
void settables(uint64_t phyfree);
void loadcr3(uint64_t,uint64_t,uint64_t);
void copytables(uint64_t,uint64_t);
uint64_t boot_alloc(size_t size);
void free_page(uint64_t va,uint64_t address);
void set_consts(uint64_t phybase,uint64_t phyfree);
void mm_init();
void map_region(pml4e_t * temp_pml4e,uint64_t va,uint64_t pa,size_t size,uint64_t perm);
void page_init();
uint64_t page_alloc();
void memset(uint64_t address, uint64_t size, char c);
uint64_t ptetoka(uint64_t inaddress);
pte_t * pml4e_walk(pml4e_t* temp_pml4e,uint64_t va,int create,uint64_t perm);
pte_t * pdpe_walk(pdpe_t* temp_pdpe,uint64_t va,int create,uint64_t perm);
pte_t * pgdir_walk(pgdir_t* temp_pgdir,uint64_t va,int create,uint64_t perm);
void npages_determine(uint64_t size);
uint64_t npages;
uint64_t exception_stack;
pml4e_t *pml4e;
pdpe_t *pdpe;
pgdir_t *pgdir;
pte_t *pte;
uint64_t PHYBASE;
uint64_t PHYFREE;
uint64_t NPAGES;
//pte_t *pte2;
//pte_t *pte3;

uint64_t curr_free;
uint64_t KERNFREE;

struct Page
{
	struct Page *next;
	int page_ref;
}*pages,*free_list;

//struct Page * free_list;

#endif
