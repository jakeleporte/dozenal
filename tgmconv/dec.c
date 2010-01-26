/* +AMDG */
/*
 * This program was begun on 3 January 2009, the Feast of
 * the Holy Name of Jesus, and it is humbly dedicated to Him
 * and to His Sacred Heart, for His mercy.
 *
 */
/*
 * A program to convert arbitrary dozenal numbers, floating
 * point or otherwise, into decimal.
 *
 * This program is released under the GNU General Public
 * License version 3.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include "conv.h"

int decmify(char c);
double wholedec(char *s);
double doztodec(char *s);
double fracdec(char *s);
int expkill (char *s, int expspot);
int errorcheck(char *s);
int decprecis(char *s);

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

double doztodec(char *s)
{
	int i, j;
	long endpoint;
	double decnum = 0.0;
	char sign = 0;

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
