#include <string.h>
#include "C10.h"
#include <stdlib.h>

struct hash make_table(int s) {
	struct hash h;
	struct anode **tab = malloc(s * sizeof(struct anode *));
	h.size = s;
	h.table = tab;
	for(int i = 0; i < s; ++i) {
		tab[i] = 0;
	} 
	return h;
}

struct anode *search_array(int k, struct anode *arr) {
	for(struct anode * ptr = arr; ptr; ptr = ptr->next) {
		if(ptr->key == k) {
			return ptr;
		}
	}
	return NULL;
}

char *search(struct hash T, int k) {
	struct anode * p = search_array(k, T.table[k%(T.size)]);
	if(p) {
		char * c = p->value;
		return c;
	}
	return NULL;
}

void add(struct hash T, int k, char *v) {
	int i = k%(T.size);
	struct anode * tmp = (T.table)[i];
	struct anode * s = search_array(k, (T.table)[i]);
	if(!s) {
		s = malloc(sizeof(struct anode));
		s->key = k;
		s->next = tmp;
		(T.table)[i] = s;
	} else {
		free(s->value);
	}
	s->value = malloc(1 + strlen(v));
	strcpy(s->value, v);
}

void free_table(struct hash T) {
	struct anode * tmp;
	for(int i = 0; i < T.size; ++i) {
		for(struct anode * ptr = (T.table)[i]; ptr; ptr = tmp) { 
			tmp = ptr->next;
			free(ptr->value);
			free(ptr);
		}
	}
	free(T.table);
}

void delete(struct hash T, int k) {
	int i = k%(T.size);
	struct anode * ptr = (T.table)[i];
	struct anode * p = 0;
	struct anode * n = ptr;
	for(; ptr; ptr = n) {
		if(n) {
			n = n->next;
		}
		if(ptr->key == k) {
			free(ptr->value);
			free(ptr);
			if(p) {
				p->next = n;
			} else {
				(T.table)[i] = n;
			}
			return;
		}
		p = ptr;
	}
}
