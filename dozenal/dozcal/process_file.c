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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include"errcodes.h"
#include"event_struct.h"
#include"utility.h"
#include"conv.h"

#define NUM_EVENTS (sizeof(*event_list) / sizeof(*event_list[0]))

extern struct event *event_list;
extern int recordnums;
extern struct todo *todo_list;
extern int todonums;

int process_file(char *s)
{
	FILE *fp; char *line = NULL; size_t len = 0; ssize_t read;
	char buffer[MAXLINES][MAXLEN+1];
	int linesread = 0;
	int currlineno = 0;
	char *t;
	int i;

	if ((fp = fopen(s,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with the following error:\n\t%d: "
			"%s\n",s,errno,strerror(errno));
		exit(BAD_FILE);
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		chomp(line);
		if (strlen(line) == 1)
			continue;
		if ((strstr(line,"[EVENT]") || strstr(line,"[TODO]"))) {
			strcpy(buffer[currlineno],"%%");
			if (linesread != 0)
				proc_rec(buffer,currlineno);
			currlineno = 0;
			if (strstr(line,"[EVENT]"))
				strcpy(buffer[currlineno++],"EVENT");
			if (strstr(line,"[TODO]"))
				strcpy(buffer[currlineno++],"TODO");
		} else if (!strstr(line,"[EVENT]") && !strstr(line,"[TODO]") && 
		(currlineno < MAXLINES)) {
			t = strchr(line,':') + 1;
			strncpy(buffer[currlineno++],line,MAXLEN);
		}
		linesread++;
	}
	strcpy(buffer[currlineno],"%%");
	proc_rec(buffer,currlineno);
	free(line);
	return 0;
}

/* expand each file event into a list of events for the struct */
int proc_rec(char buffer[][MAXLEN+1],int lines)
{
	int i; int holder;
	char title[MAXLEN+1];
	char categories[MAXLEN+1];
	char location[MAXLEN+1];
	char class[SHORTLEN+1];
	char freq[MAXLEN+1];
	time_t startdate; int startday;
	time_t duetime;
	time_t enddate = -1; int endday = -1;
	int exceptions[MAXLEN+1];
	int j = 0;
	int starttime = -1; int endtime = -1;
	int interval = 1;
	int currinterval;
	int priority = 0;
	int compflag = 0;
	int pergross = 0;
	struct tm *date;
	struct tm *othdate;
	int year; int mon; int day;

	categories[0] = '\0';
	class[0] = '\0';
	title[0] = '\0';
	location[0] = '\0';
	freq[0] = '\0';
	for (i = 0; i < MAXLEN; ++i)
		exceptions[i] = -1;
	for (i = 0; i <= lines; ++i) {
		if (strstr(buffer[i],"TITLE")) {
			holder = get_impstr(buffer[i]);
			strncpy(title,buffer[i]+holder,MAXLEN);
		} if (strstr(buffer[i],"CLASS")) {
			holder = get_impstr(buffer[i]);
			strncpy(class,buffer[i]+holder,SHORTLEN);
		} if (strstr(buffer[i],"LOCATION")) {
			holder = get_impstr(buffer[i]);
			strncpy(location,buffer[i]+holder,MAXLEN);
		} if (strstr(buffer[i],"CATEGORY")) {
			holder = get_impstr(buffer[i]);
			if ((strlen(categories) + strlen(buffer[i]+holder) + 2) < MAXLEN) {
				if (strlen(categories) > 0)
					strcat(categories,",");
				strcat(categories,buffer[i]+holder);
			}
		} if (strstr(buffer[i],"START_DATE")) {
			startdate = proc_date(buffer[i]);
		} if (strstr(buffer[i],"END_DATE")) {
			enddate = proc_date(buffer[i]);
		} if (strstr(buffer[i],"EXCEPT_DATE")) {
			exceptions[j++] = mkdaynum(proc_date(buffer[i])) + 1;
		} if (strstr(buffer[i],"START_TIME")) {
			starttime = proc_time(buffer[i]);
		} if (strstr(buffer[i],"END_TIME")) {
			endtime = proc_time(buffer[i]);
		} if (strstr(buffer[i],"INTERVAL")) {
			holder = get_impstr(buffer[i]);
			interval = (int) doztodec(buffer[i]+holder);
		} if (strstr(buffer[i],"PRIORITY")) {
			holder = get_impstr(buffer[i]);
			priority = (int) doztodec(buffer[i]+holder);
		} if (strstr(buffer[i],"DUE_DATE")) {
			startdate = proc_date(buffer[i]);
		} if (strstr(buffer[i],"DUE_TIME")) {
			starttime = proc_time(buffer[i]);
		} if (strstr(buffer[i],"COMPLETED")) {
			holder = get_impstr(buffer[i]);
			compflag = atoi(buffer[i]+holder);
		} if (strstr(buffer[i],"PERGROSS")) {
			holder = get_impstr(buffer[i]);
			pergross = (int) doztodec(buffer[i]+holder);
		} if (strstr(buffer[i],"FREQ")) {
			holder = get_impstr(buffer[i]);
			strncpy(freq,buffer[i]+holder,MAXLEN);
		}
	}
	if (enddate == -1)
		enddate = startdate;
	if (startdate == -1)
		return -1;
	startday = mkdaynum(startdate) + 1;
	endday = mkdaynum(enddate) + 1;
	currinterval = startday;
	if (strlen(freq) > 0) {
		if (endday == holder) {
			othdate = broken_date(startday);
			othdate->tm_year += 1;  othdate->tm_mon = 11;
			othdate->tm_mday = 31; mktime(othdate);
			endday = get_datenum(othdate);
			date = broken_date(startday);
		}
		lower_str(freq);
		if (is_wkday(freq)) {
			if (is_num(freq)) {
				if (is_mon(freq)) {
				} else {
				}
			} else {
				if (is_mon(freq)) {
				} else {
				}
			}
			if (is_num(freq)) {
			} else {
			}
		} else if (strstr(freq,"monthly")) {
				date = broken_date(startday);
				year = date->tm_year;
				holder = get_datenum(date);
				while (holder < endday) {
					if (strstr(buffer[0],"EVENT")) {
						add_event(starttime, endtime, holder, title, class, 
							categories, location);
					} if (strstr(buffer[0],"TODO")) {
						add_todo(holder, starttime, priority, compflag, pergross,
							title, class, categories, location);
					}
					date->tm_mon += interval; mktime(date);
					holder = get_datenum(date);
				}
		}
		return 0;
	}
	for (holder = startday; holder <= endday; ++holder) {
		if ((not_in(holder,exceptions,j-1) == 0) &&
		(currinterval == holder)) {
			if (strstr(buffer[0],"EVENT")) {
				add_event(starttime, endtime, holder, title, class, 
					categories, location);
			} if (strstr(buffer[0],"TODO")) {
				add_todo(holder, starttime, priority, compflag, pergross,
					title, class, categories, location);
			}
		}
		if (currinterval == holder)
			currinterval += interval;
	}
	return 0;
}

/* return 1 if there's a weekday, 0 if not */
int is_wkday(char *s)
{
	if (!strstr(s,"day"))
		return 0;
	if (strstr(s,"sunday") || strstr(s,"monday") ||
	strstr(s,"tuesday") || strstr(s,"wednesday") ||
	strstr(s,"thursday") || strstr(s,"friday") ||
	strstr(s,"saturday"))
		return 1;
	else
		return 0;

}

/* return 1 if there's a month, 0 if not */
int is_mon(char *s)
{
	if (strstr(s,"jan") || strstr(s,"feb") || strstr(s,"mar") ||
	strstr(s,"apr") || strstr(s,"may") || strstr(s,"jun") ||
	strstr(s,"jul") || strstr(s,"aug") || strstr(s,"sep") ||
	strstr(s,"oct") || strstr(s,"nov") || strstr(s,"dec"))
		return 1;
	else
		return 0;
}

/* return 1 if there's a number, 0 if not */
int is_num(char *s)
{
	if (strstr(s,"first") || strstr(s,"1st") ||
	strstr(s,"second") || strstr(s,"2nd") ||
	strstr(s,"third") || strstr(s,"3rd") ||
	strstr(s,"fourth") || strstr(s,"4th") ||
	strstr(s,"last"))
		return 1;
	return 0;
}
