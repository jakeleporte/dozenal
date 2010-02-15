/* +AMDG */
/*
 * This document was begun on 15 January 2010, the Feast of
 * St. Paul the Hermit, and it is humbly dedicated to him
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
 */
/*
 * A program managing the stack for the dozdc program.
 */

#include<stdio.h>
#include<stdlib.h>

#define INCREMENT 100			/* maximum depth of val stack */

static int sp = 0;				/* next free stack position */
static double val[INCREMENT]; /*	value stack */
static double *stack;			/* value stack */
static int multiple = 1;		/* for memory reallocation */

/* push: push f onto value stack */
void push(double f)
{
	if (stack == NULL) {
		if ((stack = malloc(sizeof(double)*INCREMENT)) == NULL) {
			fprintf(stderr,"dozdc:  insufficient memory\n");
			exit(1);
		}
	}
	if (sp == (multiple * INCREMENT)) {
		++multiple;
		if ((stack = realloc(stack,sizeof(double)*(multiple*INCREMENT))) 
		== NULL) {
			fprintf(stderr,"dozdc:  insufficient memory\n");
		}
	}
	if(stack) {
		stack[sp++] = f;
	}
	else
		fprintf(stderr,"dozdc: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else
		fprintf(stderr,"dozdc:  no values left on stack\n");
}

int clean(void)
{
	int i;

	free(stack);
	stack = NULL;
}
