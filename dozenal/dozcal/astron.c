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
 * The code for determining the seasons comes from the
 * public domain "Seasons" program written by Vernero
 * Cifagni, available at
 * codeguru.com/code/legacy/date_time/Seasons.zip.
 */

#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"utility.h"
#include"julday.h"
#include"conv.h"

int astron(char *s, int datenum)
{
	if (strstr(s,"season")) {
		seasons(datenum_to_jdn(datenum));
	}
	return 0;
}

int seasons(double jdn)
{
	double m, ve, ss, ae, ws;
	struct tm *date;
	int hours,mins, secs;
	char buf[8];

	date = broken_date(jdn_to_datenum(jdn));
	m = ((double)(date->tm_year+1900) - 2000.) / 1000.;
	ve = 2451623.80984 + 365242.37404 * m + 0.05169 * m * m - 
		0.00411 * m * m * m - 0.00057 * m * m * m * m;
	ss = 2451716.56767 + 365241.62603 * m + 0.00325 * m * m + 
		0.00888 * m * m * m - 0.00030 * m * m * m * m;
	ae = 2451810.21715 + 365242.01767 * m - 0.11575 * m * m + 
		0.00337 * m * m * m + 0.00078 * m * m * m * m;
	ws = 2451900.05952 + 365242.74049 * m - 0.06223 * m * m - 
		0.00823 * m * m * m + 0.00032 * m * m * m * m;
	set_time_str(buf,ve);
	add_event(proc_time(buf), 0, jdn_to_datenum(ve), "March Equinox",
		"astronomical", "astronomical,seasons", "");
	set_time_str(buf,ae);
	add_event(proc_time(buf), 0, jdn_to_datenum(ae), "September Equinox",
		"astronomical", "astronomical,seasons", "");
	fprintf(stderr,"%s\n",buf);
	set_time_str(buf,ss);
	add_event(proc_time(buf), 0, jdn_to_datenum(ss), "June Solstice",
		"astronomical", "astronomical,seasons", "");
	set_time_str(buf,ws);
	add_event(proc_time(buf), 0, jdn_to_datenum(ws), "December Solstice",
		"astronomical", "astronomical,seasons", "");
	return 0;
}
