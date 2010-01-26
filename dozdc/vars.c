/* +AMDG */
/*
 * This document was begun on 23 January 2010, the feast of
 * St. Raymund of Penafort, and it is humbly dedicated to
 * him and to the Immaculate Heart of Mary for their
 * prayers, and to the Sacred Heart of Jesus for His mercy.
 */
/*
 * The variable-handling functions and structs for dozdc.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include "stack.h"

#define MAXVARS 50
#define MAXCHARS 30

struct var {
	char name[MAXCHARS]; /* name of the variable */
	double val; /* value of the variable */
};

static struct var vars[MAXVARS];
static int varindex = 0; /* variable stack index */

int dealvar(char *s)
{
	int i;

	for (i=0; i <= varindex; ++i) {
		if (!strcmp(s,vars[i].name)) {
			push(vars[i].val);
			return 0;
		}
	}
	newvar(s);
	return 0;
}

int newvar(char *s)
{
	if (varindex < MAXVARS) {
		strncpy(vars[varindex].name,s,MAXCHARS-1);
		if (strlen(s) > (MAXCHARS-1))
			vars[varindex].name[MAXCHARS] = '\0';
		vars[varindex].val = pop();
		++varindex;
	} else {
		fprintf(stderr,"dozdc:  too many variables; cannot "
		"save variable %s\n",s);
		return 1;
	}
	return 0;
}
