//Mini Project on
//Memory Allocation Techniques

 
//Code:
/*
 * This program performs animation of first fit, best fit, worst fit operating system concepts,along with compaction!
*/

#include<stdio.h>
#include<conio.h>
#define maxmem_no 100

int mem[maxmem_no], maxmem = maxmem_no;

void initmem()
{
	int i = 0;
	for(; i<maxmem; i++)
		mem[i] = 0;
}

void comp()
{
	int mem_temp[maxmem_no], i = 0, k;
	for(; i<maxmem; i++)
		mem_temp[i] = mem[i];
	initmem();
	for(i=0, k=0; i<maxmem; i++)
		if(mem_temp[i] != 0)
		{
			mem[k] = mem_temp[i];
			k++;
		}
}

void removejob()
{
	int jn, i=0;
	printf("\nEnter Job Number to remove: "); scanf("%d", &jn);
	if(jn<0)
	{
		printf("Error!");
		getch();
		return;
	}
	for (; i<maxmem; i++)
		if (mem[i]== jn)
			mem[i] =0;
}

void printmem()
{
	int i =0;
	for (printf("\n"); i<maxmem; i++)
	{
		(mem[i]==0)?printf("%c ", 176):printf("%c ", 219);
	}
	printf("\n\n");
	for (i=0; i<maxmem; i++)
	{
		if(mem[i]!=0)
			printf("%d ", mem[i]);
		else
			printf("  ");
	}
	printf("\n\n");
}

void memalloc(int jn, int jm, int mem_srt)
{
	int i = mem_srt;
	for(; i<=mem_srt+jm-1; i++)
		mem[i] = jn;
}

int memfreeFF(int memreq)
{
	int i=0, start = -1, end = -1;
calc:
	start=-1, end=-1;
	for(; i<maxmem; i++)
	{
		if(mem[i] == 0)
		{
			start = i;
			break;
		}
	}
	for(; i<maxmem; i++)
	{
		if(mem[i]==0)
		{
			end = i;
		}
		else
		{
			break;
		}
	}
	if ((end - start +1) >= memreq)
	{
		return start;
	}
	else if(i<maxmem)
	{
		goto calc;
	}
	return -1;
}

int memfreeBF(int memreq)
{
	int i=0, start = -1, end = -1;
	int start_temp = -1, tot_free = -1;
calc:
	start=-1, end=-1;
	for(; i<maxmem; i++)
	{
		if(mem[i] == 0)
		{
			start = i;
			break;
		}
	}
	for(; i<maxmem; i++)
	{
		if(mem[i]==0)
		{
			end = i;
		}
		else
		{
			break;
		}
	}
	if ((end - start +1) >= memreq)
	{
		if (start_temp != -1)
		{
			if(tot_free <= (end - start + 1))
			{
				start = -1; end = -1;
			}
			else
			{
				start_temp = start;
				tot_free = end - start + 1;
				start = -1; end = -1;
			}
		}
		else{
			start_temp = start;
			tot_free = end - start + 1;
			start = -1; end = -1;
		}
	}
	if(i<maxmem)
	{
		goto calc;
	}
	return start_temp;
}


int memfreeWF(int memreq)
{
	int i=0, start = -1, end = -1;
	int start_temp = -1, tot_free = -1;
calc:
	start=-1, end=-1;
	for(; i<maxmem; i++)
	{
		if(mem[i] == 0)
		{
			start = i;
			break;
		}
	}
	for(; i<maxmem; i++)
	{
		if(mem[i]==0)
		{
			end = i;
		}
		else
		{
			break;
		}
	}
	if ((end - start +1) >= memreq)
	{
		if (start_temp != -1)
		{
			if(tot_free >= (end - start + 1))
			{
				start = -1; end = -1;
			}
			else
			{
				start_temp = start;
				tot_free = end - start + 1;
				start = -1; end = -1;
			}
		}
		else{
			start_temp = start;
			tot_free = end - start + 1;
			start = -1; end = -1;
		}
	}
	if(i<maxmem)
	{
		goto calc;
	}
	return start_temp;
}

int checkname(int num)
{
	int i;
	for(i=0;i<maxmem;i++)
		if(mem[i] == num)
			return 1;
	return 0;
}

void fit(int cho)
{
	int ch, jn, jm, temp;
	char fnam [5][25] = {"First Fit", "Best Fit", "Worst Fit"};
	//clrscr();
	printf("Enter Total Memory Size: ");
	scanf("%d", &maxmem);
	do{
		//clrscr();
		printmem(); fflush(stdin);
		printf("%s :\n\n1. Enter Job\n2. Remove Job\n3. Compaction\n4. Back\nEnter Your Choice: ", fnam[cho-1]);
		scanf("%d", &ch);
		switch(ch)
		{
		case 1:
			printf("\nEnter Job Number: "); scanf("%d", &jn);
			if((jn<0) || (checkname(jn) == 1))
			{
				printf("Error, Please enter a valid number!");
				getch();
				break;
			}
			printf("Enter required memory: "); scanf("%d", &jm);

			switch(cho)
			{
			case 1:
				temp = memfreeFF(jm); break;
			case 2:
				temp = memfreeBF(jm); break;
			case 3:
				temp = memfreeWF(jm); break;
			}
			if(temp == -1)
			{
				printf("\nInsufficient Memory!\n");
				getch();
			}
			else
				memalloc(jn, jm, temp);
			break;
		case 2:
			removejob();
			break;
		case 3:
			comp();
			break;
		case 4:
			return;
		default:
			printf("Wrong Choice");
			getch();
			break;
		}
	}while(ch !=4);
	getch();
}

void main()
{
	int ch=0;
	initmem();
	do{
		initmem();
		fflush(stdin); //clrscr();
		printf("\nMenu\n");
		printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
		printf("\nEnter Your Choice: ");
		scanf("%d", &ch);
		if ( (ch > 4) || (ch <1) )
			printf("Wrong Choice!\n Enter Again : ");
		else if (ch != 4)
			fit(ch);
		else
		{
			printf("Thanks!");
			break;
		}
	}while(ch != 4);
	getch();
}

/*
Output:

 Menu

1. First Fit
2. Best Fit
3. Worst Fit
4. Exit

Enter Your Choice: 1
Enter Total Memory Size: 10

░ ░ ░ ░ ░ ░ ░ ░ ░ ░


First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 1
Enter required memory: 2

█ █ ░ ░ ░ ░ ░ ░ ░ ░

1 1

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 3

█ █ █ █ █ ░ ░ ░ ░ ░

 1 1   2 2 2

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 3
Enter required memory: 3

█ █ █ █ █ █ █ █ ░ ░

1 1 2 2 2 3 3 3

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 2

Enter Job Number to remove: 2

█ █ ░ ░ ░ █ █ █ ░ ░

1 1               3 3 3

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 2

█ █ █ █ ░ █ █ █ ░ ░

1 1    2 2      3 3 3

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 2

Enter Job Number to remove: 2

█ █ ░ ░ ░ █ █ █ ░ ░

1 1               3 3 3

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 3

█ █ █ █ █ ░ ░ ░ ░ ░

 1 1  3 3 3

First Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 4

Menu

1. First Fit
2. Best Fit
3. Worst Fit
4. Exit

Enter Your Choice: 2
Enter Total Memory Size: 10

░ ░ ░ ░ ░ ░ ░ ░ ░ ░


Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 1
Enter required memory: 2

█ █ ░ ░ ░ ░ ░ ░ ░ ░

1 1

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 3

█ █ █ █ █ ░ ░ ░ ░ ░

 1 1  2 2 2

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 3
Enter required memory: 3

█ █ █ █ █ █ █ █ ░ ░

 1 1   2 2 2   3 3 3

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 2

Enter Job Number to remove: 2

█ █ ░ ░ ░ █ █ █ ░ ░

1 1               3 3 3

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 2

█ █ ░ ░ ░ █ █ █ █ █

1 1                3 3 3   2 2

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 3

█ █ █ █ █ █ █ ░ ░ ░

 1 1   3 3 3   2 2

Best Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 4


Menu

1. First Fit
2. Best Fit
3. Worst Fit
4. Exit

Enter Your Choice: 3
Enter Total Memory Size: 10

░ ░ ░ ░ ░ ░ ░ ░ ░ ░


Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 1
Enter required memory: 2

█ █ ░ ░ ░ ░ ░ ░ ░ ░

 1 1

Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 3

█ █ █ █ █ ░ ░ ░ ░ ░

 1 1  2 2 2

Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 3
Enter required memory: 3

█ █ █ █ █ █ █ █ ░ ░

 1 1   2 2 2   3 3 3

Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 2

Enter Job Number to remove: 2

█ █ ░ ░ ░ █ █ █ ░ ░

1 1               3 3 3

Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 1

Enter Job Number: 2
Enter required memory: 2

█ █ █ █ ░ █ █ █ ░ ░

 1 1   2 2      3 3 3

Worst Fit :

1. Enter Job
2. Remove Job
3. Compaction
4. Back
Enter Your Choice: 3

█ █ █ █ █ █ █ ░ ░ ░

 1 1  2 2  3 3 3

Menu

1. First Fit
2. Best Fit
3. Worst Fit
4. Exit

Enter Your Choice: 4
Thanks!


 */

 

 
