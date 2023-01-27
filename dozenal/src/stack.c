/* +AMDG */
/*
 * This document was begun on 15 January 2010, the Feast of
 * St. Paul the Hermit, and it is humbly dedicated to him
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
 */
/*
 * A program managing the stack for the dozdc program.
 *
 * (C) Copyright 2010, 2011  Donald P. Goodman III
 *
 * This file is part of dozdc.
 *
 * dozdc is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozdc is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozdc.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include"stack.h"
#include"conv.h"

#define INCREMENT 100			/* maximum depth of val stack */

static int sp = 0;				/* next free stack position */
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
		fprintf(stderr,"dozdc:  stack is full\n");
}

double pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else
		fprintf(stderr,"dozdc:  no values left on stack\n");
	return 0;
}

int clear_stack(void)
{
	sp = 0;
	return 0;
}

int print_stack(void)
{
	int tmp;
	char word[MAXLINE];

	tmp = 0;
	if (sp == 0) {
		printf("dozdc:  stack empty\n");
		return 0;
	}
	while (tmp < sp) {
		sprintf(word,"%.*f",DBL_MAX_10_EXP,stack[tmp++]);
		doz(word,word,4,0,0);
		printf(" ");
	}
	printf("\n");
	return 0;
}

int dupe_top(void)
{
	if (sp == 0) {
		fprintf(stderr,"dozdc:  nothing on stack to duplicate\n");
		return 0;
	}
	stack[sp] = stack[sp-1];
	++sp;
	return 0;
}

int swap_top(void)
{
	if (sp < 2) {
		fprintf(stderr,"dozdc:  cannot swap, less than two "
			"items on stack\n");
		return 0;
	}
	double tmp;
	tmp = stack[sp-1];
	stack[sp-1] = stack[sp-2];
	stack[sp-2] = tmp;
	return 0;
}

int clean(void)
{
	free(stack);
	stack = NULL;
	return 0;
}
