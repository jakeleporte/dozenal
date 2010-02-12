/* +AMDG */
/*
 * A test for my data structures for the dozdc program.
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
int commandops(char *s, char *word)
{
	static int i = 0;
	int j = 0;
	int type = NUM;

	while (isspace(s[i]))
		++i;
	while (s[i] != '\0') {
		while (!isspace(s[i]))
			word[j++] = s[i++];
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

double operate(int operator, int *places, char *print)
{
	double tmp;
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
		break;
	case COSH:
		if (angletype == 1)
			push(cosh( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(cosh(pop()));
		break;
	case TANH:
		if (angletype == 1)
			push(tanh( M_PI * (pop() / 180.0) ) );
		else if (angletype == 0)
			push(tanh(pop()));
		break;
	case LOG:
		push(log10(pop()) / log10(12));
		break;
	case FACTORIAL:
		longtmp = (long)pop();
		for (i=longtmp-1; i > 0; --i)
			longtmp *= i;
		push(longtmp);
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
	case DLG:
		push(log10(pop()) / log10(2));
		break;
	case LDEXP:
		tmp = pop();
		push(ldexp(pop(),tmp));
		break;
	case VAR:
		break;
	case EQUALS:
		*print = PRINT;
		return pop();
		break;
	}
}
