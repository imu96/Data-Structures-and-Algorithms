#include "C6.h"
//#include <stdio.h>

//struct Node
//{
//	int data;
//	struct Node * next;
//};

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

//int main() 
//{
//	struct Node n1 = {1, 0};
//	struct Node n2= {2, &n1};
//	struct Node n3= {3, &n2};
//
//	printf("%d\n", (n2.next)->data);
//	struct Node * p = reverse(&n3);
//
//	printf("%d\n", (n2.next)->data);
//}
