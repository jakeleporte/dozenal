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

#define MAXLEN 20

/* defines the struct that contains the conversion factors */
struct convert {
	char *tounit; char *toabb; char *tosystem;
	char *fromunit; char *fromabb; char *fromsystem;
	double factor;
} factors[] = {
	{
	"Tim", "Tm", "tgm",
	"second", "s", "metric",
	0.1736111111,
	},
	{
	"Tim", "Tm", "tgm",
	"second", "s", "imperial",
	0.1736111111,
	},
	{
	"Tim", "Tm", "tgm",
	"second", "s", "custom",
	0.1736111111,
	},
	{
	"Grafut", "Gf", "tgm",
	"foot", "ft", "custom",
	0.9700882959,
	},
	{
	"Grafut", "Gf", "tgm",
	"foot", "ft", "imperial",
	0.9700882959,
	},
	{
	"Grafut", "Gf", "tgm",
	"meter", "m", "metric",
	0.2956829126,
	},
	{
	"Gee", "G", "tgm",
	"meter/second2", "m/s2", "metric",
	9.8100494007,
	},
	{
	"Gee", "G", "tgm",
	"foot/second2", "ft/s2", "custom",
	32.18520142,
	},
	{
	"Gee", "G", "tgm",
	"foot/second2", "ft/s2", "imperial",
	32.18520142,
	},
	{
	"Vlos", "Vl", "tgm",
	"meter/second", "m/s", "metric",
	1.7031335765,
	},
	{
	"Vlos", "Vl", "tgm",
	"foot/second", "ft/s", "custom",
	5.5877085843,
	},
	{
	"Vlos", "Vl", "tgm",
	"foot/second", "ft/s", "imperial",
	5.5877085843,
	},
};

struct equiv {
	char *abbrev;
	char *full;
	double factor;
} equivs[] = {
	"meter", "meter", 1.0,
	"m", "meter", 1.0,
	"second", "second", 1.0,
	"s", "second", 1.0,
	"hr", "second", 3600.0,
	"hour","second",3600.0,
	"min", "second", 60.0,
	"Tim", "Tim", 1.0,
	"Tm", "Tim", 1.0,
	"Grafut", "Grafut", 1.0,
	"Gf", "Grafut", 1.0,
	"G", "Gee", 1.0,
	"Gee", "Gee", 1.0,
	"m/s2","m/s2",1.0,
	"foot","foot",1.0,
	"ft","foot",1.0,
	"mile","foot", 5280.0,
	"mi","foot", 5280.0,
	"inch","foot",0.0833333333,
	"in","foot",0.0833333333,
	"ft/s2","ft/s2",1.0,
	"Vlos","Vlos", 1.0,
	"Vl","Vlos",1.0,
	"m/s","m/s",1.0,
	"ft/s","ft/s",1.0,
};

int isdozdig(char c)
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4': case
	'5': case '6': case '7': case '8': case '9': case 'A':
	case 'a': case 'B': case 'b': case 'X': case 'x': case
	'E': case 'e': case 'T': case 't': case ';':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

/* determines whether the string contains a cust. or imp. unit */
int iscustunit(char *s)
{
	char *custimp[] = {
		"mile", "miles", "mi", "inch", "inches", "foot", "feet",
		"ft","in","ft/s2","min","hr","hour","ft/s",
	};
	int i;

	for (i=0; i < (sizeof(custimp)/sizeof(char *)); ++i) {
		if (!strcmp(s,custimp[i]))
			return 1;
	}
	return 0;
}

/* converts TGM units into its appropriate factor; returns it */
double gettgm(char *s)
{
	double f = 1.0;
	int i;
	char *p;
	char incdec;
	char fact[5];

	if ((p = strchr(s,'^')) || (p = strchr(s,'_'))) {
		switch (*p) {
			case '^': incdec = 0; break;
			case '_': incdec = 1; break;
		}
		for (i=0; isdozdig((fact[i] = s[i])) && i <= 4; i++);
		fact[i] = '\0';
		f = doztodec(fact);
		switch (incdec) {
			case 0: f = pow(12,f); break;
			case 1: f = 1 / pow(12,f); break;
		}
		memmove(s,p+1,strlen(p+1)+1);
	}
	return f;
}

/* extracts the appropriate factor from a metric unit */
double getmetric(char *s)
{
	double factor = 1.0;

	if (*(s+1) != '\0' && *(s+1) != '/') {
		switch (*s) {
		case 'Y': factor = pow(10,24); break;
		case 'Z': factor = pow(10,21); break;
		case 'E': factor = pow(10,18); break;
		case 'P': factor = pow(10,15); break;
		case 'T': factor = pow(10,12); break;
		case 'G': factor = pow(10,9); break;
		case 'M': factor = pow(10,6); break;
		case 'k': factor = pow(10,3); break;
		case 'h': factor = pow(10,2); break;
		case 'd':
			if (*(s+1) == 'a') {
				factor = pow(10,1);
				++s;
			} else
				factor = pow(10,-1);
			break;
		case 'c': factor = pow(10,-2); break;
		case 'm': factor = pow(10,-3); break;
		case 'u': factor = pow(10,-6); break;
		case 'n': factor = pow(10,-9); break;
		case 'p': factor = pow(10,-12); break;
		case 'f': factor = pow(10,-15); break;
		case 'a': factor = pow(10,-18); break;
		case 'z': factor = pow(10,-21); break;
		case 'y': factor = pow(10,-24); break;
		}
		if (factor != 1.0)
			memmove(s,s+1,strlen(s+1)+1);
	}
	return factor;
}

/* determines if string represents a TGM unit */
int istgm(char *s)
{
	int i;
	char *tgm[] = {
		"Grafut", "Gf", "Tim", "Tm", "Gee", "G","Vlos","Vl",
	};

	if (strchr(s,'^') || strchr(s,'_'))
		return 1;
	for (i=0; i < (sizeof(tgm)/sizeof(char *)); ++i) {
		if (!strcmp(s,tgm[i]))
		return 1;
	}
	return 0;
}

/* takes string of unit as input, returns appropriate
 * conversion factor, combined with that from gettgm() or
 * getmetric() as necessary */
double getunits(char *s)
{
	int i;
	double f = 0.0;

	if (istgm(s))
		f = gettgm(s);
	else if (iscustunit(s));
	else
		f = getmetric(s);
	for (i=0; i < (sizeof(equivs)/sizeof(struct equiv)); ++i)
		if (!strcmp(s,equivs[i].abbrev)) {
			strcpy(s,equivs[i].full);
			if (f == 0.0)
				return equivs[i].factor;
		}
	if (f == 0.0) {
		fprintf(stderr,"tgmconv:  unit %s not found\n",s);
		exit(1);
	} else {
		return f;
	}
}

/* if output unit is given by system, rather than by unit */
int getsystem(char *to, char *from)
{
	int i;
	char changed = 0;

	for (i=0; i < (sizeof(factors)/sizeof(struct convert)); ++i) {
		if (!strcmp(to,factors[i].tosystem) &&
		(!strcmp(from,factors[i].fromunit) ||
		!strcmp(from,factors[i].fromabb))) {
			strcpy(to,factors[i].tounit);
			changed = 1;
		} else if (!strcmp(to,factors[i].fromsystem) &&
		(!strcmp(from,factors[i].tounit) ||
		!strcmp(from,factors[i].toabb))) {
			strcpy(to,factors[i].fromunit);
			changed = 1;
		}
	}
	if (changed == 1)
		printf("tgmconv:  printing output as %ss\n",to);
	return 0;
}

double getslash(char *s)
{
	int i, j;
	char presl[MAXLEN]; /* units before the slash */
	char postsl[MAXLEN]; /* units after the slash */
	double f = 1.0;
	size_t len;
	char finalpre[2] = " ";
	char finalpost[2] = " ";

	for (i=0; s[i] != '/'; ++i)
		presl[i] = s[i];
	presl[i++] = '\0';
	for (j=0; s[i] != '\0'; ++i,++j)
		postsl[j] = s[i];
	postsl[j] = '\0';
	len = strlen(postsl) - 1;
	if (postsl[len] == '2') {
		finalpost[0] = '2';
		postsl[len] = '\0';
	}
	if (presl[len] == '2') {
		finalpre[0] = '2';
		presl[len] = '\0';
	}
	f /= getunits(postsl);
	f *= getunits(presl);
	if (finalpost[0] != ' ')
		strcat(postsl,finalpost);
	if (finalpre[0] != ' ')
		strcat(presl,finalpre);
	strcat(presl,"/"); /* FIXME:  no bounds checking */
	strcat(presl,postsl);
	strcpy(s,presl);
	return f;
}

/* once we've got the units and the value, converts it,
 * returns the answer as double */
double getanswer(char *to, char *from, double value)
{
	int i;
	double fromfactor = 1.0;
	double tofactor = 1.0;

	if (strstr(from,"/") != NULL)
		fromfactor = getslash(from);
	else
		fromfactor = getunits(from);
	getsystem(to,from);
	if (strstr(to,"/") != NULL)
		tofactor = getslash(to);
	else
		tofactor = getunits(to);
	for (i=0; i < (sizeof(factors)/sizeof(struct convert)); ++i) {
		if (!strcmp(from,factors[i].fromunit) && 
		!strcmp(to,factors[i].tounit)) {
			return (value / tofactor) * (fromfactor / factors[i].factor);
		} else if (!strcmp(to,factors[i].fromunit) &&
		!strcmp(from,factors[i].tounit)) {
			return (value * fromfactor) * (factors[i].factor / tofactor);
		}
	}
	fprintf(stderr,"tgmconv:  no conversion factor for %s to "
	"%s exists\n",from,to);
	exit(1);
}
