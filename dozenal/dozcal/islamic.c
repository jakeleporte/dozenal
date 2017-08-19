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
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include"utility.h"

struct isldate {
	int iday;
	int imonth;
	int iyear;
};

int isl_date(struct tm *date, struct isldate *now);
int add_eidaladha(struct tm *date, struct isldate *now);
int add_ramadan(struct tm *date, struct isldate *now);

int islamic_holidays(int daynum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int hijdays;
	int holiday;
	struct isldate *now;

	now = malloc(1 * sizeof(struct isldate));
	time(&rawtime);
	date = localtime(&rawtime);
	isl_date(date, now);
	add_ramadan(date,now);
	add_to_event("Eid Al-Fitr",get_datenum(date),"religious");
	add_eidaladha(date,now);
	date->tm_year -= 1; mktime(date);
	add_ramadan(date,now);
	add_to_event("Eid Al-Fitr",get_datenum(date),"religious");
	add_eidaladha(date,now);
	date->tm_year += 2; mktime(date);
	add_ramadan(date,now);
	add_to_event("Eid Al-Fitr",get_datenum(date),"religious");
	add_eidaladha(date,now);
	date->tm_year -= 1; mktime(date);
	free(now);
	return 0;
}

int add_ramadan(struct tm *date, struct isldate *now)
{
	while (1) {
		if (now->imonth > 9) {
			date->tm_mon -= 1;
			mktime(date);
		} else if (now->imonth < 9) {
			date->tm_mon += 1;
			mktime(date);
		} else {
			for ( ; now->iday != 1; date->tm_mday -= 1) {
				mktime(date);
				isl_date(date,now);
			}
			break;
		}
		isl_date(date,now);
	}
	while (now->imonth == 9) {
		add_to_event("Ramadan",get_datenum(date)-1,"religious");
		date->tm_mday += 1; mktime(date);
		isl_date(date,now);
	}
	return 0;
}

int add_eidaladha(struct tm *date, struct isldate *now)
{
	while (1) {
		if (now->imonth > 12) {
			date->tm_mon -= 1;
			mktime(date);
		} else if (now->imonth < 12) {
			date->tm_mon += 1;
			mktime(date);
		} else {
			if (now->iday > 10) {
				date->tm_mday -= 1;
				mktime(date);
			} else if (now->iday < 10) {
				date->tm_mday += 1;
				mktime(date);
			} else {
				break;
			}
		}
		isl_date(date,now);
	}
	add_to_event("Eid Al-Adha",get_datenum(date)-1,"religious");
	date->tm_mday += 1; mktime(date);
	isl_date(date,now);
	return 0;
}

/* algorithm from http://oriold.uzh.ch/static/hegira.html */
int isl_date(struct tm *date, struct isldate *now)
{
	time_t datesecs; time_t rawtime;
	int d, m, y, i, jd, j, l, n;
	
	d = date->tm_mday;
	m = date->tm_mon;
	y = date->tm_year + 1900;
	if ((y>1582)||((y==1582)&&(m>10))||((y==1582)&&(m==10)&&(d>14))) {
		jd=floor((1461*(y+4800+floor((m-14)/12)))/4)+
			floor((367*(m-2-12*(floor((m-14)/12))))/12)-
			floor((3*(floor((y+4900+floor((m-14)/12))/100)))/4)+
			d-32075;
	} else {
		jd = 367*y-floor((7*(y+5001+floor((m-9)/7)))/4)+
			floor((275*m)/9)+d+1729777;
	}
	l=jd-1948440+10632;
	n=floor((l-1)/10631);
	l=l-10631*n+354;
	j=(floor((10985-l)/5316))*(floor((50*l)/17719))+
		(floor(l/5670))*(floor((43*l)/15238));
	l=l-(floor((30-j)/15))*(floor((17719*j)/50))-(floor(j/16))*
		(floor((15238*j)/43))+29;
	m=floor((24*l)/709);
	d=l-floor((709*m)/24);
	y=30*n+j-30;
	now->iday = d;
	now->imonth = m + 1;
	now->iyear = y;
	return 0;
}
