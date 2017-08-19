/*
 * +AMDG
 */
/*
 * This document was begun on 10 Aug 1200, the feast of St.
 * Clare, V, and it is humbly dedicated to her and to the
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
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"utility.h"
#include"conv.h"

int frac_to_secs(double jdn);

double datenum_to_jdn(int datenum)
{
	int a, y, m, d;
	struct tm *date;
	double jdn;

	date = broken_date(datenum);
	y = date->tm_year + 1900;
	m = date->tm_mon + 1;
	d = date->tm_mday;
	y += 8000;
	if (m < 3) { y--; m+=12; }
	jdn = (y * 365) + (y / 4) - (y / 100) + (y / 400) -
		1200820 + (m * 153 + 3) / 5 - 92 + d - 1;
	return jdn - 0.5;
}

int jdn_to_datenum(double jdn)
{
	int Q, Z, W, X, A, B, C, D, E, F, dy, mn, yr;
	struct tm *date;
	time_t rawtime;

	rawtime = time(&rawtime);
	date = localtime(&rawtime);
	Q = jdn + 0.5;
	Z = floor(Q);
	W = floor((Z - 1867216.25) / 36524.25);
	X = floor(W / 4);
	A = Z + 1 + W - X;
	B = A + 1524;
	C = floor((B - 122.1) / 365.25);
	D = floor(365.25 * C);
	E = floor((B - D) / 30.6001);
	F = floor(30.6001 * E);
	dy = B - D - F + (Q - Z);
	mn = E - 1;
	if (mn > 12) {
		mn = E - 13;
	}
	if ((mn == 1) || (mn == 2)) {
		yr = C - 4715;
	} else {
		yr = C - 4716;
	}
	date->tm_year = (int)floor(yr) - 1900;
	date->tm_mon = (int)floor(mn) - 1;
	date->tm_mday = (int)floor(dy);
	frac_to_secs(jdn);
	return get_datenum(date);
}

int frac_to_secs(double jdn)
{
	double frac; double integ;
	int secs;
	char buf[8];

	frac = modf(jdn,&integ);
	sprintf(buf,"%.6f",frac);
	memmove(buf,buf+2,7);
	secs = floor((atoi(buf) * 86400.) / 1000000.);
	return secs;
}

int frac_to_hours(double jdn)
{
	int hours;
	hours = frac_to_secs(jdn);
	return (int) hours / 60 / 60;
}

int frac_to_mins(double jdn)
{
	int mins;
	mins = frac_to_secs(jdn);
	mins -= (frac_to_hours(jdn) * 3600);
	return (int) mins / 60;
}

int set_time_str(char *s, double jdn)
{
	int hrs, mns;
	char bufhr[8]; char bufmn[8];

	jdn += 0.5;
	s[0] = '\0'; bufhr[0] = '\0'; bufmn[0] = '\0';
	hrs = frac_to_hours(jdn);
	mns = frac_to_mins(jdn);
	dectodoz(bufhr,(double)hrs);
	dectodoz(bufmn,(double)mns);
	if (strlen(bufhr) == 1) {
		memmove(bufhr+1,bufhr,2);
		bufhr[0] = '0';
	}
	if (strlen(bufmn) == 1) {
		memmove(bufmn+1,bufmn,2);
		bufmn[0] = '0';
	}
	sprintf(s,"%2s:%2s",bufhr,bufmn);
	return 0;
}
