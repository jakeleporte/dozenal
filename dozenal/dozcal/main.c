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
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<limits.h>
#include"utility.h"
#include"errcodes.h"
#include"conv.h"
#include"event_struct.h"

#define NUM_EVENTS (sizeof(event_list) / sizeof(event_list[0]))
#define MAXLEN 256

struct event *event_list;
int recordnums = 0;
int comparator(const void *evone, const void *evtwo);

int main(int argc, char **argv)
{
	char c; int i;
	int numevents = 0;
	int startdate = -1; int enddate = -1;
	char *ev_form;
	const char *def_form = "%-20d : %s---%c : %34e";
	char *date_form;
	const char *def_date = "%Y-%m-%d";
	char *time_form;
	const char *def_time = "%4h;%2b;%b";

	if ((event_list = malloc(recordnums++ * sizeof(struct event))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"event list\n");
		exit(INSUFF_MEM);
	}
	if ((ev_form = malloc(2*(strlen(def_form)+1) * sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"event format line\n");
		exit(INSUFF_MEM);
	}
	strcpy(ev_form,def_form);
	if ((date_form = malloc(2*(strlen(def_date)+1)*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"date format line\n");
		exit(INSUFF_MEM);
	}
	strcpy(date_form,def_date);
	if ((time_form = malloc(2*(strlen(def_date)+1)*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"time format line\n");
		exit(INSUFF_MEM);
	}
	strcpy(time_form,def_time);
	opterr = 0;
	while ((c = getopt(argc,argv,"Vf:s:e:d:")) != -1) {
		switch(c) {
		case 'V':
			printf("dozcal v1.0\n");
			printf("Copyright (C) 1200 (2016) by Donald P.  Goodman III\n");
			printf("License GPLv3+:  GNU GPL Version 3 or later "
				"<http://gnu.org/licenses/gpl.html>\n");
			printf("This is free software; you are free to change "
				"and redistribute it.  There is NO WARRANTY, "
				"to the extent permitted by law.\n");
			exit(EXIT_SUCCESS);
			break;
		case 'f':
			numevents = process_file(optarg);
			break;
		case 's':
			startdate = proc_date(optarg) / 86400;
			break;
		case 'e':
			enddate = proc_date(optarg) / 86400;
			break;
		case 'd':
			if ((date_form = realloc(date_form,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"event format line\n");
				exit(INSUFF_MEM);
			}
			strcpy(date_form,optarg);
			break;
		case '?':
			if ((optopt == 'f') || (optopt == 'd')) {
				fprintf(stderr,"dozcal:  option \"%c\" requires "
					"an argument\n",optopt);
				exit(OPT_REQ_ARG);
			}
			fprintf(stderr,"dozcal:  unrecognized option "
				"\"%c\"\n",optopt);
			exit(UNREC_OPT);
			break;
		}
	}
	if (startdate == -1)
		startdate = 0;
	if (enddate == -1)
		enddate = INT_MAX - 1;
	qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	for (i = 0; i < (recordnums-1); ++i) {
		if ((event_list[i].thisdate >= startdate) &&
		(event_list[i].thisdate <= enddate)) {
			print_event(ev_form,i,date_form,time_form);
		}
	}
	free(event_list);
	free(ev_form);
	free(date_form);
	free(time_form);
	return 0;
}

int print_event(char *s, int index, char *date_format, char *time_format)
{
	int i; int j;
	char holder[6];
	int len = 256;
	char *ptr;
	char datestr[256];

	if ((ptr = malloc(256 * sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"event strings\n");
		exit(INSUFF_MEM);
	}
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == '%') {
			j = 0; holder[0] = '\0'; len = 0;
			while (dozendig(s[++i]))
				holder[j++] = s[i];
			holder[j] = '\0';
			if (holder[0] != '\0')
				len = (int)doztodec(holder);
			if (s[i] == 'd') {
				num_to_date(event_list[index].thisdate,datestr,date_format);
				printf("%*s",len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 's') {
				secs_to_Tims(event_list[index].starttime,datestr,time_format);
				printf("%*s",len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'c') {
				secs_to_Tims(event_list[index].endtime,datestr,time_format);
				printf("%*s",len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'e') {
				printf("%*s",len,event_list[index].title);
			}
		} else {
			printf("%c",s[i]);
		}
	}
	printf("\n");
	free(ptr);
	return 0;
}

int comparator(const void *evone, const void *evtwo)
{
	int dateone = 0; int datetwo = 0;
	int timeone = 0; int timetwo = 0;

	const struct event *firstev = (struct event*) evone;
	const struct event *secev = (struct event*) evtwo;
	dateone = ((struct event*) evone)->thisdate;
	datetwo = ((struct event*) evtwo)->thisdate;
	timeone = ((struct event*) evone)->starttime;
	timetwo = ((struct event*) evtwo)->starttime;
	if (dateone > datetwo) {
		return 1;
	} else if (dateone < datetwo) {
		return -1;
	} else {
		if (timeone > timetwo) {
			return 1;
		} else if (timeone < timetwo) {
			return -1;
		} else {
			return 0;
		}
	}
}
