#include <stdio.h>
#include "C8.h"

void printNums(int m, int n){ // note this code doesn't work for m = 0
	// variables for checking square-free condition
	int k;
	int s;
	// variables for checking palindrome condition
	int acc1;
	int acc2;
	int r;
	int exp = 1;
	int exp1;
	int exp2;
	int q;

	int i= m-1;
	if(i == -1)
		goto Degenerate;
	goto Start;

Degenerate: printf("0\n");
	    ++i;

Start: 	++i;
	if(i < 0)
		return;
	if(i > n)
 		return;
	if(i % 4 == 0)
		goto Start;

	acc1 = acc2 = 0;

	if(i % 10 == 0)
		goto Start;
	exp2= 10;
Exp: if(exp == 1000000000)
	     goto Skip;
     if((exp *= 10) < i)
	     goto Exp;
     exp /= 10;
Skip: exp1 = exp;

Check: if(exp1 == 1)
	       goto Square;
       q = (i/ exp1) % 10;
       acc1 = (acc1 * 10) + q;

       r = (i % exp2) / (exp2 / 10);
       acc2 = (acc2 * 10) + r;

       if(acc2 - acc1)
	       goto Start;

       exp1 /= 10;
       exp2 *= 10;       
       goto Check;

Square: k = 3;
CheckSquare: s = k*k;
	     if(i % s == 0)
		     goto Start;
	     if(s > i)
		     goto Print;
	     if(s < 0)
		     goto Print;
	     k += 2;
	     goto CheckSquare;

Print: printf("%d\n",i);
       goto Start;
}
