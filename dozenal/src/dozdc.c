/* +AMDG */
/*
 * This document was begun on 15 January 2010, the Feast of
 * St. Paul the Hermit, and it is humbly dedicated to him
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
 */
/*
 * Basic routines for dozdc; accompanies library dozdc.h.
 */

#include<stdio.h>
#include<float.h>
#include "dozdc.h"
#include "stack.h"
#include "getop.h"
#include "conv.h"

double commandcalc(char *word, int type, int places, char expnot)
{
	int operator;
	char s[MAXLINE];
	double answer;
	char print = NOTPRINT;

	if (type == NUM) {
		push(doztodec(word));
	} else if (type == OP) {
		operator = getop(word);
		if (operator == -1) {
			fprintf(stderr,"dozdc:  unknown operator \"%s\"\n",word);
		} else {
			answer = operate(operator,&places,&print);
			if (operator == PRPOP) {
				sprintf(s,"%.*f",DBL_MAX_10_EXP,answer);
				doz(s,s,places,expnot,1);
			}
		}
	}
	return answer;
}

int runcalc(int places, char expnot)
{
	int type;
	int operator;
	char s[MAXLINE];
	double answer;
	char print = NOTPRINT;

	while ((type = gettype(s)) != EOF) {
		if (type == NUM) {
			push(doztodec(s));
		} else if (type == OP) {
			operator = getop(s);
			if (operator == -1)
				fprintf(stderr,"dozdc:  unknown operator \"%s\"\n",s);
			else
				answer = operate(operator,&places,&print);
		}
		if ((print == PRINT) || (print == PRINTNONEW)) {
			sprintf(s,"%.*f",DBL_MAX_10_EXP,answer);
			if (print == PRINT)
				doz(s,s,places,expnot,1);
			else
				doz(s,s,places,expnot,0);
			print = NOTPRINT;
		}
	}
	return EOF;
}
