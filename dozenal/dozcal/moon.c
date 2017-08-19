/*
 * +AMDG
 */
/*
 * This document was begun on E July 1200, the Comm. of St.
 * Pius I, PM, and it is humbly dedicated to him and to the
 * Immaculate Heart of Mary for their prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 *
 * dozcal:  keeps a calendar with a specific internal format
 * in dozenal
 *
 * (C) Copyright 2016  Donald P. Goodman III
 *
 * This file is part of dozcal.
 *
 * dozcal is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozcal is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozcal.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"utility.h"
#include"conv.h"
#include"errcodes.h"
#include"event_struct.h"

extern struct event *event_list;
extern int recordnums;

int julian_day(int year, int month, int day);
int moonphase(int year,int month,int day);

int get_moonphases(int datenum, int moonphases)
{
	int julday;
	int phase;
	struct tm *date;
	time_t daynumber;
	char phase_str[48];
	char phasenum[3];

	phase_str[0] = '\0';
	strcat(phase_str,"Moon Phase:  ");
	daynumber = datenum * 86400;
	date = localtime(&daynumber);
	phase = moonphase(date->tm_year+1900,date->tm_mon,date->tm_mday);
//	sprintf(phasenum,"%d",phase);
	dectodoz(phasenum,(double)phase);
	strcat(phase_str,phasenum);
	if (phase == 0)
		strcat(phase_str," (new)");
	if (phase == 8)
		strcat(phase_str," (waxing half)");
	if (phase == 15)
		strcat(phase_str," (full)");
	if (phase == 22)
		strcat(phase_str," (waning half)");
	if ((moonphases == 1) || ((moonphases == 2) && ((phase == 0) 
	|| (phase == 8) || (phase == 15) || (phase == 22)))) {
		event_list = realloc(event_list,(recordnums * 
			sizeof(struct event)));
		add_to_event(phase_str,datenum,"astronomical");
	}
	return 0;
}

int moonphase(int year,int month,int day) {
	int n, i, j1, jd;
	double rad, t, t2, as, am, xtra;
	
	n = floor(12.37 * (year - 1900 + ((1.0 * month - 0.5)/12.0)));
	rad = 3.14159265 / 180.0;
	t = n / 1236.85;
	t2 = t * t;
	as = 359.2242 + 29.105356 * n;
	am = 306.0253 + 385.816918 * n + 0.010730 * t2;
	xtra = 0.75933 + 1.53058868 * n + ((1.178e-4) - (1.55e-7) * t) * t2;
	xtra += (0.1734 - 3.93e-4 * t) * sin(rad * as) - 0.4068 * sin(rad * am);
	i = (xtra > 0.0 ? floor(xtra) : ceil(xtra - 1.0));
	j1 = julian_day(year,month,day);
	jd = (2415020 + 28 * n) + i;
	return (j1 - jd + 30) % 30;
}

int julian_day(int year, int month, int day)
{
	int ja;

	if (year < 0) {year ++; }
	int jy = year;
	int jm = month + 1;
	if (month <= 2) {
		--jy;
		jm += 12;
	}
	int jul = floor(365.25 * jy) + floor(30.6001 * jm) + day + 1720995;
	if (day + 31 * (month + 12 * year) >= (15 + 31 * (10 + 12 * 1582))) {
		ja = floor(0.01 * jy);
		jul = jul + 2 - ja + floor(0.25 * ja);
	}
	return jul;
}
