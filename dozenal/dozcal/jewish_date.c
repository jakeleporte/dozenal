/*
 * +AMDG
 */
/*
 * This document was begun on 12 July 1200, the feast of St.
 * Bonaventure, ECD, and it is humbly dedicated to him and
 * to the Immaculate Heart of Mary for their prayers, and to
 * the Sacred Heart of Jesus for His mercy.
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
#include<string.h>
#include<time.h>
#include<math.h>
#include"utility.h"

int get_israel_holydays(int daynum);
int is_jew_leap(int hebyear);

int jew_holidays(int daynum)
{
	get_israel_holydays(daynum);
	return 0;
}

int get_israel_holydays(int daynum)
{
	struct tm *date;
	time_t datesecs;
	int a; int A; int b; int M;
	double m; double y; double x;
	int c;

	datesecs = daynum * 86400;
	date = localtime(&datesecs);
	A = date->tm_year + 1900 + 3760;
	a = (12 * A + 17) % 19;
	b = A % 4;
	y = 32 + (4343.0 / 98496.0) + ((1 + (272953.0 / 492480.0)) * (double)a)
		+ ((double)b / 4.0) - ((313.0 / 98496.0) * (double)A);
	m = modf(y,&x);
	M = (int)x;
	c = ((3 * A) + (5 * b) + M + 5) % 7;
	if ((c == 2) || (c == 4) || (c == 6)) {
		date->tm_mday = M + 1 + 13-1;
	} else if ((c == 1) && (a > 6) && (m >= (1367/2160))) {
		date->tm_mday = M + 2 + 13-1;
	} else if ((c == 0) && (a > 11) && (m >= 23269/25920)) {
		date->tm_mday = M + 1 + 13-1;
	} else {
		date->tm_mday = M + 13-1;
	}
	date->tm_mon = 2;
	mktime(date);
	mktime(date);
	add_to_event("Passover (sundown)", get_datenum(date), "religious");
	add_to_event("Passover", get_datenum(date)+1, "religious");
	add_to_event("Passover", get_datenum(date)+2, "religious");
	add_to_event("Passover", get_datenum(date)+3, "religious");
	add_to_event("Passover", get_datenum(date)+4, "religious");
	add_to_event("Passover", get_datenum(date)+5, "religious");
	add_to_event("Passover", get_datenum(date)+6, "religious");
	add_to_event("Passover", get_datenum(date)+7, "religious");
	add_to_event("Passover", get_datenum(date)+8, "religious");
	date->tm_mday = date->tm_mday - 30;
	mktime(date);
	add_to_event("Purim (sundown)", get_datenum(date), "religious");
	date->tm_mday = date->tm_mday + 163 + 30;
	mktime(date);
	add_to_event("Rosh Hashanah (sundown)", get_datenum(date), "religious");
	add_to_event("Rosh Hashanah", get_datenum(date)+1, "religious");
	add_to_event("Rosh Hashanah", get_datenum(date)+2, "religious");
	add_to_event("Yom Kippur (sundown)",get_datenum(date)+11,"religious");
	date->tm_mday += (72 + 11);
	mktime(date);
	add_to_event("Hanukkah (sundown)",get_datenum(date),"religious");
	add_to_event("Hanukkah",get_datenum(date)+1,"religious");
	add_to_event("Hanukkah",get_datenum(date)+2,"religious");
	add_to_event("Hanukkah",get_datenum(date)+3,"religious");
	add_to_event("Hanukkah",get_datenum(date)+4,"religious");
	add_to_event("Hanukkah",get_datenum(date)+5,"religious");
	add_to_event("Hanukkah",get_datenum(date)+6,"religious");
	add_to_event("Hanukkah",get_datenum(date)+7,"religious");
	add_to_event("Hanukkah",get_datenum(date)+8,"religious");
	return 0;
}

/* return 0 if a leap year, 1 if not */
int is_jew_leap(int hebyear)
{
	int i;

	i = hebyear % 19;
	switch (i) {
		case 3: case 6: case 8: case 11: case 14: case 17: case 19:
		return 0;
		break;
	}
	return 1;
}
