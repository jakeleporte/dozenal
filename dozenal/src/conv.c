/* +AMDG */
/*
 * This file was begun on 13 January 2009, the commemoration
 * of the Baptism of Our Lord, and it is humbly dedicated to
 * the Immaculate Heart of Mary for her prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 */
/*
 * Contains the code for some basic routines for conversion
 * of dozenal numbers to decimal and vice-versa.  Part of
 * the dozenal package.
 *
 * (C) Copyright 2010, 2011  Donald P. Goodman III
 *
 * This file is part of dec.
 *
 * dec is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dec is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dec.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include "conv.h"

int doz(char *s, char *t, int places, int expnot, int new)
{
	double decnum;
	int i;
	int precise;

	decnum = atof(t);
	if (decnum > (DBL_MAX)) {
		fprintf(stderr,"doz:  requested value too high; "
		"reducing to highest possible value, %f\n",DBL_MAX);
		decnum = DBL_MAX-1;
	} else if (decnum < -DBL_MAX) {
		fprintf(stderr,"doz:  requested value too low; "
		"increasing to lowest possible value, %f\n",-DBL_MAX);
		decnum = -DBL_MAX+1;
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
	if (new == 1)
		putchar('\n');
	return 0;
}

int expnotate(char *s)
{
	int zenspot = 1; /* ensures new zenimal point in right place */

	if (*s == '-')
		zenspot = 2;
	if (s[zenspot] == ';')
		negexp(s,zenspot);
	else
		posexp(s,zenspot);
	return 0;
}

int posexp(char *s, int zenspot)
{
	int i=0;
	char zensuf[5]; /* to cat onto the string */
	char *orig; /* pointer to original zenimal spot */

	orig = strchr(s,';');
	if (orig == NULL) {
		i = strlen(s) - zenspot;
		s[strlen(s)+1] = '\0';
		memmove(s+zenspot+1,s+zenspot,strlen(s+zenspot));
		*(s+zenspot) = ';';
	} else {
		i = orig - s - zenspot;
		s[strlen(s)+1] = '\0';
		memmove(orig,orig+1,strlen(orig+1));
		s[strlen(s)+1] = '\0';
		memmove(s+zenspot+1,s+zenspot,strlen(s+zenspot));
		*(s+zenspot) = ';';
	}
	strcat(s,"e");
	dectodoz(zensuf,i);
	strcat(s,zensuf);
	return 0;
}

int negexp(char *s, int zenspot)
{
	int i = 0;
	int origspot = 0; /* where zenimal is originally */
	char zensuf[5]; /* to cat onto the string */
	char *orig; /* pointer to original zenimal point */

	orig = strchr(s,';'); /* can't be null, or would be posexp */
	origspot = orig - s + 1;
	if (s[zenspot-1] == '0') {
		memmove(s+zenspot+1,s+zenspot,strlen(s+zenspot+1));
		for (i=0;s[i]=='0'||s[i]==';'||s[i]=='-';++i); /* first non-zero */
		if (*s == '-')
			memmove(s+1,s+i,strlen(s+i));
		else
			memmove(s,s+i,strlen(s+i));
		memmove(s+zenspot,s+zenspot-1,strlen(s+zenspot));
		*(s+zenspot) = ';';
	} else if (s[zenspot] == ';') {
		origspot = 0;
		i = 0;
	} else { /* FFF */
		for (i=0;s[i]=='0'||s[i]==';'||s[i]=='-';++i); /* first non-zero */
	}
	strcat(s,"e");
	dectodoz(zensuf,origspot-i);
	strcat(s,zensuf);
	return 0;
}

int dozprecis(char *s)
{
	int i;
	int precis;

	if (s == NULL)
		return -1;
	for (i=0; i <= strlen(s) - 1; ++i)
		if (!isdozdig(*(s+i)))
			return -1;
	precis = (int)doztodec(s);
	if (precis > DBL_MAX_10_EXP) {
		fprintf(stderr,"doz:  requested precision too high; "
			"truncating to maximum %d\n",DBL_MAX_10_EXP);
		return DBL_MAX_10_EXP;
	}
	return precis;
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
	return '?';
}

int dectodoz(char *doznum, double decnum)
{
	int i = 0; int sign = 0;
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
		*(doznum+(i++)) = ';';
		for (i=i; i <= DBL_MAX_10_EXP; ++i) {
			decnum = modf(decnum*12,&partholder);
			*(doznum+i) = dozenify(partholder);
		}
		*(doznum+i) = '\0';
	}
	return 0;
}

int dec(char *p, int places, char expnot)
{
	if (expnot == 1)
		printf("%.*e\n",places,doztodec(p));
	else
		printf("%.*f\n",places,doztodec(p));
	return 0;
}

int decprecis(char *s)
{
	int i;
	size_t length;

	if (s == NULL)
		return -1;
	length = strlen(s) -1;
	for (i=0; i <= length; ++i)
		if (!isdigit(*(s+i)))
			return -1;
	if (atoi(s) > DBL_MAX_10_EXP) {
		fprintf(stderr,"dec:  requested precision too high; "
			"truncating to maximum %d\n",DBL_MAX_10_EXP);
		return DBL_MAX_10_EXP;
	}
	return atoi(s);
}

/* convert exponential notation to normal b/f processing */
int expkill(char *s, int expspot)
{
	int i;
	size_t origend;
	int tmp;
	int exp;
	int semi;
	char newnum[2*MAXLINE+1] = "";

	exp = doztodec(s+expspot+1);
	for (semi=0; s[semi] != ';' && s[semi] != '\0'; ++semi)
		continue;
	s[expspot] = '\0';
	origend = strlen(s) - 1;
	if (exp > DBL_MAX_10_EXP || exp < -DBL_MAX_10_EXP) {
		fprintf(stderr,"dec:  exponent too high, reducing to "
		"maximum %d\n",DBL_MAX_10_EXP);
		exp = (exp < 0) ? -DBL_MAX_10_EXP : DBL_MAX_10_EXP;
	}
	if (exp > 0) {
		memmove(s+semi,s+semi+1,strlen(s+semi));
		if (origend > (semi+exp)) {
			memmove(s+semi+exp+1,s+semi+exp,strlen(s+semi+exp));
			s[semi+exp] = ';';
		} else {
			for (i=semi+exp-1; i >= origend; --i)
				s[i] = '0';
			s[semi+exp] = '\0';
		}
	} else if (exp < 0) {
		memmove(s+semi,s+semi+1,strlen(s+semi));
		tmp = semi + exp;
		strcat(newnum,s);
		for (i=0; i < (-tmp+2); ++i)
			s[i] = '0';
		s[i] = '\0';
		s[1] = ';';
		strcat(s,newnum);
	}
	return 0;
}

int errorclear(char *s)
{
	int i;
	char *p;

	if ((p = strchr(s,'e')) != NULL) {
		if (strchr(s,';') == NULL) {
			fprintf(stderr,"dec:  exponential "
			"notation requires a zenimal point, "
			"\';\', and at least one trailing "
			"digit\n");
			return 0;
		} else if (p != strrchr(s,'e')) {
			fprintf(stderr,"dec:  'e' cannot be "
			"used as a dozenal digit\n");
			return 0;
		}
	}
	for (i=0; s[i] != '\0'; ++i) {
		if (!isdozdig(s[i]) && s[i] != 'e' && s[i] != '-') {
			fprintf(stderr,"dec:  %s contains "
			"%c, which is not a valid dozenal "
			"character\n",s,s[i]);
			return 0;
		}
	}
	return 1;
}

double doztodec(char *s)
{
	int i, j;
	long endpoint;
	double decnum = 0.0;
	char sign = 0;

	if (!errorclear(s))
		exit(1);
	if (*s == '-') {
		sign = 1;
		s++;
	}
	for (i=0; *(s+i) != '\0'; ++i)
		if (*(s+i) == 'e')
			expkill(s,i);
	for (i=0; *(s+i) != ';' && *(s+i) != '\0'; ++i);
	endpoint = i;
	if (*(s+endpoint) != '\0') {
		decnum += fracdec(s+endpoint+1);
		*(s+endpoint) = '\0';
	}
	decnum += wholedec(s);
	return (sign == 0) ? decnum : decnum * -1;
}

double wholedec(char *s)
{
	int i=0;
	char c;
	double decnum = 0.0; /* final result to return */

	i = 0;
	while ((c = s[i++]) != '\0' && c != ';')
		decnum = decnum * 12 + decmify(c);
	return decnum;
}

double fracdec(char *s)
{
	int i;
	double divisor = 1.0;

	for (i=0; *(s+i) != '\0'; ++i)
		divisor *= 12.0;
	return wholedec(s) / divisor;
}

int decmify(char c)
{
	switch (c) {
	case '0': return 0; break;
	case '1': return 1; break;
	case '2': return 2; break;
	case '3': return 3; break;
	case '4': return 4; break;
	case '5': return 5; break;
	case '6': return 6; break;
	case '7': return 7; break;
	case '8': return 8; break;
	case '9': return 9; break;
	case 'X': case 'x': case 'T': case 't': case 'A': case
	'a':
		return 10; break;
	case 'E': case 'B': case 'b':
		return 11; break;
	default: return 0; break;
	}
}

void reverse(char *s)
{
	int i, j;
	char tmp;
	size_t length;

	length = strlen(s) - 1;
	for (i=0, j=length; i<j; ++i, --j) {
		tmp = *(s+i);
		*(s+i) = *(s+j);
		*(s+j) = tmp;
	}
}

int getword(char *s, int lim)
{
	int c, i;

	--lim;
	for (i=0; (c=getchar())!=EOF && c!='\n' && c!='\t' && c!=' '; ++i) {
		if (i < lim-1)
			*(s+i) = c;
		else if (i == lim)
			*(s+i) = '\0';
	}
	if (c == EOF)
		return EOF;
	if (i < lim)
		*(s+i) = '\0';
	return i;
}

int isdozdig(char c)
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4': case
	'5': case '6': case '7': case '8': case '9': case 'A':
	case 'a': case 'B': case 'b': case 'X': case 'x': case
	'E': case 'e': case 'T': case 't': case ';': case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}
