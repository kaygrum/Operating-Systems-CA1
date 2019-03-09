#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

// 16 bit virtual memory hexidecimal 0xFFFF
//Offset 8 bit
//256 bytes per page
//256 pages
//Maximum addressable physical memory =2^24

//Allocate a block of memory sufficient to store bytes for the 
//		full system address space(note:you may assume the system
//		will always have access to a quantity of physical memory
//		equal to the full address space)
//�Create a Page Table for a single process(note:you are not required
//		to model any other components of a process)
//�Randomly write between 2048 and 20480bytes of databelongingto
//		the �process� previously created.Both the content and locations
//		of these bytes should be pseudo - randomised to some extent.
//�Write a file to[your solution] / data / physical_memory.txtwhich 
//		displays the contents of your simulation of physical memory 
//		in linear, readable form.You must clearly label the memory
//		addresses that are and are not used
//Write a file to [your solution]/data/page_table.txtwhich displays
//		the contents of your simulated page tablein linear, readable 
//		form.
//Add 2 entries to the Page Table which point to pages which are not 
//		stored in your simulated physicalmemory, and store content for
//		these pages in your solution�s data folder (the naming 
//		convention is at your discretion). You should print 1 virtual
//		address from each of these pages, clearly labelled, to the console.
//Print, to the console, a human-readabledescription of the structure
//		of a single page table entry that you haveelected to use
//		(note: you should also document your decisions regarding this
//		in your README.md file)
//Display a prompt which allows the user to enter any virtual memory 
//		address in your system, in hexadecimalform.
int main()
{
	int physicaladdress[65536];
	int physicaladdresspage[256];
	char process1[] = { 'A','B','C','D','E','F','G','H','I','J','K','L' };
	int lengthOfPhysicalAddrArray = sizeof(physicaladdress) / sizeof(int);
	int lengthOfProcessElements = sizeof(process1) / sizeof(char);
	int randomAdressInsertProcess[12];

	for (int i = 0; i < lengthOfProcessElements; i++)
	{
		randomAdressInsertProcess[i]= rand() % (65536 - 0 + 1) + 0;
		printf("0x%X", randomAdressInsertProcess[i]);
		printf("\n");
	}


	//Open file
	FILE *physical;
	physical = fopen("physical_memory.txt", "w");
	if (physical == NULL) {
		printf("couldnt open");
		exit(0);
	}

	int insertProcess = rand() % (65536 - 0 + 1) + 0;

	//Writing Physical address info
	int a = 0, b = 256, page = 0;;
	fprintf(physical, " Address|	Frame	|	Content");
	fprintf(physical, "\n");
	char process = "X";
	for (int i = 0; i < lengthOfPhysicalAddrArray ; i++)
	{

			if (i == a || i < b) {

			}
			else {
				page++, a = a + 256, b = b + 256;
			}
			for (int j = 0; j < lengthOfProcessElements; j++)
			{
				if (i == randomAdressInsertProcess[j])
				{
					process = process1[j];
				}
			}

			physicaladdress[i] = i;
			fprintf(physical, " 0x%X	|	%d	|	%c", i, page, process);
			fprintf(physical, "\n");
			process = "X";
		
	}

	//close file
	fclose(physical);


	//fillProcess();
	//int processPageTable[256];
//	int virtualMemoryAddress[10];
	
//	int virtualMemoryToPhysicalPageTable[256];
//	int virtualToPhysicalPage[256];
//	int physicalMemorySpace[256];
//	unsigned int addr = 0xFFFF;
//	printf("%d", addr);

	//getPageNum();
	//getPageOffset();
	return 0;
}
int fillProcess()
{
	char process1[10] = { 'A','B','C','D','E','F' };
	int physicalPage[256];

	for (int i = 0; i < 256; i++)
	{
		physicalPage[i] = i;
	}
	printf("Proccess 1");
	printf("\n");
	printf("-----------");
	printf("\n");
	//int n = sizeof(process1);
	int n = sizeof(process1) / sizeof(char);
	int p = sizeof(physicalPage) / sizeof(int);

	for (int i = 0; i <= n+1; i++)
	{
		int frame = rand() % (p - 1 + 1) + 1;

		int Address = rand() %  (65536 - 60000 + 1) + 60000;
		printf("0x%X | %d | %c ", Address, frame,  process1[i]);
		printf("\n");
	}

	return 0;
}
int getPageNum()
{
	return 0;
}
int getPageOffset()
{
	return 0;
}