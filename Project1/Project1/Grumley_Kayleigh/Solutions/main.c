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
char *fillProcess(int);
void virtualToPhysicalPage(int, int *, int **, int **);
void inputHexToPhysicalToContent(int *, int *, int , int *, int *, int);
void writeToDisk(int);
int main()
{
	int physicaladdress[65536];
	int physicaladdresspage[256];
	char *process1;
	int lengthOfPhysicalAddrArray = sizeof(physicaladdress) / sizeof(int);
	int lengthOfProcessElements;
	int *randomAdressInsertProcess;

	int *takenPhysicalAddress;
	int *takenPhysicalPage;
	char *takenPhysicalContent;
	int physicalPage[256];
	int startAddress[256];
	int endAddress[256];
	int fullListOfPFrame[65536];
	int fullListOfPhyContent[65536];

	//Yes i should have put this in its own function and used pointers to change the arrays contents but i tried 4 times and every time something went wrong so i finally gave up. 
	//I used the kind of switch pointers method for the function virtualToPhysicalPage and hopefully it shows i can use pointers and what now but the code below is just big and awkward to put in its own function so i decided not to try anymore sorry!!!
	int bytes;
	printf("How many bytes would you like to have for your process? Pick between 0 to 27000 : ");
	scanf("%d", &bytes);
	while (bytes > 27000)
	{
		printf("Bytes must be below 27000 ");
		scanf("%d", &bytes);
	}

	//dynamically setting size of arrays
	process1 = (char*)malloc(bytes * sizeof(char));
	takenPhysicalAddress = (int*)malloc(bytes * sizeof(int));
	takenPhysicalPage = (int*)malloc(bytes * sizeof(int));
	takenPhysicalContent = (char*)malloc(bytes * sizeof(char));
	randomAdressInsertProcess = (int*)malloc(bytes * sizeof(int));

	process1 = fillProcess(bytes);
	
	srand(time(NULL));
	int randomStartingPage= rand() % (256 - 0 + 1) + 0;
	int randomStartingAddress= randomStartingPage*256;
	lengthOfProcessElements = bytes;
	//generating random Address for process
	for (int i = 0; i < lengthOfProcessElements; i++)
	{
		randomAdressInsertProcess[i]= i+ randomStartingAddress;
	}

	//Open file for physical memory
	FILE *physical;
	physical = fopen("data/physical_memory.txt", "w");
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
			if (i >= 0 && i < 512)
			{
				process = 'X';
			}
			fprintf(physical, " 0x%X	|	%d	|	%c", i, page, process);
			fprintf(physical, "\n");
			physicaladdress[i] = i;
			fullListOfPFrame[i] = page;
			fullListOfPhyContent[i] = process;
			//X means address is being used probably by another process, - means space is clear
			int num = rand() % (10 - 0 + 1) + 0;
			if (num % 2 == 0)
			{
				process = '-';
			}
			else
			{
				process = 'X';
			}

	}

	//close file
	fclose(physical);
	
	takenAddressesToFile(bytes,takenPhysicalAddress,takenPhysicalPage,takenPhysicalContent);

	pageTable(physicalPage, startAddress,endAddress);
	
	int *virtualPage;
	int *physicalPageB;
	int endVirtualPage = bytes / 256;
	virtualToPhysicalPage(endVirtualPage, takenPhysicalPage, &virtualPage, &physicalPageB);
	writeToDisk(bytes);
	inputHexToPhysicalToContent(virtualPage, physicalPageB, endVirtualPage,physicaladdress,fullListOfPhyContent, bytes);


	return 0;
}
char *fillProcess(int bytes)
{
	char *process1;
	process1= (char*)malloc(bytes * sizeof(char));
	FILE *readProcess1;
	//char = 1 byte. 
	//pulling from a text file a paragraph with 2764 characters which is equal to 2764 bytes
	readProcess1 = fopen("data/Process1.txt", "r");
	if (readProcess1 == NULL)
	{
		printf("couldnt open");
		exit(0);
	}

	char ch;
	int i = 0;
	while ((ch = fgetc(readProcess1)) != EOF) {
		if (bytes == i)
		{
			break;
		}
		else {
			process1[i] = ch;
			i++;
		}
	}
	fclose(readProcess1);
	return process1;
}
int takenAddressesToFile(int bytes, int * takenPhysicalAddress, int * takenPhysicalPage, char * takenPhysicalContent)
{
	//writing out to screen
	FILE *takeAddresses;
	takeAddresses = fopen("data/taken_addresses.txt", "w");
	if (takeAddresses == NULL) {
		printf("couldnt open");
		exit(0);
	}

	fprintf(takeAddresses, "Below is the content and the addresses the content is put in for process 1");
	fprintf(takeAddresses, "\n");
	fprintf(takeAddresses, " Address|	Frame	|	Content");
	fprintf(takeAddresses, "\n");

	for (int n = 0; n < bytes; n++)
	{
		fprintf(takeAddresses, "0x%X	|	%d	|	%c", takenPhysicalAddress[n], takenPhysicalPage[n], takenPhysicalContent[n]);
		fprintf(takeAddresses, "\n");
	}
	fclose(takeAddresses);
	return 0;
}
int pageTable(int *physicalPage, int * startAddress, int * endAddress)
{
	//opening page entry to write to
	FILE *pageEntry;
	pageEntry = fopen("data/page_table.txt", "w");
	if (pageEntry == NULL) {
		printf("couldnt open");
		exit(0);
	}
	fprintf(pageEntry, "Page	|	Page Table Entry");
	fprintf(pageEntry, "\n");
	for (int i = 0; i < 256; i++)
	{
		fprintf(pageEntry, "%d	|	0x%X - 0x%X", physicalPage[i], startAddress[i], endAddress[i]);
		fprintf(pageEntry, "\n");
	}
	fprintf(pageEntry, "Disk	|	D%c - D%c", '1', '2');
	fprintf(pageEntry, "\n");
	printf("/n I decided to use a simple page to hex address for the physical page table. There are 256 pages, 0 to 255, and in those 256 there are 256 addressess, oxXX00 to 0xXXFF. /n At the end of the page table text file I have added 2 new entries D1 and D2 aon Disk. \nThese are entries pointing to a disk space.\n\n");

	//closing
	fclose(pageEntry);

	return 0;
}
void virtualToPhysicalPage(int endVirtualPage, int *takenPhysicalPage,int **virtualPage,int **physicalPageB)
{

	//virtual page to physical

	*physicalPageB = malloc(256 * sizeof(int));
	*virtualPage = malloc(256 * sizeof(int));
	int * tempphysicalPageB = malloc(256 * sizeof(int));
	int * tempvirtualPage = malloc(256 * sizeof(int));

	for (int i = 0; i < 256; i++)
	{
		if (endVirtualPage > (i - 1) && endVirtualPage <= i)
		{
			endVirtualPage = i;
		}
	}


	for (int i = 0; i < endVirtualPage + 1; i++)
	{
		tempvirtualPage[i] = i;
		tempphysicalPageB[i] = takenPhysicalPage[0] + i;
	}
	FILE *vPageToPPage;
	vPageToPPage = fopen("data/physical_to_virtual_page.txt", "w");
	if (vPageToPPage == NULL) {
		printf("couldnt open");
		exit(0);
	}
	fprintf(vPageToPPage, "Virtual Page|	Physical Page");
	fprintf(vPageToPPage, "\n");

	for (int i = 0; i < endVirtualPage + 1; i++)
	{
		fprintf(vPageToPPage, "%d	|	%d", tempvirtualPage[i], tempphysicalPageB[i]);
		fprintf(vPageToPPage, "\n");
	}
	*physicalPageB = tempphysicalPageB;
	*virtualPage = tempvirtualPage;
	//closing
	fclose(vPageToPPage);
}
void inputHexToPhysicalToContent(int *virtualPage, int *physicalPageB, int endVirtualPage, int *physicaladdress, int *fullListOfPhyContent,int bytes)
{

	//User input

	int hexNumber = NULL;
	int mask = 0x00FF;
	printf("What virtual address would you like to see the contents of? \nTo exit type -1 \n: ");
	scanf("%x", &hexNumber);

	while (hexNumber != -1)
	{
		while ((int)hexNumber > bytes)
		{
			printf(" Virtual address non existant. What virtual address would you like to see the contents of? \nTo exit type -1 \n: ");
			scanf("%x", &hexNumber);
		}
		int offset = hexNumber & mask;
		int pageNum = hexNumber >> 8;
		int physicalPageC = 0;
		int physicalAddress;

		for (int i = 0; i < endVirtualPage + 1; i++)
		{
			if (pageNum == virtualPage[i])
			{
				physicalPageC = physicalPageB[i];
			}
		}
		physicalAddress = (physicalPageC << 8) + (offset);
		char contentWanted;

		for (int i = 0; i < 65536; i++)
		{
			if (physicaladdress[i] == physicalAddress)
			{
				contentWanted = fullListOfPhyContent[i];
				printf("\n That virtual Address leads to physical address 0x%X and the contents are %c \n NOTE: if a blank appears it just means a the character is a space.\n \n", physicalAddress, contentWanted);
				printf("\n For this i saved all my data in arrays so I can easily access all the info I need. The program first accessed the virtual to page table data after getting the page number from the inserted virtual address wanted and sees what the physical address is. After that it ads back the page number and searches all physical addresses for that exact hex number then gets its content.\n \n");
				printf("What virtual address would you like to see the contents of? \nTo exit type -1 \n: ");
				scanf("%x", &hexNumber);
			}
		}
	}
}
void writeToDisk(int bytes)
{
	//opening page entry to write to
	FILE *diskContent;
	diskContent = fopen("data/disk.txt", "w");
	if (diskContent == NULL) {
		printf("couldnt open");
		exit(0);
	}
	fprintf(diskContent, "Address	|	Page	|	Virtual Address \n");
	fprintf(diskContent, "D1	|	Disk	|	0x%X\n",bytes+1);
	fprintf(diskContent, "D2	|	Disk	|	0x%X\n", bytes + 2);
	printf( "D2	|	Disk	|	0x%X\n", bytes + 2);
	fclose(diskContent);
}