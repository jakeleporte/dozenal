/*
 * +AMDG
 * This document was begun on 17 Aug 11E8, the feast of St.
 * John Eudes, and it is humbly dedicated to him to the
 * Immaculate Heart of Mary, for their prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 *
*/
/*
 * Handles the conversions to and from Symm676 and the
 * Gregorian calendars.
 *
 * (C) Copyright 2012  Donald P. Goodman III
 *
 * This file is part of dozdate.
 *
 * dozdate is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozdate is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozdate.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "conv.h"
#include "error_codes.h"

#define symepoch -678575.0
#define weekdayadj 4
#define cyclemeanyear 365.24232082 /* CycleMeanYear for 52/293 */
#define NEITHER 0 		/* begin symm output and input vars */
#define OUT 1
#define IN 2
#define BACK 4
#define BOTH 3				/* end symm output and input vars */

long get_judate(struct tm *thetime);
long symnewyear(int symyear);
long symmtofixed(struct tm *thetime);

int get_symmdate(struct tm *thetime,int *usesymm)
{
	long firstday;	 	/* first day of year */
	long judate;		/* Julian day */
	int symyear;

/* here to convert date to Greg from Symm */
	if ((*usesymm == IN) || (*usesymm == BOTH)) {
		if (*usesymm == BOTH)
			*usesymm = OUT;
		judate = symmtofixed(thetime);
		symyear = fixed_to_symyear(judate,&firstday);
		thetime->tm_wday = symmtoweekday(judate,firstday,thetime);
		getgregdate(judate,thetime);
		if (thetime->tm_mon == 12)
			thetime->tm_year += 1;
	}
/* here to convert date to Symm from Greg */
	if (*usesymm == OUT) {
		judate = get_judate(thetime);
		symyear = fixed_to_symyear(judate,&firstday);
		thetime->tm_wday = symmtoweekday(judate,firstday,thetime);
		convtosym(thetime,judate,symyear,firstday);
		if (thetime->tm_mday == 0) {
			thetime->tm_mon--;
			if ((thetime->tm_mon == 1) || (thetime->tm_mon == 4)
			|| (thetime->tm_mon == 7) || (thetime->tm_mon == 10))
				thetime->tm_mday = 31;
			else
				thetime->tm_mday = 30;
		}
	}
	return 0;
}

/* calc day of week from Symm date */
int symmtoweekday(long judate, int firstday, struct tm *thetime)
{
	int dayofyear;

	dayofyear = judate - firstday + 1;
	if (thetime->tm_mon == 12)
		dayofyear += 30;
	return dayofyear % 7;
}

/* convert fixed day (modJul) to Gregorian */
int getgregdate(long judate, struct tm *thetime)
{
	int z, r, g, a, b, year,month, c, day;

	judate += 2400000.5;
	z = (int)(judate - 1721118.5);
	r = judate - 1721118.5 - z;
	g = z - 0.25;
	a = (int)(g / 36524.25);
	b = a - (int)(a / 4);
	year = (int)((b + g) / 365.25);
	c = b + z - (int)(365.25 * year);
	month = (int)((5 * c + 456) / 153);
	day = c - (int)((153 * month - 457) / 5) + r;
	if (month > 12) {
		year += 1;
		month -= 12;
	}
/*	printf("year:  %d\n",year);
	printf("month:  %d\n",month);
	printf("day:  %d\n",day);
	printf("yday:  %d\n",thetime->tm_yday);*/
	thetime->tm_year = year-1900;
	thetime->tm_mon = month;
	thetime->tm_mday = day;
	return 0;
}

/* convert Symm date to fixed day (modified Julian) */
long symmtofixed(struct tm *thetime)
{
	return symnewyear(1900 + thetime->tm_year) +
		(daysbfmonth(thetime->tm_mon) + thetime->tm_mday) - 1;
}

/* get the julian day */
long get_judate(struct tm *thetime)
{
	int a,y,m,judate;
	a = (int)((14.0 - (thetime->tm_mon+1.0)) / 12.0);
	y = (1900 + thetime->tm_year) + 4800 - a;
	m = (thetime->tm_mon+1) + (12 * a) - 3;
	judate = thetime->tm_mday + (int)((153.0 * m + 2.0) / 5.0) +
		(365.0 * y) + (int)(y / 4.0) - (int)(y / 100.0) + 
		(int)(y / 400.0) - 32045.0;
	return judate - 2400000.5;
}

/* find new year day of symyear */
long symnewyear(int symyear)
{
	int E;

	E = symyear - 1;
	return symepoch + 364.0 * E + 7.0 * (int)((52.0 * E +
		146.0) / 293.0);
}
/* takes the Julian day and pointer to a long which is the
 * Julian day of the first day of the sym year; returns sym
 * year */
int fixed_to_symyear(long judate,long *firstday)
{
	int symyear;
	long startyearday;
	long startnextyear;

	symyear = (int)(((judate - symepoch) / cyclemeanyear) + 1.0);
	*firstday = symnewyear(symyear);
	if (*firstday < judate) {
		if ((judate - *firstday) >= 364) {
			startnextyear = symnewyear(symyear + 1);
			if (judate >= startnextyear) {
				symyear += 1;
				*firstday = startnextyear;
			}
		}
	} else if (*firstday > judate) {
		symyear -= 1;
		*firstday = symnewyear(symyear);
	}
	return symyear;
}

/* returns 1 if yes, 0 if no */
int issymleapyear(int symyear)
{
	if (fmod((52.0 * symyear + 146.0),293.0) < 52)
		return 1;
	else
		return 0;
}

/* returns number of days in the year before the currmonth
 * began */
int daysbfmonth(int symmonth)
{
	return 30 * symmonth + (int)(symmonth / 3) - 30;
}

int convtosym(struct tm *thetime, long judate, int symyear, int firstday)
{
	int dayofyear;
	int weekofyear;
	int currquart;
	int dayofquart;
	int weekofquart;
	int monthofquart;
	int symmonth;
	int symday;

	dayofyear = judate - firstday + 1;
	thetime->tm_yday = dayofyear;
	thetime->tm_year = symyear - 1900;
	weekofyear = (int)(dayofyear / 7.0 + 1.0);
	currquart = (int)(4.0 / 53.0 * weekofyear + 1.0);
	dayofquart = dayofyear - 91.0 * (currquart - 1.0);
	weekofquart = (int)(dayofquart / 7.0 + 1.0);
	monthofquart = (int)((2.0 / 61.0) * dayofquart + 1.0);
	symmonth = 3 * (currquart - 1) + monthofquart;
	thetime->tm_mon = symmonth - 1;
	symday = dayofyear - daysbfmonth(symmonth);
	thetime->tm_mday = symday;
	return 0;
}
