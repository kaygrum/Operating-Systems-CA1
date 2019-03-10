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
//•Create a Page Table for a single process(note:you are not required
//		to model any other components of a process)
//•Randomly write between 2048 and 20480bytes of databelongingto
//		the ‘process’ previously created.Both the content and locations
//		of these bytes should be pseudo - randomised to some extent.
//•Write a file to[your solution] / data / physical_memory.txtwhich 
//		displays the contents of your simulation of physical memory 
//		in linear, readable form.You must clearly label the memory
//		addresses that are and are not used
//Write a file to [your solution]/data/page_table.txtwhich displays
//		the contents of your simulated page tablein linear, readable 
//		form.
//Add 2 entries to the Page Table which point to pages which are not 
//		stored in your simulated physicalmemory, and store content for
//		these pages in your solution’s data folder (the naming 
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
	char process1[2764] ;
	int lengthOfPhysicalAddrArray = sizeof(physicaladdress) / sizeof(int);
	int lengthOfProcessElements = sizeof(process1) / sizeof(char);
	int randomAdressInsertProcess[2764];

	int takenPhysicalAddress[2764];
	int takenPhysicalPage[2764];
	char takenPhysicalContent[2764];
	int physicalPage[256];
	int startAddress[256];
	int endAddress[256];

	FILE *readProcess1;
	//char = 1 byte. 
	//pulling from a text file a paragraph with 2764 characters which is equal to 2764 bytes
	readProcess1=fopen("Process1.txt", "r");
	if (readProcess1 == NULL)
	{
		printf("couldnt open");
		exit(0);
	}
	char ch;
	int i = 0;
	while ((ch = fgetc(readProcess1)) != EOF) {
		process1[i] = ch;
		i++;
	}
	fclose(readProcess1);

	//generating random Address for process
	for (int i = 0; i < lengthOfProcessElements; i++)
	{
		randomAdressInsertProcess[i]= rand() % (65536 - 0 + 1) + 0;
	}


	//Open file for physical memory
	FILE *physical;
	physical = fopen("physical_memory.txt", "w");
	if (physical == NULL) {
		printf("couldnt open");
		exit(0);
	}

	int insertProcess = rand() % (65536 - 0 + 1) + 0;

	//Writing Physical address info
	int a = 0, b = 256, page = 0;;
	physicalPage[0] = page;
	startAddress[0] = a;
	endAddress[0] = b-1;
	int g = 0;
	fprintf(physical, " Address|	Frame	|	Content");
	fprintf(physical, "\n");
	char process = '-';
	for (int i = 0; i < lengthOfPhysicalAddrArray ; i++)
	{
			if (i == a || i < b) 
			{
			}
			else 
			{
				g++;
				page++, a = a + 256, b = b + 256;
				physicalPage[g] = page;
				startAddress[g] = a;
				endAddress[g] = b-1;
			}
			for (int j = 0; j < lengthOfProcessElements; j++)
			{
				if (i == randomAdressInsertProcess[j])
				{
					process = process1[j];
					takenPhysicalAddress[j] = i;
					takenPhysicalPage[j] = page;
					takenPhysicalContent[j] = process;
				}
			}

			physicaladdress[i] = i;
			fprintf(physical, " 0x%X	|	%d	|	%c", i, page, process);
			fprintf(physical, "\n");
			process ='-';		
	}

	//close file
	fclose(physical);

	//writing out to screen
	printf("Below is the content and the addresses the content is put in for process 1");
	printf("\n");
	printf(" Address|	Frame	|	Content");
	printf("\n");

	for (int n = 0; n < 2764; n++)
	{
		printf("0x%X	|	%d	|	%c", takenPhysicalAddress[n], takenPhysicalPage[n], takenPhysicalContent[n]);
		printf("\n");
	}

	//opening page entry to write to
	FILE *pageEntry;
	pageEntry = fopen("page_table.txt", "w");
	if (pageEntry == NULL) {
		printf("couldnt open");
		exit(0);
	}
	fprintf(pageEntry, "Page	|	Page Table Entry");
	fprintf(pageEntry, "\n");
	for (int i = 0; i < 256; i++)
	{
		fprintf(pageEntry, "%d	|	0x%X - 0x%X",physicalPage[i],startAddress[i],endAddress[i]);
		fprintf(pageEntry, "\n");
	}

	//closing
	fclose(pageEntry);


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