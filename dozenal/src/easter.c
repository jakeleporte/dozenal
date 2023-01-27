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
#include<math.h>
#include<time.h>
#include"utility.h"

extern struct event *event_list;
extern int recordnums;

int date_easter(int year);
int orth_easter(int year);

int west_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int easter; int easterlast; int easternext;

	time(&rawtime);
	date = localtime(&rawtime);
	easter = date_easter(date->tm_year + 1900);
	easterlast = date_easter(date->tm_year + 1899);
	easternext = date_easter(date->tm_year + 1902);
	add_to_event("Easter (Western)",easter,"religious");
	add_to_event("Easter (Western)",easterlast,"religious");
	add_to_event("Easter (Western)",easternext,"religious");
	add_to_event("Palm Sunday (Western)",easter-7,"religious");
	add_to_event("Palm Sunday (Western)",easterlast-7,"religious");
	add_to_event("Palm Sunday (Western)",easternext-7,"religious");
	add_to_event("Ash Wednesday",easter-46,"religious");
	add_to_event("Ash Wednesday",easterlast-46,"religious");
	add_to_event("Ash Wednesday",easternext-46,"religious");
	add_to_event("Good Friday",easter-2,"religious");
	add_to_event("Good Friday",easterlast-2,"religious");
	add_to_event("Good Friday",easternext-2,"religious");
	add_to_event("Ascension Day",easter+39,"religious");
	add_to_event("Ascension Day",easterlast+39,"religious");
	add_to_event("Ascension Day",easternext+39,"religious");
	add_to_event("Pentecost",easter+49,"religious");
	add_to_event("Pentecost",easterlast+49,"religious");
	add_to_event("Pentecost",easternext+49,"religious");
	date->tm_mon = 11; date->tm_mday = 25;
	datesecs = mktime(date);
	add_to_event("Christmas",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas",mkdaynum(datesecs),"religious");
	return 0;
}

int east_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int easter; int easterlast; int easternext;

	time(&rawtime);
	date = localtime(&rawtime);
	easter = orth_easter(date->tm_year + 1900);
	easterlast = orth_easter(date->tm_year + 1899);
	easternext = orth_easter(date->tm_year + 1902);
	add_to_event("Easter (Eastern)",easter,"religious");
	add_to_event("Easter (Eastern)",easterlast,"religious");
	add_to_event("Easter (Eastern)",easternext,"religious");
	add_to_event("Clean Monday (Eastern)",easter-48,"religious");
	add_to_event("Clean Monday (Eastern)",easterlast-48,"religious");
	add_to_event("Clean Monday (Eastern)",easternext-48,"religious");
	add_to_event("Palm Sunday (Eastern)",easter-7,"religious");
	add_to_event("Palm Sunday (Eastern)",easterlast-7,"religious");
	add_to_event("Palm Sunday (Eastern)",easternext-7,"religious");
	add_to_event("Lazarus Saturday (Eastern)",easter-8,"religious");
	add_to_event("Lazarus Saturday (Eastern)",easterlast-8,"religious");
	add_to_event("Lazarus Saturday (Eastern)",easternext-8,"religious");
	add_to_event("Mid-Pentecost (Eastern)",easter+24,"religious");
	add_to_event("Mid-Pentecost (Eastern)",easterlast+24,"religious");
	add_to_event("Mid-Pentecost (Eastern)",easternext+24,"religious");
	add_to_event("Ascension Day (Eastern)",easter+39,"religious");
	add_to_event("Ascension Day (Eastern)",easterlast+39,"religious");
	add_to_event("Ascension Day (Eastern)",easternext+39,"religious");
	add_to_event("Pentecost (Eastern)",easter+49,"religious");
	add_to_event("Pentecost (Eastern)",easterlast+49,"religious");
	add_to_event("Pentecost (Eastern)",easternext+49,"religious");
	date->tm_mon = 0; date->tm_mday = 6;
	datesecs = mktime(date);
	add_to_event("Christmas (Eastern)",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas (Eastern)",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas (Eastern)",mkdaynum(datesecs),"religious");
	date->tm_mon = 11; date->tm_mday = 25; date->tm_year += 2;
	datesecs = mktime(date);
	add_to_event("Christmas (Greek)",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas (Greek)",mkdaynum(datesecs),"religious");
	date->tm_year -= 1;
	datesecs = mktime(date);
	add_to_event("Christmas (Greek)",mkdaynum(datesecs),"religious");
	return 0;
}

int date_easter(int year)
{
	int a, b, c, d, e, f, g, h, i, k, l, m, month, day;
	int easterday;
	struct tm *thedate;
	time_t eastersecs;
	time_t buffer = 0;

	thedate = localtime(&buffer);
	a = year % 19;
	b = floor(year / 100);
	c = year % 100;
	d = floor(b / 4);
	e = b % 4;
	f = floor((b + 8) / 25);
	g = floor((b - f + 1) / 3);
	h = (19 * a + b - d - g + 15) % 30;
	i = floor(c / 4);
	k = c % 4;
	l = (32 + (2 * e) + (2 * i) - h - k) % 7;
	m = floor((a + (11 * h) + (22 * l)) / 451);
	month = floor((h + l - (7 * m) + 114) / 31);
	day = ((h + l - (7 * m) + 114) % 31) + 1;
	thedate->tm_year = year - 1900;
	thedate->tm_mon = month - 1;
	thedate->tm_mday = day;
	eastersecs = mktime(thedate);
	easterday = mkdaynum(eastersecs);
	return easterday;
}

int orth_easter(int year)
{
	int a, b, c, d, e, month, day;
	time_t eastersecs;
	time_t buffer = 0;
	int easterday;
	struct tm *thedate;

	thedate = localtime(&buffer);
	a = year % 4;
	b = year % 7;
	c = year % 19;
	d = ((19 * c) + 15) % 30;
	e = ((2 * a) + (4 * b) - d + 34) % 7;
	month = floor((d + e + 114) / 31);
	day = ((d + e + 114) % 31) + 1;
	thedate->tm_year = year - 1900;
	thedate->tm_mon = month - 1;
	thedate->tm_mday = day;
	eastersecs = mktime(thedate);
	easterday = mkdaynum(eastersecs) + 13;
	return easterday;
}
