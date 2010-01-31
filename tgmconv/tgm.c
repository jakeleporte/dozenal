/* +AMDG */
/*
 * This document was begun on 18 Jan 2010, the commemoration
 * of St. Prisca, virgin and martyr; and it is humbly
 * dedicated to her and to the Immaculate Heart of Mary for
 * their prayers, and to the Sacred Heart of Jesus, for His
 * mercy.
 */
/*
 * Functions specific for tgmconv.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tgmconv.h"
#include "conv.h"

#define MAXEXP 3
#define MAXLEN 20

/* only the seven fundamental dimensions */
struct units {
	char *sys; /* the metric system in question */
	char *unit; /* the unit, in short form */
	double factor; /* the conversion factor to TGM */
} fundunits[] = {
	"metric","s",0.1736111111,
	"metric","m",0.2956829126,
	"tgm","Tm",1.0,
	"tgm","Gf",1.0,
	"cust","ft",0.9700882959,
};

/* turns elaborations on the seven fundamental dimensions
 * into the fundamental dimensions themselves */
struct convs {
	char *unit; /* the unit */
	char *base; /* the base unit */
	double factor; /* what gets from unit to base */
} convs[] = {
	"day","s",86400.0,
	"hr","s",3600.0,
	"min","s",60.0,
	"mi","ft",5280.0,
	"yd","ft",3.0,
	"in","ft",0.083333333333,
};

/* expands composite units of all systems */
struct expand {
	char *unit; /* the unit as given */
	char *full; /* the unit expanded */
} expanded[] = {
	"Vl","Gf/Tm",
	"G","Gf/Tm2",
};

/* by Lars Wirzenius at stackoverflow.com; public domain */
char *strrstr(char *s, char *t)
{
	if (*t == '\0')
		return (char *)s;
	
	char *result = NULL;
	for (;;) {
		char *p = strstr(s,t);
		if (p == NULL)
			break;
		result = p;
		s = p + 1;
	}
	return result;
}

/* get metric factors */
double dometric(char *s)
{
	int i;
	double f = 1.0;
	char *p = s;

	for (i=0; i < sizeof(fundunits) / sizeof(struct units); ++i) {
		if (strcmp(s,fundunits[i].unit) ==0) {
			return f;
		}
	}
	switch(s[0]) {
	case 'Y': f = pow(10,24); p++; break;
	case 'Z': f = pow(10,21); p++; break;
	case 'E': f = pow(10,18); p++; break;
	case 'P': f = pow(10,15); p++; break;
	case 'T': f = pow(10,12); p++; break;
	case 'G': f = pow(10,9); p++; break;
	case 'M': f = pow(10,6); p++; break;
	case 'k': f = pow(10,3); p++; break;
	case 'h': f = pow(10,2); p++; break;
	case 'd':
		if (s[1] == 'a') {
			f = pow(10,1);
			p += 2;
		} else {
			f = pow(10,-1);
			p++;
		}
		break;
	case 'c': f = pow(10,-2); p++; break;
	case 'm': f = pow(10,-3); p++; break;
	case 'u': f = pow(10,-6); p++; break;
	case 'n': f = pow(10,-9); p++; break;
	case 'p': f = pow(10,-12); p++; break;
	case 'f': f = pow(10,-15); p++; break;
	case 'a': f = pow(10,-18); p++; break;
	case 'z': f = pow(10,-21); p++; break;
	case 'y': f = pow(10,-24); p++; break;
	}
	memmove(s,p,strlen(p)+1);
	return f;
}

double dotgm(char *s)
{
	double f = 1.0;
	int i = 0;
	char exp[MAXEXP];

	while (isdozdig(s[i]) && i < MAXEXP) {
		exp[i] = s[i];
		++i;
	}
	exp[i] = '\0';
	if (s[i] == '^')
		f = pow(12,doztodec(exp));
	else if (s[i] == '_')
		f = pow(12,-doztodec(exp));
	if (strchr(s,'^') != NULL || strchr(s,'_') != NULL)
		memmove(s,s+i+1,strlen(s+i+1)+1);
	return f;
}

double docust(char *s)
{
	double f = 1.0;

	return f;
}

/* handles each unit given to it by parse() */
double dealunit(char *s, char funct)
{
	double f = 1.0;
	double interf = 1.0;
	int i = 0;
	int exp = 1; /* possible exponent on unit */

	while (!isalpha(s[i]))
		++i;
	while (isalpha(s[i]))
		++i;
	if (isdigit(s[i])) {
		exp = atoi(s+i);
		s[i] = '\0';
	}
	for (i=0; i < sizeof(convs) / sizeof(struct convs); ++i) {
		if (strcmp(s,convs[i].unit) == 0) {
			strcpy(s,convs[i].base);
			if (funct == '*')
				f /= convs[i].factor;
			else if (funct == '/')
				f *= convs[i].factor;
		}
	}
	for (i=0; i < sizeof(fundunits) / sizeof(struct units); ++i) {
		if (strstr(s,fundunits[i].unit) != NULL) {
			if (strcmp(fundunits[i].sys,"tgm") == 0) 
				interf *= dotgm(s);
			else if (strcmp(fundunits[i].sys,"cust") == 0)
				interf *= docust(s);
			else if (strcmp(fundunits[i].sys,"metric") == 0)
				interf *= dometric(s);
		}
	}
	if (funct == '*')
		f /= interf;
	else if (funct == '/')
		f *= interf;
	for (i=0; i < sizeof(fundunits) / sizeof(struct units); ++i) {
		if (strcmp(s,fundunits[i].unit) == 0) {
			if (funct == '*')
				f *= fundunits[i].factor;
			else if (funct == '/')
				f *= (1 / fundunits[i].factor);
		}
	}
	return pow(f,exp);
}

/* deal with compound units */
double parse(char *s)
{
	double f = 1.0;
	char funct = '*'; /* what to do while parsing; default multiply */
	char unit[MAXLEN]; /* each individual unit */
	int i, j = 0;

	for (i=0; i < sizeof(expanded) / sizeof(struct expand); ++i) {
		if (strcmp(expanded[i].unit,s) == 0)
			strcpy(s,expanded[i].full);
	}
	for (i=0; s[i] != '\0'; ++i) {
		if (isdozdig(s[i]) || isalpha(s[i]) || s[i]=='^' || s[i]=='_') {
			unit[j++] = s[i];
		} else {
			unit[j] = '\0';
			j = 0;
			f *= dealunit(unit,funct);
		}
		if (s[i] == '/')
			funct = '/';
	}
	unit[j] = '\0';
	f *= dealunit(unit,funct);
	return f;
}

/* does the actual unit conversion itself */
double domain(char *to, char *from)
{
	int i;
	double f = 1.0;
	char done = 0;

	f *= parse(to);
	f /= parse(from);
	return f;
}

/* gets the final answer; returns it to main */
double getanswer(char *to, char *from, double value)
{
	double f = 1.0;
	int i;

	f *= domain(to,from);
	value *= f;
	return value;
}
