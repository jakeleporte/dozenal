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
#include<hdate.h>

int jew_holidays(int daynum)
{
	get_israel_holydays(daynum);
	return 0;
}

int get_israel_holydays(int daynum)
{
	struct tm *date;
	time_t datesecs;
	int hebyear;
	hdate_struct *h;
	int i;

	datesecs = daynum * 86400;
	date = localtime(&datesecs);
	h = new_hdate();
	hebyear = hdate_get_hyear(h);
	h = hdate_set_hdate(h,15,7,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	for (i = 0; i <= 7; ++i) {
		add_to_event("Passover",get_datenum(date) + i);
	}
	hebyear -= 1; date->tm_year -= 1;
	h = hdate_set_hdate(h,15,7,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	for (i = 0; i <= 7; ++i)
		add_to_event("Passover",get_datenum(date) + i);
	hebyear += 2; date->tm_year += 2;
	h = hdate_set_hdate(h,15,7,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	for (i = 0; i <= 7; ++i)
		add_to_event("Passover",get_datenum(date) + i);
	delete_hdate(h);
	h = new_hdate();
	h = hdate_set_hdate(h,1,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 1; ++i)
		add_to_event("Rosh Hashanah",get_datenum(date) + i);
	hebyear -= 1; date->tm_year -= 1;
	h = hdate_set_hdate(h,1,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 1; ++i)
		add_to_event("Rosh Hashanah",get_datenum(date) + i);
	hebyear += 2; date->tm_year += 2;
	h = hdate_set_hdate(h,1,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 1; ++i)
		add_to_event("Rosh Hashanah",get_datenum(date) + i);
	delete_hdate(h);
	h = new_hdate();
	hebyear -= 1;
	h = hdate_set_hdate(h,10,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	add_to_event("Yom Kippur",get_datenum(date));
	hebyear -= 1;
	h = hdate_set_hdate(h,10,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	add_to_event("Yom Kippur",get_datenum(date));
	hebyear += 2;
	h = hdate_set_hdate(h,10,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	add_to_event("Yom Kippur",get_datenum(date));
	hebyear -= 1;
	delete_hdate(h);
	h = new_hdate();
	h = hdate_set_hdate(h,15,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 6; ++i)
		add_to_event("Sukkot",get_datenum(date) + i);
	hebyear -= 1;
	h = hdate_set_hdate(h,15,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 6; ++i)
		add_to_event("Sukkot",get_datenum(date) + i);
	hebyear += 2;
	h = hdate_set_hdate(h,15,1,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 6; ++i)
		add_to_event("Sukkot",get_datenum(date) + i);
	hebyear -= 1;
	delete_hdate(h);
	h = new_hdate();
	h = hdate_set_hdate(h,25,3,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 7; ++i)
		add_to_event("Hanukkah",get_datenum(date) + i);
	hebyear -= 1;
	delete_hdate(h);
	h = new_hdate();
	h = hdate_set_hdate(h,25,3,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 7; ++i)
		add_to_event("Hanukkah",get_datenum(date) + i);
	hebyear += 2;
	delete_hdate(h);
	h = new_hdate();
	h = hdate_set_hdate(h,25,3,hebyear);
	date->tm_mon = hdate_get_gmonth(h) - 1;
	date->tm_mday = hdate_get_gday(h);
	date->tm_year = hdate_get_gyear(h) - 1900;
	for (i = 0; i <= 7; ++i)
		add_to_event("Hanukkah",get_datenum(date) + i);
	hebyear -= 1;
	delete_hdate(h);
	return mkdaynum(date);
}
