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

struct factor {
	char *name;
	char *sys;
	double factor;
} facs[] = {
	"Tim","tgm", 1.0,
	"second","metric", 0.1736111111,
	"Grafut","tgm", 1.0,
	"meter","metric", 0.2956829126,
	"foot","custom", 0.9700882959,
	"Maz","tgm", 1.0,
	"gram","metric", 0.0258503556494,
	"pound","custom", 56.9902828681,
};

struct metabbs {
	char *abb;
	char *full;
} metabbrev[] = {
	"m", "meter",
	"meters", "meter",
	"s", "second",
	"seconds", "second",
	"g", "gram",
	"grams", "gram",
	"A", "ampere",
	"amperes", "ampere",
	"K", "Kelvin",
	"mole", "mol",
	"moles", "mol",
	"cd", "candela",
	"candelas", "candela",
};

struct tgmabbs {
	char *abb;
	char *full;
} tgmabbrev[] = {
	"Gf", "Grafut",
	"Tm", "Tim",
	"Mz", "Maz",
};

/* expand metric abbreviations; cannot alter the string
 * after calling this function, since it makes the string a
 * pointer to a string literal in the struct */
int expandmetabb(char *s)
{
	int i;

	for (i=0; i < (sizeof(metabbrev) / sizeof(struct metabbs)); ++i)
		if (strcmp(s,metabbrev[i].abb) == 0 ||
		strcmp(s,metabbrev[i].full) ==0) {
			strcpy(s,metabbrev[i].full);
			return 0;
		}
	fprintf(stderr,"tgmconv:  no metric unit %s found\n",s);
	exit(1);
}

/* expand tgm abbreviations; cannot alter the string
 * after calling this function, since it makes the string a
 * pointer to a string literal in the struct */
int expandtgmabb(char *s)
{
	int i;

	for (i=0; i < (sizeof(tgmabbrev) / sizeof(struct tgmabbs)); ++i)
		if (strcmp(s,tgmabbrev[i].abb) == 0 ||
		strcmp(s,tgmabbrev[i].full) == 0) {
			s = tgmabbrev[i].full;
			return 0;
		}
	fprintf(stderr,"tgmconv:  no TGM unit %s found\n",s);
	exit(1);
}

/* get metric factors */
double dometric(char *s)
{
	int i;
	double f = 1.0;
	char *p = s;
/*	char *mets[] = {"meter", "meters", "m", "second", "seconds", 
	"s", "grams", "gram", "g",};*/

	for (i=0; i < (sizeof(metabbrev) / sizeof(struct metabbs)); ++i) {
		if (strstr(s,metabbrev[i].abb) != NULL && 
		strstr(s,metabbrev[i].abb) != s) {
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
		}
	}
	expandmetabb(s);
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
	expandtgmabb(s);
	return f;
}

double docust(char *s)
{
	return 1.0;
}

/* does the actual unit conversion itself */
double domain(char *outp, char *inp, char *to, char *from)
{
	int i;
	double f = 1.0;

	if (strcmp(to,"tgm") == 0)
		f /= dotgm(outp);
	else if (strcmp(to,"metric") == 0)
		f /= dometric(outp);
	else if (strcmp(to,"cust") == 0)
		f /= docust(outp);
	if (strcmp(from,"tgm") == 0)
		f *= dotgm(inp);
	else if (strcmp(from,"metric") == 0)
		f *= dometric(inp);
	else if (strcmp(from,"cust") == 0)
		f *= docust(inp);
	for (i=0; i < sizeof(facs) / sizeof(struct factor); ++i) {
		if (strcmp(outp,facs[i].name) == 0) {
			f *= facs[i].factor;
		} else if (strcmp(inp,facs[i].name) == 0) {
			f *= (1 / facs[i].factor);
		}
	}
	return f;
}

/* gets the final answer; returns it to main */
double getanswer(char *inp, char *outp, char *to, char *from, double value)
{
	double f = 1.0;
	int i;

	f *= domain(outp,inp,to,from);
	value *= f;
	return value;
}
