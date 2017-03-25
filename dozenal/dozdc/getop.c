/* +AMDG */
/*
 * A test for my data structures for the dozdc program.
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
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include "conv.h"
#include "dozdc.h"
#include "stack.h"
#include "vars.h"

/* the variable necessary for doing the operations */
#define NUMOPS 15

char *ops[] = {
	"+",
	"-",
	"*",
	"/",
	"%",
	"v",
	"^",
	"sin",
	"cos",
	"tan",
	"=", /* answer */
	"k", /* PRECISION */
	"pi", /* the pi constant */
	"d", /* set degrees for trig functions */
	"rad", /* set radians for trig functions */
	"ln", /* natural logarithms */
	"logx", /* base 10 logarithms */
	"asin",
	"acos",
	"atan",
	"log",
	"!", /* factorial */
	"eul", /* euler's number */
	"phi", /* golden ratio */
	"exp", /* e ^ pop() */
	"abs", /* absolute value */
	"quit", /* quits the calculator */
	"recip", /* reciprocal of previous number */
	"logb", /* arbitrary bse logs */
	"sinh",
	"cosh",
	"tanh", /* hyperbolic trig */
	"ldexp", /* x * 2^n; binary */
	"z", /* use zeniPis rather than radians */
	"dlg", /* dublog */
	"gcf", /* greatest common factor */
	"lcm", /* least common multiple */
	"atan2", /* uses two values to determine correct quadrant */
	"ceil", /* returns next integer value above */
	"floor", /* returns next integer value below */
	"max", /* returns highest of two values */
	"min", /* returns lowest of two values */
	"p", /* answer, but push it back onto the stack */
	"n", /* equivalent to "=", but with no newline */
	"~", /* divide, push both quotient and remainder */
	"c", /* clear the stack */
	"dupe", /* double the top of the stack */
	"swap", /* swap the top two values on the stack */
	"f", /* print the stack, without changing it */
};

/* refer to ops[] array to determine what operator to use;
 * pass it back to the calling function, or -1 if an error */
int getop(char *s)
{
	int i;

	for (i=0; i < (sizeof(ops)/sizeof(char *)); ++i)
		if (!strcmp(s,ops[i]))
			return i;
	if (s[0] == '#')
		return -3;
	if (s[0] == '$') {
		dealvar(s);
		return -2;
	}
	return -1;
}

/* determines whether it's a number or an operator; returns
 * the type */
int gettype(char *s)
{
	int i;
	int type = NUM;

	while (getword(s,MAXLINE-1) != EOF) {
		if (!strcmp(s,""))
			continue;
		for (i=0; s[i] != '\0'; ++i)
			if (!isdozdig(s[i]) && s[i] != '-') {
				type = OP;
			} else if (s[i] == '-') {
				if (!isdozdig(s[i+1]))
					type = OP;
			}
		s[0] == '\0';
		return type;
	}
	return EOF;
}

/* the same as gettype, but for command-line args */
int graphops(char *s, char *word, int *i)
{
	int j = 0;
	int type = NUM;

	while (isspace(s[*i]))
		++(*i);
	while (s[*i] != '\0') {
		while (!isspace(s[*i]))
			word[j++] = s[(*i)++];
		word[j] = '\0';
		for (j=0; word[j] != '\0'; ++j) {
			if (!isdozdig(word[j]) && word[j] != '-') {
				type = OP;
			} else if (word[j] == '-') {
				if (!isdozdig(word[j+1]))
					type = OP;
			}
		}
		return type;
	}
	return EOF;
}

int gcf(double num, double othnum)
{
	double quotient;
	int remainder = -1;
	int gcf;
	double large;
	double small;

	if (num > othnum) {
		large = num;
		small = othnum;
	} else {
		large = othnum;
		small = num;
	}
	while (remainder != 0) {
		remainder = (int)large % (int)small;
		large /= small;
		large = small;
		if (remainder != 0)
			small = remainder;
	}
	return small;
}

int lcm(double num, double othnum)
{
	int gcfact;
	
	gcfact = gcf(num,othnum);
	return (int) ((abs(num * othnum)) / gcfact);
}

double operate(int operator, int *places, char *print)
{
	double tmp;
	double othtmp;
	char s[MAXLINE];
	static char angletype = 2;
	long i, longtmp;

	switch (operator) {
	case ADD:
		push(pop() + pop());
		break;
	case SUBTRACT:
		tmp = pop();
		push(pop() - tmp);
		break;
	case MULT:
		push(pop() * pop());
		break;
	case DIVIDE:
		tmp = pop();
		if (tmp == 0) {
			fprintf(stderr,"dozdc:  cannot divide by 0\n");
			push(tmp);
		} else {
			push(pop() / tmp);
		}
		break;
	case TILDE:
		tmp = pop();
		if (tmp == 0) {
			fprintf(stderr,"dozdc:  cannot divide by 0\n");
			push(tmp);
		} else {
			othtmp = pop();
			push(othtmp / tmp);
			push(fmod(othtmp,tmp));
		}
		break;
	case MOD:
		tmp = pop();
		if (tmp == 0) {
			fprintf(stderr,"dozdc:  cannot divide by 0\n");
			push(tmp);
		} else {
			push(fmod(pop(),tmp));
		}
		break;
	case PRECISION:
		sprintf(s,"%d",(int)pop());
		*places = dozprecis(s);
		break;
	case SIN:
		if (angletype == 1)
			push(sin( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(sin(pop()));
		else if (angletype == 2)
			push(sin(pop() * M_PI));
		break;
	case COS:
		if (angletype == 1)
			push(cos( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(cos(pop()));
		else if (angletype == 2)
			push(cos(pop() * M_PI));
		break;
	case TAN:
		if (angletype == 1)
			push(tan( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(tan(pop()));
		else if (angletype == 2)
			push(tan(pop() * M_PI));
		break;
	case PI:
		push(M_PI);
		break;
	case DEGREES:
		angletype = 1;
		break;
	case RADIANS:
		angletype = 0;
		break;
	case ZENIPI:
		angletype = 2;
		break;
	case POW:
		push(pow(pop(),pop()));
		break;
	case SQRT:
		tmp = pop();
		if (tmp < 0) {
			fprintf(stderr,"dozdc:  cannot compute square root "
			"of negative number\n");
			push(tmp);
		} else {
			push(sqrt(tmp));
		}
		break;
	case LN:
		push(log(pop()));
		break;
	case LOGX:
		push(log10(pop()));
		break;
	case ASIN:
		tmp = pop();
		if (tmp < -1 || tmp > 1) {
			fprintf(stderr,"dozdc:  value outside proper "
			"arcsine range\n");
			push(tmp);
			break;
		}
		if (angletype == 0)
			push(asin(tmp));
		else if (angletype == 1)
			push(asin(tmp) * (180.0 / M_PI));
		else if (angletype == 2)
			push(asin(tmp) / M_PI);
		break;
	case ACOS:
		tmp = pop();
		if (tmp < -1 || tmp > 1) {
			fprintf(stderr,"dozdc:  value outside proper "
			"arccosine range\n");
			push(tmp);
			break;
		}
		if (angletype == 0)
			push(acos(tmp));
		else if (angletype == 1)
			push(acos(tmp) * (180.0 / M_PI));
		else if (angletype == 2)
			push(acos(tmp) / M_PI);
		break;
	case ATAN:
		tmp = pop();
		if (angletype == 0)
			push(atan(tmp));
		else if (angletype == 1)
			push(atan(tmp) * (180.0 / M_PI));
		else if (angletype == 2)
			push(atan(tmp) / M_PI);
		break;
	case SINH:
		if (angletype == 1)
			push(sinh( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(sinh(pop()));
		else if (angletype == 2)
			push(sinh(pop() * M_PI));
		break;
	case COSH:
		if (angletype == 1)
			push(cosh( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(cosh(pop()));
		else if (angletype == 2)
			push(cosh(pop() * M_PI));
		break;
	case TANH:
		if (angletype == 1)
			push(tanh( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(tanh(pop()));
		else if (angletype == 2)
			push(tanh(pop() * M_PI));
		break;
	case LOG:
		push(log10(pop()) / log10(12));
		break;
	case FACTORIAL:
		tmp = floor(pop());
		if (tmp == 0) {
			push(1.0);
			break;
		}
		for (i=tmp-1.0; i > 1.0; --i)
			tmp *= i;
		push(tmp);
		break;
	case EULER:
		push(exp(1.0));
		break;
	case PHI:
		push((1+sqrt(5)) / 2);
		break;
	case EXP:
		push(exp(pop()));
		break;
	case ABS:
		push(fabs(pop()));
		break;
	case QUIT:
		exit(0);
		break;
	case RECIPROCAL:
		tmp = pop();
		if (tmp == 0) {
			fprintf(stderr,"dozdc:  cannot take the reciprocal of 0\n");
			push(tmp);
		} else {
			push(1 / tmp);
		}
		break;
		break;
	case LOGB:
		tmp = pop();
		push(log10(pop()) / log10(tmp));
		break;
	case ATAN2:
		tmp = pop();
		push(atan2(pop(),tmp));
		break;
	case DLG:
		push(log10(pop()) / log10(2));
		break;
	case LDEXP:
		tmp = pop();
		push(ldexp(pop(),tmp));
		break;
	case GCF:
		push(gcf(pop(),pop()));
		break;
	case LCM:
		push(lcm(pop(),pop()));
		break;
	case CEIL:
		push(ceil(pop()));
		break;
	case FLOOR:
		push(floor(pop()));
		break;
	case MAX:
		tmp = pop();
		othtmp = pop();
		if (tmp > othtmp)
			push(tmp);
		else
			push(othtmp);
		break;
	case MIN:
		tmp = pop();
		othtmp = pop();
		if (tmp < othtmp)
			push(tmp);
		else
			push(othtmp);
		break;
	case VAR:
		break;
	case PRPOP:	/* pop the top, print it, then push it back */
		*print = PRINT;
		tmp = pop();
		push(tmp);
		return tmp;
		break;
	case DCPOP:
		*print = PRINTNONEW;
		return pop();
		break;
	case EQUALS:
		*print = PRINT;
		return pop();
		break;
	case CLEARSTACK:
		clear_stack();
		break;
	case DOUBLETOP:
		dupe_top();
		break;
	case SWAP:
		swap_top();
		break;
	case PRINTSTACK:
		print_stack();
		break;
	}
}
