<<<<<<< HEAD:dozenal/doz/doz.c
=======
/* +AMDG */
/* This program was begun on 2 January 2009, the ninth day
 * of Christmas, and it is humbly dedicated to the
 * Immaculate Heart of Mary for her prayers, and to the
 * Child Jesus for His mercy.
 */
/*
 * A program for converting arbitrary decimal numbers, up to
 * and including floating point and exponential notation,
 * into dozenal.
 *
 * This program is licensed under the GNU General Public
 * License, version 3.
 */

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include "conv.h"

char dozenify(char num);
int dectodoz(char *doznum, double decnum);
int dozprecis(char *s);
int expnotate(char *s);
int negexp(char *s, int zenspot);
int posexp(char *s, int zenspot);

int doz(char *s, char *t, int places, int expnot)
{
	double decnum;
	int i;
	int precise;
	size_t length;

	decnum = atof(t);
	if (decnum >= (DBL_MAX)) {
		fprintf(stderr,"doz:  requested value too high; "
		"reducing to highest possible value, %f\n",DBL_MAX);
		decnum = DBL_MAX;
	} else if (decnum <= -DBL_MAX) {
		fprintf(stderr,"doz:  requested value too low; "
		"increasing to lowest possible value, %f\n",-DBL_MAX);
		decnum = DBL_MAX * -1;
	}
	dectodoz(s, decnum);
	if (expnot == 1)
		expnotate(s);
	for (i=0; s[i] != ';' && s[i] != '\0'; ++i)
		putchar(s[i]);
	if (s[i] == ';') {
		precise = i + places;
		for (i=i; i <= precise && s[i] != '\0'; ++i)
			putchar(s[i]);
		if (expnot == 1 && s[i] != '\0') {
			for (i=0; s[i] != 'e'; ++i);
			if (s[i+1] == 'e')
				++i;
			for (i=i; s[i] != '\0'; ++i)
				putchar(s[i]);
		}
	}
	putchar('\n');
	return 0;
}

int expnotate(char *s)
{
	int i;
	int zenspot = 1; /* ensures new zenimal point in right place */

	if (*s == '-')
		zenspot = 2;
	if (*(s+zenspot-1) == '0' && *(s+zenspot) == ';') {
		if (zenspot == 2) {
			memmove(s+1,s,strlen(s));
			*s = '-';
			++s;
		}
		negexp(s, zenspot);
	} else {
		posexp(s, zenspot);
	}
	return 0;
}

int posexp(char *s, int zenspot)
{
	int i;
	char origspot = 0; /* where zenimal is originally */
	char zensuf[5]; /* to cat onto the string */

	for (i=0; *(s+i) != ';' && *(s+i) != '\0'; ++i);
	origspot = i;
	if (origspot == (strlen(s))) {
		*(s+origspot) = ';';
		*(s+origspot+1) = '0';
		*(s+origspot+2) = '\0';
	}
	for (i=origspot; *(s+i) != '\0'; ++i)
		*(s+i) = *(s+i+1);
	for (i=strlen(s); i >= zenspot; --i)
		*(s+i) = *(s+i-1);
	*(s+zenspot) = ';';
	*(s+strlen(s)+1) = '\0';
	*(s+strlen(s)) = 'e';
	dectodoz(zensuf, origspot - zenspot);
	strcat(s,zensuf);
	return 0;
}

int negexp(char *s, int zenspot)
{
	int i, j = 0;
	int origspot = 0; /* where zenimal is originally */
	char zensuf[5]; /* to cat onto the string */

	for (i=0; *(s+zenspot+1+i) == '0' && *(s+zenspot+1+i) != '\0'; ++i);
	if (*(s+zenspot+1+i) == '\0') {
		for (j=zenspot+1+i; j<(zenspot+1+i+10); ++j)
			s[j] = '0';
		s[j] = '\0';
	}
	origspot = i = i + zenspot + 1;
	j = 0;
	*(s+(j++)) = *(s+(i++));
	*(s+(j++)) = ';';
	for (j=j,i=i; *(s+i) != '\0'; ++j,++i)
		*(s+j) = *(s+i);
	if (s[j] == ';')
		s[j++] = '0';
	*(s+(j++)) = 'e';
	*(s+j) = '\0';
	dectodoz(zensuf,zenspot - origspot);
	strcat(s,zensuf);
	return 0;
}

int dozprecis(char *s)
{
	int i;

	if (s == NULL)
		return -1;
	for (i=0; i <= strlen(s) - 1; ++i)
		if (!isdigit(*(s+i)))
			return -1;
	if (atoi(s) > DBL_MAX_10_EXP) {
		fprintf(stderr,"doz:  requested precision too high; "
			"truncating to maximum %d\n",DBL_MAX_10_EXP);
		return DBL_MAX_10_EXP;
	}
	return atoi(s);
}

char dozenify(char num)
{
	switch (num) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
	case 7: case 8: case 9:
		return (num % 10) + '0';
	case 10: 
		return 'X'; 
	case 11:
		return 'E';
	}
}

int dectodoz(char *doznum, double decnum)
{
	int i = 0; int sign = 0; int j = 0;
	double wholedec; /* whole number portion of decnum */
	double partholder; /* someplace for modf to dump integral */

	if (decnum < 0) {
		decnum = -decnum;
		sign = 1;
	}
	partholder = modf(decnum,&wholedec);
	decnum -= wholedec;
	while (wholedec >= 12) {
		*(doznum+(i++)) = dozenify(fmod(wholedec,12.0));
		wholedec /= 12;
	}
	*(doznum+(i++)) = dozenify(fmod(wholedec,12));
	if (sign == 1)
		*(doznum+(i++)) = '-';
	*(doznum+i) = '\0';
	reverse(doznum);
	if (decnum > 0) {
		if ((decnum - round(decnum)) >= DBL_MIN)
			decnum += DBL_EPSILON;
		*(doznum+(i++)) = ';';
		for (i=i; i <= DBL_MAX_10_EXP; ++i) {
			*(doznum+i) = dozenify((int)(decnum * 12));
			decnum = modf(decnum*12,&partholder);
		}
		*(doznum+i) = '\0';
	}
	return 0;
}
