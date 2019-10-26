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
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
#include<sys/stat.h>
#include"event_struct.h"
#include"errcodes.h"

extern struct event *event_list;
extern int recordnums;
extern struct todo *todo_list;
extern int todonums;
extern int geventid;
extern int gtodoid;

int get_datenum(struct tm *date);
int mkdaynum(time_t datenum);

int init_str(char **s)
{
	if ((*s = malloc(sizeof(char) + 1)) == NULL) {
		fprintf(stderr,"dozcal:  error:  insufficient memory\n");
		exit(INSUFF_MEM);
	}
	*s[0] = '\0';
	return 0;
}

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
	int i;
	char *t;

	t = s;
	for (i = 0; isspace(s[i]) && s[i] != '\0'; ++i) {
			++t;
	}
	return t;
}

int reassign_str(char *s, char *t)
{
	s = realloc(s,sizeof(t) + 1);
	s[0] = '\0';
	strcat(s,t);
	return 0;
}

int addto_str(char **s, char *t)
{
	if (*s == NULL) {
		*s = malloc(strlen(t) + 2);
		*s[0] = '\0';
		strcpy(*s,t);
	} else {
		*s = realloc(*s,strlen(*s) + strlen(t) + 4);
		if (strlen(*s) != 0)
			strcat(*s,", ");
		strcat(*s,t);
	}
	return 0;
}

/* checks if variable is in array; if not, return 0, else 1 */
int not_in(int date, int exceptions[], int len)
{
	int i;

	for (i = 0; i <= len; ++i) {
		if (date == exceptions[i])
			return 1;
	}
	return 0;
}

int get_impstr(char *s)
{
	char *t;

	t = strchr(s,':');
	if (t == NULL)
		return 0;
	t++;
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

int upper_str(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; ++i) {
		s[i] = toupper(s[i]);
	}
	return 0;
}

int add_event(int starttime, int endtime, int thisdate,
	char *title, char *class, char *categories, char
	*location, char transp, char *attendees, char *url)
{
	event_list = realloc(event_list,(recordnums * 
		sizeof(struct event)));
	event_list[recordnums-1].starttime = -1;
	event_list[recordnums-1].endtime = -1;
	event_list[recordnums-1].title = NULL;
	addto_str(&event_list[recordnums-1].title,title);
	event_list[recordnums-1].evclass = NULL;
	addto_str(&event_list[recordnums-1].evclass,class);
	event_list[recordnums-1].categories = NULL;
	addto_str(&event_list[recordnums-1].categories,categories);
	event_list[recordnums-1].location = NULL;
	addto_str(&event_list[recordnums-1].location,location);
	event_list[recordnums-1].thisdate = thisdate;
	event_list[recordnums-1].starttime = starttime;
	event_list[recordnums-1].endtime = endtime;
	event_list[recordnums-1].relatedto = -1;
	event_list[recordnums-1].transp = 1;
	event_list[recordnums-1].attendees = NULL;
	addto_str(&event_list[recordnums-1].attendees,attendees);
	event_list[recordnums-1].url = NULL;
	addto_str(&event_list[recordnums-1].url,url);
	event_list[recordnums-1].idnum = geventid;
	recordnums++;
	return 0;
}

int add_to_event(char *title, int datenum, char *cat)
{
	add_event(-1,-1,datenum,title,"",cat,"",1,"","");
	return 0;
}

int add_todo(int duedate,int starttime,int priority,
	int compflag, int pergross, char *title, char *class,
	char *categories, char *location, char *url)
{
	todo_list = realloc(todo_list,(todonums *
		sizeof(struct todo)));
	todo_list[todonums-1].duedate = -1;
	todo_list[todonums-1].duetime = -1;
	todo_list[todonums-1].priority = 0;
	todo_list[todonums-1].completed = 0;
	todo_list[todonums-1].pergross = 0;
	todo_list[todonums-1].item = NULL;
	addto_str(&todo_list[todonums-1].item,title);
	todo_list[todonums-1].duedate = duedate;
	todo_list[todonums-1].duetime = starttime;
	todo_list[todonums-1].priority = priority;
	todo_list[todonums-1].completed = compflag;
	todo_list[todonums-1].pergross = pergross;
	todo_list[todonums-1].todoclass = NULL;
	addto_str(&todo_list[todonums-1].todoclass,class);
	todo_list[todonums-1].categories = NULL;
	addto_str(&todo_list[todonums-1].categories,categories);
	todo_list[todonums-1].location = NULL;
	addto_str(&todo_list[todonums-1].location,location);
	todo_list[todonums-1].url = NULL;
	addto_str(&todo_list[todonums-1].url,url);
	todo_list[todonums-1].idnum = gtodoid;
	todonums++;
	return 0;
}

struct tm *broken_date(int daynum)
{
	struct tm *date;
	time_t datenum;

	datenum = daynum * 86400;
	date = localtime(&datenum);
	return date;
}

int first_of_next(struct tm *date)
{
	struct tm *thisdate;
	time_t rawtime;
	int mon; int year; int mday;

	mon = date->tm_mon; year = date->tm_year; mday = date->tm_mday;
	time(&rawtime);
	thisdate = localtime(&rawtime);
	thisdate->tm_year = year;
	thisdate->tm_mon = mon;
	thisdate->tm_mday = mday;
	mktime(thisdate);
	date->tm_mon = mon; date->tm_year = year; date->tm_mday = mday;
	thisdate->tm_mon += 1; thisdate->tm_mday = 1;
	mktime(thisdate);
	return get_datenum(thisdate);
}

int file_exist(char *s)
{
	struct stat buffer;
	return (stat(s,&buffer) == 0);
}

int countchars(char *s, char c)
{
	int num = 0;
	int i;

	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == c) {
			++num;
		}
	}
	return num;
}

int first_dow(char *s)
{
	int ret;

	if (isdigit(s[0])) {
		ret = atoi(s);
		if ((ret < 7) && (ret >= 0)) {
			return ret;
		} else {
			fprintf(stderr,"dozcal:  invalid value for "
				"the first day of week; must be the name of "
				"a day or a number 0--7, but value is \"%s\"\n",
				s);
			exit(BAD_FDOW);
		}
	} else {
		lower_str(s);
		if (strstr(s,"sun"))
			return 0;
		else if (strstr(s,"mon"))
			return 1;
		else if (strstr(s,"tue"))
			return 2;
		else if (strstr(s,"wed"))
			return 3;
		else if (strstr(s,"thu"))
			return 4;
		else if (strstr(s,"fri"))
			return 5;
		else if (strstr(s,"sat"))
			return 6;
		else {
			fprintf(stderr,"dozcal:  invalid value for "
				"the first day of week; must be the name of "
				"a day or a number 0--7, but value is \"%s\"\n",
				s);
			exit(BAD_FDOW);
		}
	}
}
