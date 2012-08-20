/*
 * +AMDG
 * This document was begun on 17 Aug 11E8, the feast of St.
 * John Eudes, and it is humbly dedicated to him to the
 * Immaculate Heart of Mary, for their prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 *
*/
/*
 * Gets Julian date and converts to Symm676.
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

#define symepoch 1721426 /* Julian day SymEpoch */
#define weekdayadj 6		/* Julian day WeekdayAdjust */
#define cyclemeanyear 365.24232082 /* CycleMeanYear for 52/293 */

long get_judate(struct tm *thetime);
long symnewyear(int symyear);

int main()
{
	struct tm *thetime;
	time_t curtime;
	curtime = time(NULL);
	thetime = localtime(&curtime);
	long firstday;	 /* first day of year */
	long judate;		/* Julian day */
	int symyear;

	judate = get_judate(thetime);
	printf("Julian day:  %d\n",judate);
	symyear = fixed_to_symyear(judate,&firstday);
	printf("Symm year:  %d\n",symyear);
	printf("First day:  %d\n",firstday);
	convtosym(judate,symyear,firstday);
	return 0;
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
	return judate;
}

/* find new year day of symyear */

long symnewyear(int symyear)
{
	int E;

	E = symyear - 1;
	return symepoch + 364.0 * E + 7.0 * ((int)(52.0 * E +
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

int convtosym(long judate, int symyear, int firstday)
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
	printf("Symday of year:  %d\n",dayofyear);
	weekofyear = (int)(dayofyear / 7.0 + 1.0);
	printf("Symweek of year:  %d\n",weekofyear);
	currquart = (int)(4.0 / 53.0 * weekofyear + 1.0);
	printf("Quarter of year:  %d\n",currquart);
	dayofquart = dayofyear - 91.0 * (currquart - 1.0);
	weekofquart = (int)(dayofquart / 7.0 + 1.0);
	printf("Day of quarter:  %d\n",dayofquart);
	printf("Week of quarter:  %d\n",weekofquart);
	monthofquart = (int)(2.0 / 61.0 * dayofquart + 1);
	printf("Month of quarter:  %d\n",monthofquart);
	symmonth = 3 * (currquart - 1) + monthofquart;
	printf("Symmonth:  %d\n",symmonth);
	printf("Leapyear:  %s\n",(issymleapyear(symyear) == 0) ? "no" : "yes");
	symday = dayofyear - daysbfmonth(symmonth);
	printf("Symday:  %d\n",symday);
	printf("SYMDATE:  %d - %d - %d\n",symyear,symmonth,symday);
}
