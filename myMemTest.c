#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"
#include "mmu.h"
 //#define PGSIZE 4096
//#include <fileapi.h>
#define DEBUG 1
#define x 2*4096



int
main(int argc, char *argv[]){


	

	//  FILE *fptr;
	//  fptr=fopen("amr.txt","r");
	//  int num;
	//  fscanf(fptr,"%d", &num);
	// printf(1,"Value of n=%d", num);
	//  fclose(fptr); 


	#if FIFO
	int i;
	
	char *arr[14];
	char input[10];
	// Allocate all remaining 12 physical pages
	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE)-x;
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE)-x 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	/*
	Allocate page 13.
	This allocation would cause page 0 to move to the swap file, but upon returning
	to user space, a PGFLT would occur and pages 0,1 will be hot-swapped.
	Afterwards, page 1 is in the swap file, the rest are in memory.
	*/
	arr[12] = sbrk(PGSIZE)-x;
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE)-x for the 13th time, a page fault should occur and one page in swap file.\nPress any key...\n");
	gets(input, 10);

	/*
	Allocate page 14.
	This would cause page 2 to move to the swap file, but since it contains the
	user stack, it would be hot-swapped with page 3.
	Afterwards, pages 1 & 3 are in the swap file, the rest are in memory.
	*/
	arr[13] = sbrk(PGSIZE)-x;
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE)-x for the 14th time, a page fault should occur and two pages in swap file.\nPress any key...\n");
	gets(input, 10);

#endif
	exit();
}
