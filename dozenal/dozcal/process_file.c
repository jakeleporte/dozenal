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

/* to get getline() defined */
#ifdef TARGGNU
	#define _POSIX_C_SOURCE 200809L
	#define _XOPEN_SOURCE 700
	#define _GNU_SOURCE
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include"errcodes.h"
#include"event_struct.h"
#include"utility.h"
#include"proc_date.h"
#include"conv.h"

#define NUM_EVENTS (sizeof(*event_list) / sizeof(*event_list[0]))

extern struct event *event_list;
extern int recordnums;
extern struct todo *todo_list;
extern int todonums;
extern int geventid;
extern int gtodoid;
extern char **origevs;
extern char **origtos;

int is_mon(char *s);
int is_num(char *s);
int is_wkday(char *s);
int proc_rec(char buffer[][MAXLEN+1],int lines);

int process_file(char *s)
{
	FILE *fp; char *line = NULL; size_t len = 0; ssize_t read;
	char buffer[MAXLINES][MAXLEN+1];
	int linesread = 0;
	int currlineno = 0;

	if ((fp = fopen(s,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with this error:\n\t%d: "
			"%s\n",s,errno,strerror(errno));
		exit(BAD_FILE);
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		if (line[0] == '#')
			continue;
		chomp(line);
		if (strlen(line) == 1)
			continue;
		if ((strstr(line,"[EVENT]") || strstr(line,"[TODO]"))) {
			strcpy(buffer[currlineno],"%%");
			if (strstr(line,"[EVENT]")) ++geventid;
			if (strstr(line,"[TODO]")) ++gtodoid;
			if (linesread != 0) {
				proc_rec(buffer,currlineno);
//				make_whole_rec(buffer,currlineno);
			}
			currlineno = 0;
			if (strstr(line,"[EVENT]")) {
				strcpy(buffer[currlineno++],"EVENT");
			}
			if (strstr(line,"[TODO]")) {
				strcpy(buffer[currlineno++],"TODO");
			}
		} else if (!strstr(line,"[EVENT]") && !strstr(line,"[TODO]") && 
		(currlineno < MAXLINES)) {
			strncpy(buffer[currlineno],line,MAXLEN);
			buffer[currlineno][MAXLEN] = '\0';
			++currlineno;
		}
		linesread++;
	}
	strcpy(buffer[currlineno],"%%");
	proc_rec(buffer,currlineno);
//	make_whole_rec(buffer,currlineno);
	free(line);
	return 0;
}

int make_whole_rec(char buffer[][MAXLEN+1],int lines)
{
	int i;
	int len = 0;

	printf("YO:  %d\n",geventid);
	if (origevs == NULL)
		origevs = malloc(1000 * sizeof(char *));
//	else
//		origevs = realloc(origevs,(geventid+4) * sizeof(char *));
	for (i = 0; i < lines; ++i)
		len += strlen(buffer[i]);
	origevs[geventid] = malloc((len + 1) * sizeof(char));
	/* FIXME */
//	*(origevs+(geventid))[0] = '\0';
	for (i = 0; i < lines; ++i) {
//		strcat(origevs[geventid],buffer[i]);
	}
	return 0;
}

/* expand each file event into a list of events for the struct */
int proc_rec(char buffer[][MAXLEN+1],int lines)
{
	int i; int holder;
	char *location;
	char *title;
	char *class;
	char freq[SHORTLEN][MAXLEN+1];
	time_t startdate; int startday;
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
	int mon; int wday; int nday;
	int numfreq = 0;
	int transp = 0;
	char *attendees;
	char *categories;
	char *url;
	char *description;
	int retval = 0;

	init_str(&categories);
	init_str(&attendees);
	init_str(&location);
	init_str(&url);
	init_str(&title);
	init_str(&class);
	init_str(&description);
	for (i = 0; i < SHORTLEN; ++i)
		freq[i][0] = '\0';
	for (i = 0; i < MAXLEN; ++i)
		exceptions[i] = -1;
	for (i = 0; i <= lines; ++i) {
		if (strstr(buffer[i],"TITLE")) {
			holder = get_impstr(buffer[i]);
			addto_str(&title,buffer[i]+holder);
		} if (strstr(buffer[i],"CLASS")) {
			holder = get_impstr(buffer[i]);
			addto_str(&class,buffer[i]+holder);
		} if (strstr(buffer[i],"LOCATION")) {
			holder = get_impstr(buffer[i]);
			addto_str(&location,buffer[i]+holder);
		} if (strstr(buffer[i],"CATEGORY")) {
			holder = get_impstr(buffer[i]);
			addto_str(&categories,buffer[i]+holder);
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
			strncpy(freq[numfreq++],buffer[i]+holder,MAXLEN);
		} if (strstr(buffer[i],"TRANSPARENT")) {
			holder = get_impstr(buffer[i]);
			transp = atoi(buffer[i]+holder);
		} if (strstr(buffer[i],"ATTENDEES")) {
			holder = get_impstr(buffer[i]);
			addto_str(&attendees,buffer[i]+holder);
		} if (strstr(buffer[i],"URL")) {
			holder = get_impstr(buffer[i]);
			addto_str(&url,buffer[i]+holder);
		} if (strstr(buffer[i],"DESCRIPTION")) {
			holder = get_impstr(buffer[i]);
			addto_str(&description,buffer[i]+holder);
		}
	}
	if (enddate == -1)
		enddate = startdate;
	if (startdate == -1) {
		retval = -1;
		goto cleanup;
	}
	startday = mkdaynum(startdate) + 1;
	endday = mkdaynum(enddate) + 1;
	currinterval = startday;
	if (numfreq > 0) {
		for (i = 0; i < numfreq; ++i) {
			if (endday == holder) {
				othdate = broken_date(startday);
				othdate->tm_year += 1;  othdate->tm_mon = 11;
				othdate->tm_mday = 31; mktime(othdate);
				endday = get_datenum(othdate);
				date = broken_date(startday);
			}
			lower_str(freq[i]);
			if ((wday = is_wkday(freq[i]))) {
				if ((nday = is_num(freq[i]))) {
					if ((mon = is_mon(freq[i]))) {
						date = broken_date(startday);
						date->tm_mon = mon - 1; mktime(date);
						holder = get_datenum(date);
						if (nday <= 5)
							holder = wday_of_month(holder,wday-1,nday);
						else
							holder = last_wday_of_month(holder,wday-1);
						if (endday <= holder)
							endday = holder + 1;
						while (holder < endday) {
							if (strstr(buffer[0],"EVENT")) {
								add_event(starttime, endtime, holder, title, class, 
									categories, location, transp,
									attendees, url, description);
							} if (strstr(buffer[0],"TODO")) {
								add_todo(holder, starttime, priority, 
									compflag, pergross, title, class, 
									categories, location, url,
									description);
							}
							date->tm_year += interval; mktime(date);
							holder = get_datenum(date);
							if (nday <= 5)
								holder = wday_of_month(holder,wday-1,nday);
							else
								holder = last_wday_of_month(holder,wday-1);
						}
					} else {
						date = broken_date(startday);
						holder = get_datenum(date);
						if (nday <= 5)
							holder = wday_of_month(holder,wday-1,nday);
						else
							holder = last_wday_of_month(holder,wday-1);
						if (endday <= holder)
							endday = holder + 1;
						while (holder < endday) {
							if (strstr(buffer[0],"EVENT")) {
								add_event(starttime, endtime, holder, title, class, 
									categories, location, transp,
									attendees, url, description);
							} if (strstr(buffer[0],"TODO")) {
								add_todo(holder, starttime, priority, 
									compflag, pergross, title, class, 
									categories, location, url,
									description);
							}
							date->tm_mon += interval; mktime(date);
							holder = get_datenum(date);
							if (nday <= 5)
								holder = wday_of_month(holder,wday-1,nday);
							else
								holder = last_wday_of_month(holder,wday-1);
						}
					}
				} else {//wday but no ordinal
					if ((mon = is_mon(freq[i]))) { // wkday, no ordinal, month
						date = broken_date(startday);
						holder = get_datenum(date);
						holder = wday_of_month(holder,wday-1,1);
						while (holder < startday) holder += 7;
						if (endday <= holder) {
							endday = first_of_next(date);
							date = broken_date(startday);
						}
						while (holder < endday) {
							if (date->tm_mon == (mon - 1)) {
								if (strstr(buffer[0],"EVENT")) {
									add_event(starttime, endtime, holder, title,
											class, categories, location,
											transp, attendees, url,
											description);
								} if (strstr(buffer[0],"TODO")) {
									add_todo(holder, starttime, priority, 
										compflag, pergross, title, class, 
										categories, location, url,
										description);
								}
							}
							date->tm_mday += (interval * 7); mktime(date);
							holder += (interval * 7);
						}
					} else { //wkday, no ordinal, no month
						date = broken_date(startday);
						holder = get_datenum(date);
						holder = wday_of_month(holder,wday-1,1);
						while (holder < startday) holder += 7;
						if (endday <= holder) {
							endday = first_of_next(date);
							date = broken_date(startday);
						}
						while (holder < endday) {
							if (strstr(buffer[0],"EVENT")) {
								add_event(starttime, endtime, holder, title, class, 
									categories, location, transp,
									attendees, url, description);
							} if (strstr(buffer[0],"TODO")) {
								add_todo(holder, starttime, priority, 
									compflag, pergross, title, class, 
									categories, location, url,
									description);
							}
							date->tm_mday += (interval * 7); mktime(date);
							holder += (interval * 7);
						}
					}
				}
			} else if (strstr(freq[i],"monthly")) {
				date = broken_date(startday);
				holder = get_datenum(date);
				while (holder < endday) {
					if (strstr(buffer[0],"EVENT")) {
						add_event(starttime, endtime, holder, title, class, 
							categories, location, transp,
							attendees, url, description);
					} if (strstr(buffer[0],"TODO")) {
						add_todo(holder, starttime, priority, compflag, pergross,
							title, class, categories, location,
							url, description);
					}
					date->tm_mon += interval; mktime(date);
					holder = get_datenum(date);
				}
			} else if (strstr(freq[i],"yearly")) {
				date = broken_date(startday);
				holder = get_datenum(date);
				while (holder < endday) {
					if (strstr(buffer[0],"EVENT")) {
						add_event(starttime, endtime, holder, title, class, 
							categories,
							location,transp,attendees,url,
							description);
					} if (strstr(buffer[0],"TODO")) {
						add_todo(holder, starttime, priority, compflag, pergross,
							title, class, categories, location,
							url, description);
					}
					date->tm_year += interval; mktime(date);
					holder = get_datenum(date);
				}
			} else {
				fprintf(stderr,"dozcal:  \"FREQ\" directive \"%s\" "
					"cannot be interpreted\n",freq[i]);
				exit(BAD_FREQ);
			}
		}
		goto cleanup;
	}
	for (holder = startday; holder <= endday; ++holder) {
		if ((not_in(holder,exceptions,j-1) == 0) &&
		(currinterval == holder)) {
			if (strstr(buffer[0],"EVENT")) {
				add_event(starttime, endtime, holder, title, class, 
					categories, location, transp, attendees, url,
					description);
			} if (strstr(buffer[0],"TODO")) {
				add_todo(holder, starttime, priority, compflag, pergross,
					title, class, categories, location, url,
					description);
			}
		}
		if (currinterval == holder)
			currinterval += interval;
	}
	cleanup:
	free(title);
	free(class);
	free(attendees);
	free(categories);
	free(location);
	free(url);
	free(description);
	return retval;
}

/* return non-zero if there's a weekday, 0 if not */
int is_wkday(char *s)
{
	if (strstr(s,"sunday"))
		return 1;
	else if (strstr(s,"monday"))
		return 2;
	else if (strstr(s,"tuesday"))
		return 3;
	else if (strstr(s,"wednesday"))
		return 4;
	else if (strstr(s,"thursday"))
		return 5;
	else if (strstr(s,"friday"))
		return 6;
	else if (strstr(s,"saturday"))
		return 7;
	else
		return 0;
}

/* return non-zero if there's a month, 0 if not */
int is_mon(char *s)
{
	if (strstr(s,"jan"))
		return 1;
	else if (strstr(s,"feb"))
		return 2;
	else if (strstr(s,"mar"))
		return 3;
	else if (strstr(s,"apr"))
		return 4;
	else if (strstr(s,"may"))
		return 5;
	else if (strstr(s,"jun"))
		return 6;
	else if (strstr(s,"jul"))
		return 7;
	else if (strstr(s,"aug"))
		return 8;
	else if (strstr(s,"sep"))
		return 9;
	else if (strstr(s,"oct"))
		return 10;
	else if (strstr(s,"nov"))
		return 11;
	else if (strstr(s,"dec"))
		return 12;
	else
		return 0;
}

/* return non-zero if there's a number, 0 if not */
int is_num(char *s)
{
	if (strstr(s,"first") || strstr(s,"1st"))
		return 1;
	else if (strstr(s,"second") || strstr(s,"2nd"))
		return 2;
	else if (strstr(s,"third") || strstr(s,"3rd"))
		return 3;
	else if (strstr(s,"fourth") || strstr(s,"4th"))
		return 4;
	else if (strstr(s,"fifth") || strstr(s,"5th"))
		return 5;
	else if (strstr(s,"last"))
		return 6;
	return 0;
}
