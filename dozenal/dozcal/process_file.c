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
#include"errcodes.h"
#include"event_struct.h"
#include"utility.h"
#include"conv.h"

#define NUM_EVENTS (sizeof(*event_list) / sizeof(*event_list[0]))
#define MAXLEN 256

extern struct event *event_list;
extern int recordnums;

int process_file(char *s)
{
	FILE *fp; char *line = NULL; size_t len = 0; ssize_t read;
	char buffer[16][MAXLEN];
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
		if (strstr(line,"[EVENT]") && (linesread != 0)) {
			strcpy(buffer[currlineno],"%%");
			proc_rec(buffer,currlineno);
			currlineno = 0;
		} else if (!strstr(line,"[EVENT]")) {
			t = strchr(line,':') + 1;
			strcpy(buffer[currlineno++],line);
		}
		linesread++;
	}
	strcpy(buffer[currlineno],"%%");
	proc_rec(buffer,currlineno);
	free(line);
	return 0;
}

/* expand each file event into a list of events for the struct */
int proc_rec(char buffer[][MAXLEN],int lines)
{
	int i; int holder;
	char title[256];
	time_t startdate; int startday;
	time_t enddate = -1; int endday = -1;
	int exceptions[256];
	int j = 0;
	int starttime = -1; int endtime = -1;
	int interval = 1;
	int currinterval;

	for (i = 0; i < 256; ++i)
		exceptions[i] = -1;
	for (i = 0; i <= lines; ++i) {
		if (strstr(buffer[i],"TITLE")) {
			holder = get_impstr(buffer[i]);
			strcpy(title,buffer[i]+holder);
		}
		if (strstr(buffer[i],"START_DATE")) {
			startdate = proc_date(buffer[i]);
		}
		if (strstr(buffer[i],"END_DATE")) {
			enddate = proc_date(buffer[i]);
		}
		if (strstr(buffer[i],"EXCEPT_DATE")) {
			exceptions[j++] = (int)proc_date(buffer[i]) / 86400 + 1;
		}
		if (strstr(buffer[i],"START_TIME")) {
			starttime = proc_time(buffer[i]);
		}
		if (strstr(buffer[i],"END_TIME")) {
			endtime = proc_time(buffer[i]);
		}
		if (strstr(buffer[i],"INTERVAL")) {
			holder = get_impstr(buffer[i]);
			interval = (int) doztodec(buffer[i]+holder);
		}
	}
	if (enddate == -1)
		enddate = startdate;
	if (startdate == -1)
		return 0;
	startday = (int)startdate / 86400 + 1;
	endday = (int)enddate / 86400 + 1;
	currinterval = startday;
	for (holder = startday; holder <= endday; ++holder) {
		if ((not_in(holder,exceptions,j-1) == 0) &&
		(currinterval == holder)) {
			event_list = realloc(event_list,(recordnums * 
				sizeof(struct event)));
			event_list[recordnums-1].starttime = -1;
			event_list[recordnums-1].endtime = -1;
			strcpy(event_list[recordnums-1].title,title);
			event_list[recordnums-1].thisdate = holder;
			event_list[recordnums-1].starttime = starttime;
			event_list[recordnums-1].endtime = endtime;
			recordnums++;
		}
		if (currinterval == holder)
			currinterval += interval;
	}
	return 0;
}
