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
#include<getopt.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<errno.h>
#include<limits.h>
#include"utility.h"
#include"libholidays.h"
#include"main_func.h"
#include"tui.h"
#include"moon.h"
#include"errcodes.h"
#include"conv.h"
#include"event_struct.h"
#include"proc_date.h"

#define NUM_EVENTS (sizeof(event_list) / sizeof(event_list[0]))

struct event *event_list;
int recordnums = 0;
struct todo *todo_list;
int todonums = 0;
double latitude = 0.0;
double longitude = 0.0;
double tzoffset = -999.0;
int utc = 0; /* if 1, use UTC time */
char **evlines; int numevs = 1;
char **todolines; int numtodos = 1;
struct globopts *allopts;
int numopts = 35;

int comparator(const void *evone, const void *evtwo);
int todocomp(const void *todoone, const void *todotwo);
int fill_todo(char *s, int index, char *date_format, char
	*time_format,FILE *outfile);
int fill_event(char *s, int index, char *date_format, char
	*time_format, FILE *outfile);
int print_todos();
int clear_todos();
int print_events();
int clear_events();
int build_globopts_struct();

int main(int argc, char **argv)
{
	char c; int i;
	int tmpctr;					/* for looping without changing recordnums */
	int moonphases = 0;		/* if 0, no phases; if 1, yes */
	int startdate = -1; int enddate = -1;
	char *ev_form;
	const char *def_form = "%d | %s | %c | %e | %t | %C | %l | %a | %u";
	char *date_form;
	const char *def_date = "%Y-%m-%d";
	char *time_form;
	const char *def_time = "%h;%4b";
	char *todo_form;
	const char *def_todo_form = "%p | %d | %t | %i | %c | %g | %T | %C | %l | %u";
	char *nat;
	char *relig;
	char *astro;
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
	FILE *outfile = stdout;
	int usetui = 0;

	build_globopts_struct();
	allopts[NOCOLOR].colconst = 1;
	if ((evlines = malloc(1 * sizeof(char *))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	if ((todolines = malloc(1 * sizeof(char *))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted todo lines\n");
		exit(INSUFF_MEM);
	}
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
	if ((astro = malloc(1*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"astronomical dates requested\n");
		exit(INSUFF_MEM);
	}
	astro[0] = '\0';
	if ((relig = malloc(1*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"religious holidays requested\n");
		exit(INSUFF_MEM);
	}
	relig[0] = '\0';
	opterr = 0;
	while ((c = getopt(argc,argv,"VCETwuvR:m:f:s:e:d:t:r:c:n:h:l:W:a:g:z:")) 
	!= -1) {
		switch(c) {
		case 'V':
			printf("dozcal v1.6\n");
			printf("Copyright (C) 1203 (2019) by Donald P.  Goodman III\n");
			printf("License GPLv3+:  GNU GPL Version 3 or later "
				"<http://gnu.org/licenses/gpl.html>\n");
			printf("This is free software; you are free to change "
				"and redistribute it.  There is NO WARRANTY, "
				"to the extent permitted by law.\n");
			exit(EXIT_SUCCESS);
			break;
		case 'v':
			usetui = 1;
			break;
		case 'C':
			allopts[NOCOLOR].colconst = -1;
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
		case 'u':
			utc = 1;
			break;
		case 'w':
			weekout = 1;
			break;
		case 'W':
			fdow = first_dow(optarg);
			break;
		case 'a':
			if ((astro = realloc(astro,(strlen(optarg)+1) * 
			sizeof(char)))==NULL) {
				fprintf(stderr,"dozcal:  insufficient memory to hold the "
					"astronomical dates requested\n");
				exit(INSUFF_MEM);
			}
			strcpy(astro,optarg);
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
		case 'z':
			tzoffset = doztodec(optarg);
			break;
		case 'g':
			proc_geog(optarg);
			break;
		case 'f':
			process_file(optarg);
			break;
		case 'c':
			proc_options(optarg,&moonphases,&nat,&relig,&date_form,
				&time_form,&ev_form,&todo_form,&iftodo,&ifevent,&weekout,
				&fdow,&astro);
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
			|| (optopt == 'W') || (optopt == 'a')
			|| (optopt == 'g') || (optopt == 'z')) {
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
			&fdow,&astro);
	}
	qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	if (startdate == -1)
		startdate = 0;
	if (enddate == -1)
		enddate = event_list[recordnums-2].thisdate;
	if ((weekout == 1) && (startdate != 0)) {
		while (get_weekday(startdate) != fdow)
			startdate -= 1;
		enddate = startdate + 6;
	}
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
	}
	if (strlen(astro) > 0) {
		if (startdate == 0)
			astron(astro,event_list[0].thisdate,enddate);
		else
			astron(astro,startdate,enddate);
	}
	if (strlen(nat) > 0) {
		nat_holidays(nat, event_list[0].thisdate);
	}
	if (moonphases > 0) {
		tmpctr = event_list[recordnums-2].thisdate;
		for (i = event_list[0].thisdate; i <= tmpctr; ++i) {
			get_moonphases(i,moonphases);
		}
	}
	qsort(event_list,recordnums-1,sizeof(struct event),comparator);
	if (usetui == 1) {
		qsort(todo_list,todonums-1,sizeof(struct todo),todocomp);
		build_tui(ev_form,date_form,time_form,todo_form);
		goto clean;
	}
	if (ifevent == 1) {
		for (i = 0; i < (recordnums-1); ++i) {
			if ((event_list[i].thisdate >= startdate) &&
			(event_list[i].thisdate <= enddate)) {
				fill_event(ev_form,i,date_form,time_form,outfile);
				print_events();
			}
		}
	}
	if (iftodo == 1) {
		qsort(todo_list,todonums-1,sizeof(struct todo),todocomp);
		for (i = 0; i < (todonums-1); ++i) {
			if ((todo_list[i].duedate >= startdate) &&
			(todo_list[i].duedate <= enddate)) {
				fill_todo(todo_form,i,date_form,time_form,outfile);
				print_todos();
			}
		}
	}
	clean:
	for (i = 0; i < (recordnums-1); ++i) {
		if (event_list[i].title != NULL)
			free(event_list[i].title);
		if (event_list[i].attendees != NULL)
			free(event_list[i].attendees);
		if (event_list[i].url != NULL)
			free(event_list[i].url);
		if (event_list[i].categories != NULL)
			free(event_list[i].categories);
		if (event_list[i].location != NULL)
			free(event_list[i].location);
		if (event_list[i].evclass != NULL)
			free(event_list[i].evclass);
	}
	free(event_list);
	for (i = 0; i < (todonums-1); ++i) {
		if (todo_list[i].item != NULL)
			free(todo_list[i].item);
		if (todo_list[i].todoclass != NULL)
			free(todo_list[i].todoclass);
		if (todo_list[i].categories != NULL)
			free(todo_list[i].categories);
		if (todo_list[i].location != NULL)
			free(todo_list[i].location);
		if (todo_list[i].url != NULL)
			free(todo_list[i].url);
	}
	free(todo_list);
	free(ev_form);
	free(date_form);
	free(time_form);
	free(todo_form);
	free(nat);
	free(relig);
	free(astro);
	free(conffile);
	for (i = 1; i < numevs; ++i)
		free(*(evlines+i));
	free(evlines);
	for (i = 1; i < numtodos; ++i)
		free(*(todolines+i));
	free(todolines);
	free(allopts);
	return 0;
}

int fill_todo(char *s, int index, char *date_format, char
*time_format,FILE *outfile)
{
	int i; int j;
	char holder[6];
	int len = MAXLEN + 1;
	char datestr[MAXLEN+1];
	char buffer[SHORTLEN];
	char othbuf[MAXLEN+1];
	char tmpbuf[MAXLEN+1];

	numtodos++;
	if ((todolines=realloc(todolines,(numtodos*sizeof(char *)))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	if ((*(todolines+(numtodos-1))=malloc(MAXLEN*sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	othbuf[0] = '\0';
	for (i = 0; s[i] != '\0'; ++i) {
		tmpbuf[0] = '\0';
		if (s[i] == '%') {
			j = 0; holder[0] = '\0'; len = 0;
			while (dozendig(s[++i]))
				holder[j++] = s[i];
			holder[j] = '\0';
			if (holder[0] != '\0')
				len = (int)doztodec(holder);
			if (s[i] == 'd') {
				num_to_date(todo_list[index].duedate,datestr,date_format);
				if (len == 0)
					len = strlen(datestr);
				sprintf(tmpbuf,"%*.*s",len,len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 't') {
				secs_to_Tims(todo_list[index].duetime,datestr,time_format);
				if (len == 0)
					len = strlen(datestr);
				sprintf(tmpbuf,"%*.*s",len,len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'p') {
				sprintf(tmpbuf,"%*d",len,todo_list[index].priority);
			} else if (s[i] == 'c') {
				sprintf(tmpbuf,"%*d",len,todo_list[index].completed);
			} else if (s[i] == 'g') {
				dectodoz(buffer,(double)todo_list[index].pergross);
				if (len == 0)
					len = strlen(buffer);
				sprintf(tmpbuf,"%*.*s",len,len,buffer);
			} else if (s[i] == 'i') {
				if (len == 0)
					len = strlen(todo_list[index].item);
				sprintf(tmpbuf,"%*.*s",len,len,todo_list[index].item);
			} else if (s[i] == 'l') {
				if (len == 0)
					len = strlen(todo_list[index].location);
				sprintf(tmpbuf,"%*.*s",len,len,todo_list[index].location);
			} else if (s[i] == 'C') {
				if (len == 0)
					len = strlen(todo_list[index].categories);
				sprintf(tmpbuf,"%*.*s",len,len,todo_list[index].categories);
			} else if (s[i] == 'T') {
				if (len == 0)
					len = strlen(todo_list[index].todoclass);
				sprintf(tmpbuf,"%*.*s",len,len,todo_list[index].todoclass);
			} else if (s[i] == 'u') {
				if (len == 0)
					len = strlen(todo_list[index].url);
				sprintf(tmpbuf,"%*.*s",len,len,todo_list[index].url);
			} else {
				fprintf(stderr,"dozcal:  unrecognized conversion "
					"character \"%%%c\" in todo form string, "
					"\"%%%s\"\n",s[i],s);
				exit(BAD_TODO_FORMAT);
			}
		} else {
			if (s[i] == '\\') {
				if (s[i+1] == 'n') {
					sprintf(tmpbuf,"\n");
					++i;
				} else if (s[i+1] == 't') {
					sprintf(tmpbuf,"\t");
					++i;
				} else {
					sprintf(tmpbuf,"\\");
				}
			} else {
				sprintf(tmpbuf,"%c",s[i]);
			}
		}
		len = MAXLEN + 1;
		strcat(othbuf,tmpbuf);
	}
	strncpy(*(todolines+(numtodos-1)),othbuf,MAXLEN);
	return 0;
}

int print_todos()
{
	printf("%s",*(todolines+(numtodos-1)));
	printf("\n");
	return 0;
}

int fill_event(char *s, int index, char *date_format, char
*time_format, FILE *outfile)
{
	int i; int j;
	char holder[6];
	int len = MAXLEN + 1;
	char datestr[MAXLEN+1];
	char buffer[MAXLEN+1];
	char othbuf[MAXLEN+1];

	numevs++;
	if ((evlines = realloc(evlines,(numevs * sizeof(char *)))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	if ((*(evlines+(numevs-1)) = malloc(MAXLEN * sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	othbuf[0] = '\0';
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == '%') {
			j = 0; holder[0] = '\0'; len = 0; buffer[0] = '\0';
			while (dozendig(s[++i]))
				holder[j++] = s[i];
			holder[j] = '\0';
			if (holder[0] != '\0')
				len = (int)doztodec(holder);
			if (s[i] == 'd') {
				num_to_date(event_list[index].thisdate,datestr,date_format);
				if (len == 0)
					len = strlen(datestr);
				sprintf(buffer,"%*.*s",len,len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 's') {
				secs_to_Tims(event_list[index].starttime,datestr,time_format);
				if (len == 0)
					len = strlen(datestr);
				sprintf(buffer,"%*.*s",len,len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'c') {
				secs_to_Tims(event_list[index].endtime,datestr,time_format);
				if (len == 0)
					len = strlen(datestr);
				sprintf(buffer,"%*.*s",len,len,datestr);
				datestr[0] = '\0';
			} else if (s[i] == 'e') {
				if (len == 0)
					len = strlen(event_list[index].title);
				sprintf(buffer,"%*.*s",len,len,event_list[index].title);
			} else if (s[i] == 'C') {
				if (len == 0)
					len = strlen(event_list[index].categories);
				sprintf(buffer,"%*.*s",len,len,event_list[index].categories);
			} else if (s[i] == 't') {
				if (len == 0)
					len = strlen(event_list[index].evclass);
				sprintf(buffer,"%*.*s",len,len,event_list[index].evclass);
			} else if (s[i] == 'l') {
				if (len == 0)
					len = strlen(event_list[index].location);
				sprintf(buffer,"%*.*s",len,len,event_list[index].location);
			} else if (s[i] == 'T') {
				if (len == 0)
					len = 1;
				sprintf(buffer,"%*.*d",len,len,event_list[index].transp);
			} else if (s[i] == 'a') {
				if (len == 0)
					len = strlen(event_list[index].attendees);
				sprintf(buffer,"%*.*s",len,len,event_list[index].attendees);
			} else if (s[i] == 'u') {
				if (len == 0)
					len = strlen(event_list[index].url);
				sprintf(buffer,"%*.*s",len,len,event_list[index].url);
			} else {
				fprintf(stderr,"dozcal:  unrecognized conversion "
					"character \"%%%c\" in event form string, "
					"\"%%%s\"\n",s[i],s);
				exit(BAD_EV_FORMAT);
			}
		} else {
			if (s[i] == '\\') {
				if (s[i+1] == 'n') {
					sprintf(buffer,"\n");
					++i;
				} else if (s[i+1] == 't') {
					sprintf(buffer,"\t");
					++i;
				} else {
					sprintf(buffer,"\\");
				}
			} else {
				sprintf(buffer,"%c",s[i]);
			}
		}
		len = MAXLEN + 1;
		strcat(othbuf,buffer);
	}
	strncpy(*(evlines+(numevs-1)),othbuf,MAXLEN);
	return 0;
}

int print_events()
{
	printf("%s",*(evlines+(numevs-1)));
	printf("\n");
	return 0;
}

int clear_events()
{
	int i;

	for (i = 1; i < (numevs); ++i)
		free(*(evlines+i));
	numevs = 1;
	if ((evlines = realloc(evlines,(1 * sizeof(char *)))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted event lines\n");
		exit(INSUFF_MEM);
	}
	return 0;
}

int clear_todos()
{
	int i;

	for (i = 1; i < (numtodos); ++i)
		free(*(todolines+i));
	numtodos = 1;
	if ((todolines = realloc(todolines,(1 * sizeof(char *)))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the formatted todo lines\n");
		exit(INSUFF_MEM);
	}
	return 0;
}

int todocomp(const void *todoone, const void *todotwo)
{
	int priorone = 0; int priortwo = 0;
	int dateone = 0; int datetwo = 0;
	int timeone = 0; int timetwo = 0;
	char *itemone; char *itemtwo;

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
	
int build_globopts_struct()
{
	if ((allopts = malloc(numopts * sizeof(struct globopts))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to store "
			"the global options");
		exit(INSUFF_MEM);
	}
	strcpy(allopts[NOCOLOR].opt,"NOCOLOR");
		allopts[NOCOLOR].r = 0; allopts[NOCOLOR].g = 0; 
		allopts[NOCOLOR].b = 0;
	strcpy(allopts[WHOLEBG].opt,"WHOLE_BG");
		allopts[WHOLEBG].r = 0; allopts[WHOLEBG].g = 0;
		allopts[WHOLEBG].b = 0;
	strcpy(allopts[CALBG].opt,"CALENDAR_BG");
		allopts[CALBG].r = 0; allopts[CALBG].g = 0;
		allopts[CALBG].b = 0;
	strcpy(allopts[EVENTBG].opt,"EVENT_BG");
		allopts[EVENTBG].r = 0; allopts[EVENTBG].g = 0;
		allopts[EVENTBG].b = 0;
	strcpy(allopts[TODOBG].opt,"TODO_BG");
		allopts[TODOBG].r = 0; allopts[TODOBG].g = 0;
		allopts[TODOBG].b = 0;
	strcpy(allopts[CALTITLEFORE].opt,"CAL_TITLE_FORE");
		allopts[CALTITLEFORE].r = 1000; allopts[CALTITLEFORE].g = 1000;
		allopts[CALTITLEFORE].b = 1000;
	strcpy(allopts[CALTITLEBACK].opt,"CAL_TITLE_BACK");
		allopts[CALTITLEBACK].r = 0; allopts[CALTITLEBACK].g = 0;
		allopts[CALTITLEBACK].b = 0;
	strcpy(allopts[CALWEEKFORE].opt,"CAL_WEEK_FORE");
		allopts[CALWEEKFORE].r = 1000; allopts[CALWEEKFORE].g = 1000;
		allopts[CALWEEKFORE].b = 1000;
	strcpy(allopts[CALWEEKBACK].opt,"CAL_WEEK_BACK");
		allopts[CALWEEKBACK].r = 0; allopts[CALWEEKBACK].g = 0;
		allopts[CALWEEKBACK].b = 0;
	strcpy(allopts[TODOTITLEFORE].opt,"TODO_TITLE_FORE");
		allopts[TODOTITLEFORE].r = 1000; allopts[TODOTITLEFORE].g = 1000;
		allopts[TODOTITLEFORE].b = 1000;
	strcpy(allopts[TODOTITLEBACK].opt,"TODO_TITLE_BACK");
		allopts[TODOTITLEBACK].r = 0; allopts[TODOTITLEBACK].g = 0;
		allopts[TODOTITLEBACK].b = 0;
	strcpy(allopts[TODOLINEFORE].opt,"TODO_LINE_FORE");
		allopts[TODOLINEFORE].r = 1000; allopts[TODOLINEFORE].g = 1000;
		allopts[TODOLINEFORE].b = 1000;
	strcpy(allopts[TODOLINEBACK].opt,"TODO_LINE_BACK");
		allopts[TODOLINEBACK].r = 0; allopts[TODOLINEBACK].g = 0;
		allopts[TODOLINEBACK].b = 0;
	strcpy(allopts[TODOFORE].opt,"TODO_FORE");
		allopts[TODOFORE].r = 1000; allopts[TODOFORE].g = 1000;
		allopts[TODOFORE].b = 1000;
	strcpy(allopts[TODOBACK].opt,"TODO_BACK");
		allopts[TODOBACK].r = 0; allopts[TODOBACK].g = 0;
		allopts[TODOBACK].b = 0;
	strcpy(allopts[EVTITLEFORE].opt,"EV_TITLE_FORE");
		allopts[EVTITLEFORE].r = 1000; allopts[EVTITLEFORE].g = 1000;
		allopts[EVTITLEFORE].b = 1000;
	strcpy(allopts[EVTITLEBACK].opt,"EV_TITLE_BACK");
		allopts[EVTITLEBACK].r = 0; allopts[EVTITLEBACK].g = 0;
		allopts[EVTITLEBACK].b = 0;
	strcpy(allopts[EVLINEFORE].opt,"EV_LINE_FORE");
		allopts[EVLINEFORE].r = 0; allopts[EVLINEFORE].g = 0;
		allopts[EVLINEFORE].b = 0;
	strcpy(allopts[EVLINEBACK].opt,"EV_LINE_BACK");
		allopts[EVLINEBACK].r = 0; allopts[EVLINEBACK].g = 0;
		allopts[EVLINEBACK].b = 0;
	strcpy(allopts[EVFORE].opt,"EV_FORE");
		allopts[EVFORE].r = 1000; allopts[EVFORE].g = 1000;
		allopts[EVFORE].b = 1000;
	strcpy(allopts[EVBACK].opt,"EV_BACK");
		allopts[EVBACK].r = 0; allopts[EVBACK].g = 0;
		allopts[EVBACK].b = 0;
	strcpy(allopts[TITLEFORE].opt,"TITLE_FORE");
		allopts[TITLEFORE].r = 0; allopts[TITLEFORE].g = 0;
		allopts[TITLEFORE].b = 0;
	strcpy(allopts[TITLEBACK].opt,"TITLE_BACK");
		allopts[TITLEBACK].r = 1000; allopts[TITLEBACK].g = 1000;
		allopts[TITLEBACK].b = 1000;
	strcpy(allopts[BOTFORE].opt,"BOT_FORE");
		allopts[BOTFORE].r = 0; allopts[BOTFORE].g = 0;
		allopts[BOTFORE].b = 0;
	strcpy(allopts[BOTBACK].opt,"BOT_BACK");
		allopts[BOTBACK].r = 1000; allopts[BOTBACK].g = 1000;
		allopts[BOTBACK].b = 1000;
	strcpy(allopts[WARNINGFORE].opt,"WARNING_FORE");
		allopts[WARNINGFORE].r = 1000; allopts[WARNINGFORE].g = 1000;
		allopts[WARNINGFORE].b = 1000;
	strcpy(allopts[WARNINGBACK].opt,"WARNING_BACK");
		allopts[WARNINGBACK].r = 0; allopts[WARNINGBACK].g = 0;
		allopts[WARNINGBACK].b = 0;
	strcpy(allopts[INACTIVEBORDFORE].opt,"INACTIVE_BORDER_FORE");
		allopts[INACTIVEBORDFORE].r = 1000;
		allopts[INACTIVEBORDFORE].g = 1000;
		allopts[INACTIVEBORDFORE].b = 1000;
	strcpy(allopts[INACTIVEBORDBACK].opt,"INACTIVE_BORDER_BACK");
		allopts[INACTIVEBORDBACK].r = 0;
		allopts[INACTIVEBORDBACK].g = 0;
		allopts[INACTIVEBORDBACK].b = 0;
	strcpy(allopts[ACTIVEBORDFORE].opt,"ACTIVE_BORDER_FORE");
		allopts[ACTIVEBORDFORE].r = 1000; allopts[ACTIVEBORDFORE].g = 1000;
		allopts[ACTIVEBORDFORE].b = 1000;
	strcpy(allopts[ACTIVEBORDBACK].opt,"ACTIVE_BORDER_BACK");
		allopts[ACTIVEBORDBACK].r = 0; allopts[ACTIVEBORDBACK].g = 0;
		allopts[ACTIVEBORDBACK].b = 0;
	strcpy(allopts[WHOLEEVBG].opt,"WHOLE_EV_BG");
		allopts[WHOLEEVBG].r = 0; allopts[WHOLEEVBG].g = 0;
		allopts[WHOLEEVBG].b = 0;
	strcpy(allopts[WHOLETODOBG].opt,"WHOLE_TODO_BG");
		allopts[WHOLETODOBG].r = 0; allopts[WHOLETODOBG].g = 0;
		allopts[WHOLETODOBG].b = 0;
	strcpy(allopts[CALFORE].opt,"CAL_FORE");
		allopts[CALFORE].r = 1000; allopts[CALFORE].g = 1000;
		allopts[CALFORE].b = 1000;
	strcpy(allopts[CALBACK].opt,"CAL_BACK");
		allopts[CALBACK].r = 0; allopts[CALBACK].g = 0;
		allopts[CALBACK].b = 0;
	return 0;
}
