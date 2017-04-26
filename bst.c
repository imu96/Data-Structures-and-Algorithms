#include "C12.h"
#include <stdio.h>
#include <stdlib.h>

void add_bst(struct node **tloc, int k, int v) {
	if(!(*tloc)) { // deals with the empty bst case
		*tloc = malloc(sizeof (struct node));
		(*tloc)->key = k;
		(*tloc)->value = v;
		(*tloc)->right = (*tloc)->left = NULL;
		return;
	}
	struct node *p = *tloc;
	int rl; // indicates which side the new node should go on
	// relative to the previous node
	while(1) { // finds which node the new node should be tacked
		// on to
		if(p->key < k) {
			if(p->right) {
				p = p->right;
			} else {
				rl = 1;
				break;
			}
		} else if (p->key == k) {
			p->value = v;
			return;
		} else {
			if(p->left) {
				p=p->left;
			} else {
				rl = 0;
				break;
			}
		}
	}
	if(rl) {
		p->right = malloc(sizeof (struct node));
		p = p->right;
	} else {
		p->left = malloc(sizeof (struct node));
		p = p->left;
	}
		p->key = k;
		p->value = v;
		p->right = p->left = NULL;
}

void pb_h(struct node *t);

void print_bst(struct node *t) {
	if(t) {
		printf("( %d", t->key);
		pb_h(t->left);
		pb_h(t->right);
		printf(" )");
	} else {
		printf("\\");
	}
}

// print bst helper function
void pb_h(struct node *t) {
	if(t) {
		printf(" ( %d", t->key);
		pb_h(t->left);
		pb_h(t->right);
		printf(" )");
	} else {
		printf(" \\");
	}
}

struct node *search_bst(struct node *t, int k) {
	struct node *p = t;
	while(p) {
		if(k == p->key) {
			return p;
		} else if (k < p->key) {
			p = p->left;
		} else {
			p = p->right;
		}
	}
	return NULL;
}
