#include <stdio.h>
#include "array.h"

struct Stack
{
	int start;
	int end;
	int is_empty;
};
struct Stack stacks [3];
int s; /// s is the only variable I use for stuff that goes on the stack

int length(int i)
{
	if((stacks[i]).is_empty)
		return 0;
	return ((stacks[i]).start + ArraySize + 1 - stacks[i].end) % ArraySize;
}

void pop(int i)
{
	printf("%d\n", get((stacks[i]).end));
	if((stacks[i]).end != (stacks[i]).start)
		(stacks[i]).end = (stacks[i].end + (ArraySize - 1)) % ArraySize;
	else
	{
		(stacks[i]).end = (stacks[i]).start = -1;
		(stacks[i]).is_empty = 1;
	}
}

int is_free(int tmp)
{
	for(int j = 0; j < 3; ++j)
	{
		if((stacks[j]).is_empty)
			continue;
		if((stacks[j]).start <= (stacks[j]).end)
		{
			if((stacks[j]).start <= tmp && tmp <= (stacks[j]).end)
				return j;
		}
		else if((stacks[j]).start <= tmp || tmp <= (stacks[j]).end) 
			return j;
	}
	return -1;
}

void shift(int i)
{
	for(int j = (stacks[i]).end; 
                j != (((stacks[i]).start)+(ArraySize-1)) %ArraySize; 
                j = (j+(ArraySize-1))%ArraySize)
	{
		put((j+1)%ArraySize, get(j));
	}
	(stacks[i]).end = (((stacks[i]).end) + 1) % ArraySize;
	(stacks[i]).start = (((stacks[i]).start) + 1) % ArraySize;
}

void shift_back(int i)
{
	for(int j = (stacks[i]).start; j != (((stacks[i]).end)+1) %ArraySize; j = (j+1)%ArraySize)
		put((j+(ArraySize - 1))%ArraySize, get(j));
	(stacks[i]).start = (stacks[i].start + (ArraySize- 1)) % ArraySize;
}

void alloc_empty(int i)
{
	int tmp;
	for(int j = 0; j < ArraySize; ++j)
	{
		tmp = is_free(j);
		if(tmp == -1)
		{
			(stacks[i]).start = (stacks[i]).end = j;
			scanf("%d", &s);
			put(j, s);
			(stacks[i]).is_empty = 0;
			break;
		}
		else
			j = (stacks[tmp]).end;
	}
}
void second_shift(int fst, int snd);

int main()
{
	for(int k = 0; k < 3; ++k)// initialising stack trackers
	{
		(stacks[k]).start = (stacks[k]).end = -1;
		(stacks[k]).is_empty = 1;
	}		
	char c, x; 
	int eof_test;
	int i; 
	eof_test = getchar();
	int tmp, tmp2, tmp3;
	while(eof_test != EOF)
	{
		ungetc(eof_test, stdin);
		c = getchar();
		if(c == 'u')
		{
			scanf("%d", &i);
			if((stacks[i]).is_empty)
			{
				alloc_empty(i);
				x = getchar();
				eof_test = getchar();
				continue;
			}
			// if the stack is nonempty:
			tmp = ((stacks[i]).end + 1) %ArraySize; // where the variable has to go
			tmp2 = is_free(tmp); // what stack is using tmp if any
			// if there is space after the stack
			if(-1 == tmp2) 
			{
				(stacks[i]).end = ((stacks[i]).end + 1) % ArraySize; // incrementing the end of stack
				scanf("%d", &s); // reading what needs to go on the stack
				put((stacks[i].end), s); // putting it on the stack
			}
			// if the stack is small:
			else if (length(i) <= length(tmp2))
			{
				if(is_free(((stacks[i]).start +( ArraySize-1)) % ArraySize) == -1)
				{
					shift_back(i);
					scanf("%d",&s);
					put((stacks[i]).end, s);
				}
				else
				{
					shift(tmp2);
					(stacks[i]).end = ((stacks[i]).end + 1)%ArraySize;
					scanf("%d",&s);
					put((stacks[i].end),s);
				}
			}
			else
			{
				tmp3 = is_free((((stacks[tmp2]).end) + 1)%ArraySize); // is the slot after the next stack free
				if(-1 == tmp3) // if so shift it over and then do the thing
				{
					shift(tmp2);
					(stacks[i]).end = ((stacks[i]).end + 1) % ArraySize; // incrementing the end of stack
					scanf("%d", &s); // reading what needs to go on the stack
					put((stacks[i].end), s); // putting it on the stack
				}
				else if(length(i) > length(tmp2) + length(tmp3))
				{
					shift(tmp3);
					shift(tmp2);
					(stacks[i]).end = ((stacks[i]).end + 1)%ArraySize;
					scanf("%d",&s);
					put((stacks[i].end),s);
				}
				else
				{
					shift_back(i);
					scanf("%d", &s); // reading what needs to go on the stack
					put((stacks[i]).end, s); // putting it on the stack
				}
			}	
		}
		else 
		{
			scanf("%d", &i);
			pop(i);
		}
		getchar();
		eof_test = getchar();
	}
//	printf("\n");
//	for(int l = 0; l < ArraySize; ++l)
//		printf("%d\n",get(l));
}

// functions that actually do the shifting
//void second_shift(int fst, int snd)
//{
//
//}
