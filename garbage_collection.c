#include <stdio.h>
#include "C11-mem.h"
#include "C11.h"

int first(int lst) {
	return memory[lst];
}

int rest(int lst) {
	return memory[lst + 1];
}

int cons(int fst, int rst) {
	if(free_list) {
		int new_free = memory[free_list+1];
		memory[free_list] = fst;
		memory[free_list + 1] = rst;
		int ret = free_list;
		free_list = new_free;
		return ret;
	} if(next_mem < MSIZE - 1) {
		memory[next_mem] = fst;
		memory[next_mem+ 1] = rst;
		int ret = next_mem;
		next_mem+=2;
		return ret;
	}
	printf("Cons: Out of memory.\n");
	return rst;
}

void give_back(int ptr) {
	memory[ptr + 1] = free_list;
	free_list = ptr;
}
