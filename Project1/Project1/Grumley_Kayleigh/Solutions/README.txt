Hey Shane!
So i put the requirments into functions I guess exept writing the
 physical memory file. I tried it and it took me aggggessss as well 
as a few different errors everytime i tried to run the thing. I know
 how to use pointers and the & it was just becomming v messy but i 
used it in the virtualToPhysicalPage and hopefully that enough but i 
think i spent a lot of time on this so apart from that i think i did 
pretty well.

I used a exert from some mythology wikipedia page for the process1.
It reads the characters into an array depending on how many bytes 
you want.
The page table was written from 0 to 155 for the pages and the entries 
from 0 to whatever 256*256 is.
I also included a text file with the teaken addresses from process 1
 and their contents so its easier for you to look at it.
For the virtual to physical pages I started obviously at page 0 since 
the virtual memory is for that process only and connected it to a
 randomly generated number and mutiplied it byy 256. Making sure it 
wasnt in the range 0 to 512 since its saved for the page entries and 
also no more than that plus the amount of bytes so it would have enough room to breath.
I used malloc for the arrays whos sizes depended on how many bytes you were using.
In the full physical memory text file the X's are used to indicate that
 that physical memory address is being used up by another process, bar 
the 0 to 511 being used for the page table.
The - indicates there is nothing in that memory and i just have them 
randomly generated.
I explained in the console what is going on when you insert your virtual memory you want to look but ill paste it below.
 For this i saved all my data in arrays so I can easily access all the
 info I need. The program first accessed the virtual to page table data
 after getting the page number from the inserted virtual address wanted
 and sees what the physical address is. After that it ads back the page
 number and searches all physical addresses for that exact hex number  
then gets its content.
So yeah I think i explained everything!
Thanks

