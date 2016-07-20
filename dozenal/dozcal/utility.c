/*
 * +AMDG
 */
/*
 * This document was begun on 5 July 1200, the feast of St.
 * Anthony Mary Zaccaria, C, and it is humbly dedicated to
 * him and to the Immaculate Heart of Mary for their
 * prayers, and to the Sacred Heart of Jesus for His mercy.
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

#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include"event_struct.h"
#include"errcodes.h"

extern struct event *event_list;
extern int recordnums;

int chomp(char *s)
{
	int i; int j = 0;

	for (i = strlen(s) - 1; i != 0; --i) {
		if (isspace(s[i])) {
			s[i] = '\0';
			++j;
		} else {
			break;
		}
	}
	return j;
}

char *front_chomp(char *s)
{
	int i; int j = 0;
	char *t;

	t = s;
	for (i = 0; isspace(s[i]) && s[i] != '\0'; ++i) {
			++t;
	}
	return t;
}

/* checks if variable is in array; if not, return 0, else 1 */
int not_in(int date, int exceptions[], int len)
{
	int i; int j;

	for (i = 0; i <= len; ++i) {
		if (date == exceptions[i])
			return 1;
	}
	return 0;
}

int get_impstr(char *s)
{
	char *t;

	t = strchr(s,':') + 1;
	t = front_chomp(t);
	return t-s;
}

int dozendig(char c)
{
	switch(c) {
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': case 'X': case 'E':
	case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

int add_to_event(char *title, int datenum, char *cat)
{
	event_list = realloc(event_list,(recordnums * 
		sizeof(struct event)));
	event_list[recordnums-1].starttime = -1;
	event_list[recordnums-1].endtime = -1;
	strncpy(event_list[recordnums-1].title,title,MAXLEN);
	strcpy(event_list[recordnums-1].evclass,"");
	strcpy(event_list[recordnums-1].location,"");
	strncpy(event_list[recordnums-1].categories,cat,MAXLEN);
	event_list[recordnums-1].thisdate = datenum;
	event_list[recordnums-1].relatedto = -1;
	event_list[recordnums-1].transp = 1;
	recordnums++;
}

int get_weekday(int datenum)
{
	time_t datesecs;
	struct tm *date;

	datesecs = datenum * 86400;
	date = localtime(&datesecs);
	return date->tm_wday;
}

int wday_of_month(int datenum, int wday, int num)
{
	time_t datesecs;
	struct tm *date;
	int i;

	datesecs = datenum * 86400;
	date = localtime(&datesecs);
	date->tm_mday = 1; mktime(date);
	for (i = 0; date->tm_wday != wday; ++i) {
		date->tm_mday++;
		mktime(date);
	}
	for (i = 1; i < num; ++i)
		date->tm_mday += 7;
	mktime(date);
	return get_datenum(date);
}

int last_wday_of_month(int datenum, int wday)
{
	time_t datesecs;
	struct tm *date;
	int i;
	int holder;

	datesecs = datenum * 86400;
	date = localtime(&datesecs);
	holder = date->tm_mon;
	for (i = 27; date->tm_mon == holder; ++i) {
		date->tm_mday++;
		mktime(date);
	}
	date->tm_mday--;
	mktime(date);
	for (i = date->tm_mday; date->tm_wday != wday; --i) {
		date->tm_mday--;
		mktime(date);
	}
	mktime(date);
	return get_datenum(date);
}

int get_datenum(struct tm *date)
{
	time_t rawtime;

	mktime(date);
	rawtime = mktime(date);
	return mkdaynum(rawtime);
}

int mkdaynum(time_t datenum)
{
	double holder;

	holder = (double) datenum / 86400;
	return lround(holder);
}

int lower_str(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; ++i) {
		s[i] = tolower(s[i]);
	}
	return 0;
}
