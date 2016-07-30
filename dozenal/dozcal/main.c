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

struct event *event_list;
int recordnums = 0;
struct todo *todo_list;
int todonums = 0;
int comparator(const void *evone, const void *evtwo);
int todocomp(const void *todoone, const void *todotwo);

int main(int argc, char **argv)
{
	char c; int i;
	int tmpctr;					/* for looping without changing recordnums */
	int moonphases = 0;		/* if 0, no phases; if 1, yes */
	int numevents = 0;
	int startdate = -1; int enddate = -1;
	char *ev_form;
	const char *def_form = "%d | %s | %c | %e | %t | %C | %l";
	char *date_form;
	const char *def_date = "%Y-%m-%d";
	char *time_form;
	const char *def_time = "%h;%4b";
	char *todo_form;
	const char *def_todo_form = "%p | %d | %t | %i | %c | %g | %T | %C | %l";
	char *nat;
	char *relig;
	char *conffile;
	char *defconfname = "/.dozcal/dozcalrc";
	char *home;
	char cwd[] = "~";
	int preflen = -1;
	int confflag = 0;
	int ifevent = 1;
	int iftodo = 0;
	int weekout = 0;
	int fdow = 0;

	home = getenv("HOME");
	if (home != NULL) {
		preflen = strlen(home) + 1;
	} else {
		preflen = 2;
	}
	if ((conffile = malloc((preflen + strlen(defconfname) + 1) * 
	sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold "
		"the configuration file name\n");
		exit(INSUFF_MEM);
	}
	*conffile = '\0';
	if (home != NULL) {
		strcat(conffile,home); strcat(conffile,defconfname);
	} else {
		strcat(conffile,cwd); strcat(conffile,defconfname);
	}
	if ((event_list = malloc(recordnums++ * sizeof(struct event))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"event list\n");
		exit(INSUFF_MEM);
	}
	if ((todo_list = malloc(todonums++ * sizeof(struct todo))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"todo list\n");
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
	if ((todo_form = malloc(2*(strlen(def_todo_form)+1)*sizeof(char))) 
	== NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"date format line\n");
		exit(INSUFF_MEM);
	}
	strcpy(todo_form,def_todo_form);
	if ((time_form = malloc(2*(strlen(def_date)+1)*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"time format line\n");
		exit(INSUFF_MEM);
	}
	strcpy(time_form,def_time);
	if ((nat = malloc(1*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"national holidays requested\n");
		exit(INSUFF_MEM);
	}
	nat[0] = '\0';
	if ((relig = malloc(1*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"religious holidays requested\n");
		exit(INSUFF_MEM);
	}
	relig[0] = '\0';
	opterr = 0;
	while ((c = getopt(argc,argv,"VETwR:m:f:s:e:d:t:r:c:n:h:l:W:")) != -1) {
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
		case 'E':
			ifevent = 0;
			break;
		case 'T':
			iftodo = 1;
			break;
		case 'l':
			call_lua(optarg);
			break;
		case 'w':
			weekout = 1;
			break;
		case 'W':
			fdow = first_dow(optarg);
			break;
		case 'n':
			if ((nat = realloc(nat,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"national holidays requested\n");
				exit(INSUFF_MEM);
			}
			strcpy(nat,optarg);
			break;
		case 'h':
			if ((relig = realloc(relig,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"religional holidays requested\n");
				exit(INSUFF_MEM);
			}
			strcpy(relig,optarg);
			break;
		case 'f':
			numevents = process_file(optarg);
			break;
		case 'c':
			proc_options(optarg,&moonphases,&nat,&relig,&date_form,
				&time_form,&ev_form,&todo_form,&iftodo,&ifevent,&weekout,
				&fdow);
			confflag = 1;
			break;
		case 'm':
			if (strstr(optarg,"all")) {
				moonphases = 1;
			} else if (strstr(optarg,"major")) {
				moonphases = 2;
			} else {
				fprintf(stderr,"dozcal:  unrecognized argument "
					"\"%s\" for option \"-m\"; possible values "
					"are \"all\" and \"major\"\n",optarg);
				exit(BAD_MOON_PHASE);
			}
			break;
		case 's':
			startdate = mkdaynum(proc_date(optarg)) + 1;
			break;
		case 'e':
			enddate = mkdaynum(proc_date(optarg)) + 1;
			break;
		case 'd':
			if ((date_form = realloc(date_form,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"date format line\n");
				exit(INSUFF_MEM);
			}
			strcpy(date_form,optarg);
			break;
		case 'R':
			if ((todo_form = realloc(todo_form,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"date format line\n");
				exit(INSUFF_MEM);
			}
			strcpy(todo_form,optarg);
			break;
		case 't':
			if ((time_form = realloc(time_form,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"time format line\n");
				exit(INSUFF_MEM);
			}
			strcpy(time_form,optarg);
			break;
		case 'r':
			if ((ev_form = realloc(ev_form,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"event format line\n");
				exit(INSUFF_MEM);
			}
			strcpy(ev_form,optarg);
			break;
		case '?':
			if ((optopt == 'f') || (optopt == 'd')
			|| (optopt == 'm') || (optopt == 'c')
			|| (optopt == 't') || (optopt == 'r')
			|| (optopt == 'R') || (optopt == 'l')
			|| (optopt == 'W')) {
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
	if (confflag == 0) {
		proc_options(conffile,&moonphases,&nat,&relig,&date_form,
			&time_form,&ev_form,&todo_form,&iftodo,&ifevent,&weekout,
			&fdow);
	}
	if (startdate == -1)
		startdate = 0;
	if (enddate == -1)
		enddate = INT_MAX - 1;
	if ((weekout == 1) && (startdate != 0)) {
		while (get_weekday(startdate) != fdow)
			startdate -= 1;
		enddate = startdate + 6;
	}
	qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	if (strlen(relig) > 0) {
		if (strstr(relig,"west")) {
			west_holidays(event_list[0].thisdate);
		} if (strstr(relig,"east")) {
			east_holidays(event_list[0].thisdate);
		} if (strstr(relig,"jew")) {
			jew_holidays(event_list[0].thisdate);
		} if (strstr(relig,"isl")) {
			islamic_holidays(event_list[0].thisdate);
		}
		qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	}
	if (strlen(nat) > 0) {
		nat_holidays(nat, event_list[0].thisdate);
		qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	}
	if (moonphases > 0) {
		tmpctr = event_list[recordnums-2].thisdate;
		for (i = event_list[0].thisdate; i <= tmpctr; ++i) {
			get_moonphases(i,moonphases);
		}
		qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	}
	if (ifevent == 1) {
		for (i = 0; i < (recordnums-1); ++i) {
			if ((event_list[i].thisdate >= startdate) &&
			(event_list[i].thisdate <= enddate)) {
				print_event(ev_form,i,date_form,time_form);
			}
		}
	}
	if (iftodo == 1) {
		qsort(todo_list,todonums-1,sizeof(struct todo),todocomp);
		for (i = 0; i < (todonums-1); ++i) {
			if ((todo_list[i].duedate >= startdate) &&
			(todo_list[i].duedate <= enddate)) {
				print_todo(todo_form,i,date_form,time_form);
			}
		}
	}
	free(event_list);
	free(todo_list);
	free(ev_form);
	free(date_form);
	free(time_form);
	free(todo_form);
	free(nat);
	free(relig);
	free(conffile);
	return 0;
}

int print_todo(char *s, int index, char *date_format, char *time_format)
{
	int i; int j;
	char holder[6];
	int len = MAXLEN + 1;
	char *ptr;
	char datestr[MAXLEN+1];
	char buffer[8];

	if ((ptr = malloc((MAXLEN+1) * sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"todo strings\n");
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
				num_to_date(todo_list[index].duedate,datestr,date_format);
				printf("%*s",len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 't') {
				secs_to_Tims(todo_list[index].duetime,datestr,time_format);
				printf("%*s",len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'p') {
				printf("%*d",len,todo_list[index].priority);
			} else if (s[i] == 'c') {
				printf("%*d",len,todo_list[index].completed);
			} else if (s[i] == 'g') {
				dectodoz(buffer,(double)todo_list[index].pergross);
				printf("%*s",len,buffer);
			} else if (s[i] == 'i') {
				printf("%*s",len,todo_list[index].item);
			} else if (s[i] == 'l') {
				printf("%*s",len,todo_list[index].location);
			} else if (s[i] == 'C') {
				printf("%*s",len,todo_list[index].categories);
			} else if (s[i] == 'T') {
				printf("%*s",len,todo_list[index].todoclass);
			} else {
				fprintf(stderr,"dozcal:  unrecognized conversion "
					"character \"%%%c\" in todo form string, "
					"\"%%%s\"\n",s[i],s);
				exit(BAD_TODO_FORMAT);
			}
		} else {
			if (s[i] == '\\') {
				if (s[i+1] == 'n') {
					printf("\n");
					++i;
				} else if (s[i+1] == 't') {
					printf("\t");
					++i;
				} else {
					printf("\\");
				}
			} else {
				printf("%c",s[i]);
			}
		}
		len = MAXLEN + 1;
	}
	printf("\n");
	free(ptr);
	return 0;
}

int print_event(char *s, int index, char *date_format, char *time_format)
{
	int i; int j;
	char holder[6];
	int len = MAXLEN + 1;
	char *ptr;
	char datestr[MAXLEN+1];
	char buffer[MAXLEN+1];

	if ((ptr = malloc((MAXLEN+1) * sizeof(char))) == NULL) {
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
			} else if (s[i] == 'C') {
				printf("%*s",len,event_list[index].categories);
			} else if (s[i] == 't') {
				printf("%*s",len,event_list[index].evclass);
			} else if (s[i] == 'l') {
				printf("%*s",len,event_list[index].location);
			} else {
				fprintf(stderr,"dozcal:  unrecognized conversion "
					"character \"%%%c\" in event form string, "
					"\"%%%s\"\n",s[i],s);
				exit(BAD_EV_FORMAT);
			}
		} else {
			if (s[i] == '\\') {
				if (s[i+1] == 'n') {
					printf("\n");
					++i;
				} else if (s[i+1] == 't') {
					printf("\t");
					++i;
				} else {
					printf("\\");
				}
			} else {
				printf("%c",s[i]);
			}
		}
		len = MAXLEN + 1;
	}
	printf("\n");
	free(ptr);
	return 0;
}

int todocomp(const void *todoone, const void *todotwo)
{
	int priorone = 0; int priortwo = 0;
	int dateone = 0; int datetwo = 0;
	int timeone = 0; int timetwo = 0;
	char *itemone; char *itemtwo;

	const struct todo *firsttodo = (struct todo*) todoone;
	const struct todo *sectodo = (struct todo*) todotwo;
	priorone = ((struct todo*) todoone)->priority;
	priortwo = ((struct todo*) todotwo)->priority;
	dateone = ((struct todo*) todoone)->duedate;
	datetwo = ((struct todo*) todotwo)->duedate;
	timeone = ((struct todo*) todoone)->duetime;
	timetwo = ((struct todo*) todotwo)->duetime;
	itemone = ((struct todo*) todoone)->item;
	itemtwo = ((struct todo*) todotwo)->item;
	if (priorone > priortwo) {
		return 1;
	} else if (priorone < priortwo) {
		return -1;
	} else {
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
				return strcmp(itemone,itemtwo);
			}
		}
	}
}

int comparator(const void *evone, const void *evtwo)
{
	int dateone = 0; int datetwo = 0;
	int timeone = 0; int timetwo = 0;
	char *itemone; char *itemtwo;

	const struct event *firstev = (struct event*) evone;
	const struct event *secev = (struct event*) evtwo;
	dateone = ((struct event*) evone)->thisdate;
	datetwo = ((struct event*) evtwo)->thisdate;
	timeone = ((struct event*) evone)->starttime;
	timetwo = ((struct event*) evtwo)->starttime;
	itemone = ((struct event*) evone)->title;
	itemtwo = ((struct event*) evtwo)->title;
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
			return strcmp(itemone,itemtwo);
		}
	}
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
