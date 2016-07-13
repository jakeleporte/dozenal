/*
 * +AMDG
 */
/*
 * This document was begun on 10 July 1200, the feast of St.
 * John Gualbert, A, and the Comm. of Ss. Nabor and Felix,
 * MM, and it is humbly dedicated to them and to the
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
#include<string.h>
#include<time.h>

extern struct event *event_list;
extern int recordnums;

int nat_holidays(char *s, int datenum)
{
	if (strstr(s,"usa")) {
		usa_holidays(datenum);
	} if (strstr(s,"uk")) {
	} if (strstr(s,"eng")) {
		england_holidays(datenum);
	} if (strstr(s,"wales")) {
		wales_holidays(datenum);
	} if (strstr(s,"scot")) {
		scot_holidays(datenum);
	} if (strstr(s,"nire")) {
		nire_holidays(datenum);
	} if (strstr(s,"rire")) {
	} if (strstr(s,"austral")) {
	} if (strstr(s,"nz") || strstr(s,"kiwi")) {
	}
	return 0;
}

int england_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int holiday;

	datesecs = datenum * 86400;
	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = 0; date->tm_mday = 1; mktime(date);
	holiday = mkdaynum(mktime(date));
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (England)",holiday);
	date->tm_year -= 1;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (England)",holiday);
	date->tm_year += 2;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (England)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (England)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (England)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (England)",holiday);
	date->tm_year -= 1; date->tm_mon = 11; date->tm_mday = 25;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+3);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+3);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+3);
	date->tm_year -= 1;
	date->tm_mday = 26;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+2);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+2);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (England)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (England)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (England)",holiday+2);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (England)",holiday);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (England)",holiday);
	date->tm_year += 2;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (England)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (England)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (England)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (England)",holiday);
	date->tm_year -= 1; date->tm_mon = 7;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (England)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (England)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (England)",holiday);
	date->tm_year -= 1;
	return 0;
}

int wales_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int holiday;

	datesecs = datenum * 86400;
	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = 0; date->tm_mday = 1; mktime(date);
	holiday = mkdaynum(mktime(date));
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Wales)",holiday);
	date->tm_year -= 1;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Wales)",holiday);
	date->tm_year += 2;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Wales)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (Wales)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (Wales)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (Wales)",holiday);
	date->tm_year -= 1; date->tm_mon = 11; date->tm_mday = 25;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+3);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+3);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+3);
	date->tm_year -= 1;
	date->tm_mday = 26;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Wales)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Wales)",holiday+2);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (Wales)",holiday);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (Wales)",holiday);
	date->tm_year += 2;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (Wales)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (Wales)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (Wales)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (Wales)",holiday);
	date->tm_year -= 1; date->tm_mon = 7;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (Wales)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (Wales)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (Wales)",holiday);
	date->tm_year -= 1;
	return 0;
}

int scot_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int holiday;

	datesecs = datenum * 86400;
	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = 0; date->tm_mday = 1; mktime(date);
	holiday = mkdaynum(mktime(date));
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Scotland)",holiday);
	date->tm_year += 2;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (Scotland)",holiday);
	date->tm_year -= 1; date->tm_mon = 11; date->tm_mday = 25;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+3);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+3);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+3);
	date->tm_year -= 1;
	date->tm_mday = 26;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (Scotland)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (Scotland)",holiday+2);
	date->tm_year -= 1; date->tm_mon=4;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labour Day, May Day (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labour Day, May Day (Scotland)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labour Day, May Day (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) - 2;
	add_to_event("Good Friday (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) - 2;
	add_to_event("Good Friday (Scotland)",holiday);
	date->tm_year += 2;
	holiday = date_easter(date->tm_year + 1900) - 2;
	add_to_event("Good Friday (Scotland)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = last_wday_of_month(get_datenum(date),1);
	add_to_event("Spring Holiday (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date),1);
	add_to_event("Spring Holiday (Scotland)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date),1);
	add_to_event("Spring Holiday (Scotland)",holiday);
	date->tm_year -= 1; date->tm_mon = 7;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Summer Holiday (Scotland)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Summer Holiday (Scotland)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Summer Holiday (Scotland)",holiday);
	date->tm_year -= 1; date->tm_mon = 10; date->tm_mday = 30;
	add_to_event("St. Andrew's Day (Scotland)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("St. Andrew's Day (Scotland)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("St. Andrew's Day (Scotland)",get_datenum(date));
	date->tm_year -= 1;
	return 0;
}

int nire_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int holiday;

	datesecs = datenum * 86400;
	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = 0; date->tm_mday = 1; mktime(date);
	holiday = mkdaynum(mktime(date));
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (N. Ire.)",holiday);
	date->tm_year -= 1;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (N. Ire.)",holiday);
	date->tm_year += 2;
	holiday = get_datenum(date);
	if (get_weekday(holiday) == 0) holiday++;
	if (get_weekday(holiday) == 6) holiday += 2;
	add_to_event("New Year's Day (N. Ire.)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (N. Ire.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1; date->tm_mon = 11; date->tm_mday = 25;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Christmas (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year -= 1;
	date->tm_mday = 26;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("Boxing Day (N. Ire.)",holiday);
	if (get_weekday(holiday) == 0)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	else if (get_weekday(holiday) == 6)
		add_to_event("Bank Holiday (N. Ire.)",holiday+2);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (N. Ire.)",holiday);
	date->tm_year -= 1;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (N. Ire.)",holiday);
	date->tm_year += 2;
	holiday = date_easter(date->tm_year + 1900) + 1;
	add_to_event("Easter Monday (N. Ire.)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (N. Ire.)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Spring Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1; date->tm_mon = 7;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (N. Ire.)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Late Summer Bank Holiday (N. Ire.)",holiday);
	date->tm_year -= 1; date->tm_mon = 2; date->tm_mday = 17;
	add_to_event("St. Patrick's Day (N. Ire.)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("St. Patrick's Day (N. Ire.)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("St. Patrick's Day (N. Ire.)",get_datenum(date));
	date->tm_year -= 1; date->tm_mon = 6; date->tm_mday = 12;
	add_to_event("Orangeman's Day (N. Ire.)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("Orangeman's Day (N. Ire.)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("Orangeman's Day (N. Ire.)",get_datenum(date));
	date->tm_year -= 1;
	return 0;
}

int usa_holidays(int datenum)
{
	time_t datesecs; time_t rawtime;
	struct tm *date;
	int holiday;

	datesecs = datenum * 86400;
	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = 0; date->tm_mday = 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("New Year's Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = mkdaynum(mktime(date));
	add_to_event("New Year's Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = mkdaynum(mktime(date));
	add_to_event("New Year's Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Martin Luther King Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Martin Luther King Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Martin Luther King Day (U.S.)",holiday);
	date->tm_year -= 1;
	date->tm_mon = 1;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Presidents' Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Presidents' Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 3);
	add_to_event("Presidents' Day (U.S.)",holiday);
	date->tm_year -= 1; date->tm_mon = 4;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Memorial Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Memorial Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = last_wday_of_month(get_datenum(date), 1);
	add_to_event("Memorial Day (U.S.)",holiday);
	date->tm_year -= 1;
	date->tm_mon = 6; date->tm_mday = 4;
	add_to_event("Independence Day (U.S.)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("Independence Day (U.S.)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("Independence Day (U.S.)",get_datenum(date));
	date->tm_year -= 1;
	date->tm_mon = 8;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labor Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labor Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	add_to_event("Labor Day (U.S.)",holiday);
	date->tm_year -= 1;
	date->tm_mon = 9;
	holiday = wday_of_month(get_datenum(date), 1, 2);
	add_to_event("Columbus Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 2);
	add_to_event("Columbus Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 2);
	add_to_event("Columbus Day (U.S.)",holiday);
	date->tm_year -= 1; date->tm_mon = 10; date->tm_mday = 11;
	add_to_event("Veterans Day (U.S.)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("Veterans Day (U.S.)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("Veterans Day (U.S.)",get_datenum(date));
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 4, 4);
	add_to_event("Thanksgiving (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 4, 4);
	add_to_event("Thanksgiving (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 4, 4);
	add_to_event("Thanksgiving (U.S.)",holiday);
	date->tm_year -= 1; date->tm_mon = 11; date->tm_mday = 25;
	add_to_event("Christmas Day (U.S.)",get_datenum(date));
	date->tm_year -= 1;
	add_to_event("Christmas Day (U.S.)",get_datenum(date));
	date->tm_year += 2;
	add_to_event("Christmas Day (U.S.)",get_datenum(date));
	date->tm_year -= 1; date->tm_mon = 10;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	holiday += 1;
	add_to_event("Election Day (U.S.)",holiday);
	date->tm_year -= 1;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	holiday += 1;
	add_to_event("Election Day (U.S.)",holiday);
	date->tm_year += 2;
	holiday = wday_of_month(get_datenum(date), 1, 1);
	holiday += 1;
	add_to_event("Election Day (U.S.)",holiday);
	date->tm_year -= 1;
	return 0;
}
