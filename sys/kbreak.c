#include <sys/pmap.h>
#include <sys/proc.h>

uint64_t kbreak(uint64_t address)
{
	struct vma_area *temp;
	temp = cur_proc->mm_struct;
	while(1)
	{
	//	temp = temp->next;
		if(temp->vma_start == UHEAP)
			break;
		temp = temp->next;
	}
	if(address==0)
		return temp->vma_end;
	else
	{
		temp->vma_end = address;
		return temp->vma_end;
	}
}

