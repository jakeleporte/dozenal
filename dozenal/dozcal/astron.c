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

/* from sunriset.c */
#define sun_rise_set(year,month,day,lon,lat,rise,set)  \
        __sunriset__( year, month, day, lon, lat, -35.0/60.0, 1, rise, set )

#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"errcodes.h"
#include"utility.h"
#include"julday.h"

extern double latitude;
extern double longitude;

double degtorad(double degs);
double radtodeg(double rads);

int astron(char *s, int startdate, int enddate)
{
	if (strstr(s,"season")) {
		seasons(datenum_to_jdn(startdate));
	} if (strstr(s,"sun")) {
		while (startdate <= enddate) {
			suntimes(datenum_to_jdn(startdate));
			startdate++;
		}
	}
	return 0;
}

int suntimes(double jdn)
{
	struct tm *date;
	time_t rawtime;
	int sunset;
	double risetime; double settime;
	char bufr[12]; char bufs[12];

	rawtime = time(&rawtime);
//	date = localtime(&rawtime);
	date = broken_date(jdn_to_datenum(jdn));
	sunset = sun_rise_set(date->tm_year+1900,date->tm_mon+1,date->tm_mday,
		longitude,latitude,&risetime,&settime);
	risetime += date->tm_gmtoff/60/60;
	settime += date->tm_gmtoff/60/60;
	dec_to_mins(settime,bufs);
	dec_to_mins(risetime,bufr);
	if (sunset == 0) {
		add_event(proc_time(bufr), 0, jdn_to_datenum(jdn), "Sunrise",
			"solar", "astronomical,solar", "");
		add_event(proc_time(bufs), 0, jdn_to_datenum(jdn), "Sunset",
			"solar", "astronomical,solar", "");
	} else if (sunset == -1) {
	}
	return 0;
}

int dec_to_mins(double number, char *s)
{
	int i; int j = 0;
	double hrs, mns, frac;
	int hours, mins;
	char bufhr[SHORTLEN]; char bufmn[SHORTLEN];
	char dbufhr[SHORTLEN]; char dbufmn[SHORTLEN];

	s[0] = '\0'; bufhr[0] = '\0'; bufmn[0] = '\0';
	frac = modf(number,&hrs);
	hours = (int)(floor(hrs));
	mns = frac * 60;
	mins = (int)(floor(mns));
	dectodoz(bufhr,(double)hours);
	dectodoz(bufmn,(double)mins);
	sprintf(s,"%2s:%2s\n",bufhr,bufmn);
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == ' ') s[i] = '0';
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
	set_time_str(buf,ss);
	add_event(proc_time(buf), 0, jdn_to_datenum(ss), "June Solstice",
		"astronomical", "astronomical,seasons", "");
	set_time_str(buf,ws);
	add_event(proc_time(buf), 0, jdn_to_datenum(ws), "December Solstice",
		"astronomical", "astronomical,seasons", "");
	return 0;
}

double degtorad(double degs)
{
	return ((degs * M_PI) / 180);
}

double radtodeg(double rads)
{
	return ((rads * 180) / M_PI);
}
