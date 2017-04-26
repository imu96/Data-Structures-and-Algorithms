#include <stdio.h>
#include <stdlib.h>
#include "C7.h"

int base = 10000;
int length(struct Node *);

struct Node *reverse(struct Node *);
struct Node *a_h(struct Node *, struct Node*);

struct Node *m_h(struct Node*, struct Node*);
struct Node *m_h2(int n, struct Node*);

// purpose: prints a bignum in human readable form
// side effects: see above
// usage: print_num(cons_bigit(3, (cons_bigit (2, NULL))))
void print_num(struct Node *nlst){
	if(!nlst){
		printf("0");
		return;
	}
	if(nlst->next){
		print_num(nlst->next);
		printf("%04d",nlst->bigit);
	}
	else
		printf("%d",nlst->bigit);
}

// purpose: cons
struct Node *cons_bigit(int bgt, struct Node *nxt){
	struct Node *p = malloc(sizeof(struct Node));
	p->next = nxt;
	p->bigit = bgt;
	return p;
}

void free_num(struct Node *blst){
	struct Node *p = blst;
	struct Node *q;
	while(p->next){
		q = p->next;
		free(p);
		p = q;
	}
	free(p);
}

struct Node *copy_num(struct Node *nlst){
	if(!nlst)
		return NULL;
	struct Node* p = nlst;
	struct Node *q = malloc(sizeof(struct Node));
	q->bigit = p->bigit;
	struct Node *r = q;
	while(p->next){
		r->next = malloc(sizeof(struct Node));
		r = r->next;
		p = p->next;
		r->bigit = p-> bigit;
	}
	r->next = 0;
	return q;
}

struct Node *add (struct Node *n1lst, struct Node *n2lst){
	if(length(n1lst) >= length(n2lst))
		return a_h(n2lst,n1lst);
	return a_h(n1lst,n2lst);
}

struct Node *mult(struct Node* n1lst, struct Node* n2lst){
	if(n2lst && n1lst)
		return m_h(n2lst, n1lst);
	return NULL;
}

// purpose: returns the length of a list (bigint)
// side effects: none
// usage length(p) where p is the pointer to the beginning of a bigint
int length(struct Node *nlst){
	struct Node *p = nlst;
	int i = 0;
	while(p){
		++i;
		p = p->next;
	}
	return i;
}

//purpose: reverses a list
//side effects: sets every node n's pointer to the node m,
//	which was the pointer pointing to n
//usage: reverse(1, cons_bigit(2, cons_bigit(3, NULL)));
struct Node *reverse(struct Node *lst)
{
	struct Node *p = 0;
	struct Node *c = lst;
	struct Node *n;

	while(c)
	{
		n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
	return p;
}

struct Node *a_h(struct Node *little, struct Node *big){
	int sum, digit, carry = 0;
	// the accumulator of the bigint that is to be returned:
	struct Node *acc = NULL;
	struct Node *b = big;
	struct Node *l = little;
	int j = length(l);
	for(int i = length(b); i; --i){
//while(length(b)){
		if(j){
			sum = carry + l->bigit + b->bigit;
			digit = sum % base;
			carry = sum / base;
			acc = cons_bigit(digit, acc);
			b = b->next;
			l = l->next;
			--j;
		}
		else{
			sum = carry + b->bigit;
			digit = sum % base;
			carry = sum / base;
			acc = cons_bigit(digit, acc);
			b = b->next;
		}
	}
	if(carry)
		acc = cons_bigit(carry, acc);
	return reverse(acc);
}

struct Node *m_h2(int n, struct Node *lst){
	struct Node *p = lst;
	int sum,digit,c = 0;
	struct Node *acc = NULL;
	while(p){
		sum = c + n * p->bigit;
		c = sum / base;
		digit = sum % base;
		acc = cons_bigit(digit, acc);
		p= p->next;
	}
	if(c)
		acc = cons_bigit(c, acc);
	return reverse(acc);
}

struct Node *m_h(struct Node *a, struct Node *b){
	struct Node* acc = NULL;
	struct Node* acc2; // free up intermediate values
	int z = 0; // adding 0's for long multiplication tracker
	struct Node* sum;
	for(struct Node* i = a; i; i= i->next, ++z){
		sum = m_h2(i->bigit, b);
		for(int j = 0; j < z; ++j)
			sum = cons_bigit(0, sum);
		acc2 = acc;
		acc = add(acc, sum);
		if(acc2)
			free_num(acc2);
		free_num(sum);
	}
	return acc;
}
