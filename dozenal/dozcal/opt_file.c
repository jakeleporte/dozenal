/*
 * +AMDG
 */
/*
 * This document was begun on E July 1200, the Comm. of St.
 * Pius I, PM, and it is humbly dedicated to him and to the
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

/* to get getline() defined */
#ifdef TARGGNU
	#define _POSIX_C_SOURCE 200809L
	#define _XOPEN_SOURCE 700
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<regex.h>
#include"conv.h"
#include"utility.h"
#include"errcodes.h"
#include"main_func.h"
#include"event_struct.h"

#define MAX_ERR_LENGTH 256

extern double latitude;
extern double longitude;
extern double tzoffset;
extern int utc;
extern struct globopts *allopts;
extern int numopts;

int proc_color(char *s, char *t, int ind);
int find_color_ind(char *s);
int check_line(char *s);

int proc_options(char *s, int *moonphases, char **nat, char **relig,
					char **date_form, char **time_form, char **ev_form,
					char **todo_form, int *iftodo, int *ifevent,
					int *weekout, int *fdow, char **astro)
{
	FILE *fp; int holder;
	char *line = NULL; size_t len = 0; ssize_t read;
	int ind;

	if (strcmp(s,"-") == 0)
		return 0;
	if ((fp = fopen(s,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with this error:\n\t%d: "
			"%s\n",s,errno,strerror(errno));
		return 0;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		if (line[0] == '#')
			continue;
		chomp(line);
		if (strstr(line,"PRINT_TODOS")) {
			*iftodo = 1;
			continue;
		} else if (strstr(line,"UTCTIME")) {
			utc = 1;
			continue;
		} else if (strstr(line,"NO_EVENT")) {
			*ifevent = 0;
			continue;
		} else if (strstr(line,"WEEKLY")) {
			*weekout = 1;
			continue;
		} else if (strstr(line,"NOCOLOR")) {
			allopts[NOCOLOR].colconst = -1;
			continue;
		}
		if (check_line(line) >= 1)
			continue;
		if (strstr(line,"MOON")) {
			if (strstr(line,"major"))
				*moonphases = 2;
			else if (strstr(line,"all"))
				*moonphases = 1;
		} else if (strstr(line,"RELIG")) {
			holder = get_impstr(line);
			*relig = realloc(*relig,((strlen(line)+1) * sizeof(char)));
			strcpy(*relig,line+holder);
		} else if (strstr(line,"NATION")) {
			holder = get_impstr(line);
			*nat = realloc(*nat,((strlen(line)+1) * sizeof(char)));
			strcpy(*nat,line+holder);
		} else if (strstr(line,"ASTRON")) {
			holder = get_impstr(line);
			*astro = realloc(*astro,((strlen(line)+1) * sizeof(char)));
			strcpy(*astro,line+holder);
		} else if (strstr(line,"TIMEZONE")) {
			holder = get_impstr(line);
			tzoffset = doztodec(line+holder);
		} else if (strstr(line,"GEOG")) {
			holder = get_impstr(line);
			proc_geog(line+holder);
		} else if (strstr(line,"DATE_FORMAT")) {
			holder = get_impstr(line);
			*date_form = realloc(*date_form,((strlen(line)+1) * sizeof(char)));
			strcpy(*date_form,line+holder);
		} else if (strstr(line,"TIME_FORMAT")) {
			holder = get_impstr(line);
			*time_form = realloc(*time_form,((strlen(line)+1) * sizeof(char)));
			strcpy(*time_form,line+holder);
		} else if (strstr(line,"EVENT_FORMAT")) {
			holder = get_impstr(line);
			*ev_form = realloc(*ev_form,((strlen(line)+1) * sizeof(char)));
			strcpy(*ev_form,line+holder);
		} else if (strstr(line,"TODO_FORMAT")) {
			holder = get_impstr(line);
			*todo_form = realloc(*todo_form,((strlen(line)+1) * sizeof(char)));
			strcpy(*todo_form,line+holder);
		} else if (strstr(line,"INPUT")) {
			holder = get_impstr(line);
			process_file(line+holder);
		} else if (strstr(line,"SCRIPT")) {
			holder = get_impstr(line);
			call_lua(line+holder);
		} else if (strstr(line,"FIRST_DOW")) {
			holder = get_impstr(line);
			*fdow = first_dow(line+holder);
		} else if (strstr(line,"WHOLE_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CALENDAR_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EVENT_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_TITLE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_TITLE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_WEEK_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_WEEK_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_TITLE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_TITLE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_LINE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_LINE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TODO_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_TITLE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_TITLE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_LINE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_LINE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"EV_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TITLE_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"TITLE_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"BOT_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"BOT_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"WARNING_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"WARNING_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"INACTIVE_BORDER_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"INACTIVE_BORDER_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"ACTIVE_BORDER_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"ACTIVE_BORDER_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"WHOLE_EV_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"WHOLE_TODO_BG")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_FORE")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else if (strstr(line,"CAL_BACK")) {
			ind = find_color_ind(line);
			holder = get_impstr(line);
			proc_color(line+holder,line,ind);
		} else {
			fprintf(stderr,"dozcal:  option \"%s\" is not "
				"recognized; skipping...\n",line);
		}
	}
	free(line);
	fclose(fp);
	return 0;
}

int proc_color(char *s, char *t, int ind)
{
	int result; int errornum;
	char holder[SHORTLEN];
	char err[MAX_ERR_LENGTH+1];
	regmatch_t pmatch[4];
	regex_t regone;
	char *colpat = 
		"\\([0-9XE][0-9XE]*\\),\\([0-9XE][0-9XE]*\\),\\([0-9XE][0-9XE]*\\)";

	holder[0] = '\0';
	lower_str(s);
	if (strstr(s,"red")) {
		allopts[ind].r = 1000; allopts[ind].g = 0; allopts[ind].b = 0;
	} else if (strstr(s,"blue")) {
		allopts[ind].r = 0; allopts[ind].g = 0; allopts[ind].b = 1000;
	} else if (strstr(s,"green")) {
		allopts[ind].r = 0; allopts[ind].g = 1000; allopts[ind].b = 0;
	} else if (strstr(s,"yellow")) {
		allopts[ind].r = 1000; allopts[ind].g = 1000; allopts[ind].b = 0;
	} else if (strstr(s,"magenta")) {
		allopts[ind].r = 1000; allopts[ind].g = 0; allopts[ind].b = 1000;
	} else if (strstr(s,"cyan")) {
		allopts[ind].r = 0; allopts[ind].g = 1000; allopts[ind].b = 1000;
	} else if (strstr(s,"black")) {
		allopts[ind].r = 0; allopts[ind].g = 0; allopts[ind].b = 0;
	} else if (strstr(s,"white")) {
		allopts[ind].r = 1000; allopts[ind].g = 1000; allopts[ind].b = 1000;
	} else {
		upper_str(s);
		if ((errornum = regcomp(&regone,colpat,0)) != 0) {
			regerror(errornum,&regone,err,MAX_ERR_LENGTH);
			return -1;
		}
		result = regexec(&regone,s,4,pmatch,0);
		regfree(&regone);
		if (result != 0) {		/* no match */
			if (strstr(t,"FORE")) {
				allopts[ind].r = 1000; allopts[ind].g = 1000;
				allopts[ind].b = 1000;
			} else {
				allopts[ind].r = 0; allopts[ind].g = 0;
				allopts[ind].b = 0;
			}
		} else {						/* match */
			sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
				s+pmatch[1].rm_so);
			allopts[ind].r = (int) doztodec(holder);
			holder[0] = '\0';
			sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
				s+pmatch[2].rm_so);
			allopts[ind].g = (int) doztodec(holder);
			holder[0] = '\0';
			sprintf(holder,"%.*s",pmatch[3].rm_eo - pmatch[3].rm_so, 
				s+pmatch[3].rm_so);
			allopts[ind].b = (int) doztodec(holder);
		}
	}
	return 0;
}

int find_color_ind(char *s)
{
	int i;
	char buffer[SHORTLEN+SHORTLEN];

	for (i = 0; s[i] != ':'; ++i)
		buffer[i] = s[i];
	buffer[i] = '\0';
	for (i = 0; i < numopts; ++i) {
		if (!strcmp(allopts[i].opt,buffer)) {
			return i;
		}
	}
	return -1;
}

/* if -1, error; if 0, line is fine; if 1, line is bad; if
 * 2, line is blank */
int check_line(char *s)
{
	int result; int errornum;
	char err[MAX_ERR_LENGTH+1];
	regmatch_t pmatch[4];
	regex_t regone;
	char *optpat = "[A-Z_][A-Z_]*:[\t ]";
	char *blank = "^[ \t\n]*$";

	if ((errornum = regcomp(&regone,blank,0)) != 0) {
		regerror(errornum,&regone,err,MAX_ERR_LENGTH);
		return -1;
	}
	result = regexec(&regone,s,4,pmatch,0);
	regfree(&regone);
	if (result == 0)
		return 2;
	if ((errornum = regcomp(&regone,optpat,0)) != 0) {
		regerror(errornum,&regone,err,MAX_ERR_LENGTH);
		return -1;
	}
	result = regexec(&regone,s,4,pmatch,0);
	regfree(&regone);
	if (result != 0) {		/* no match */
		fprintf(stderr,"dozcal:  option line \"%s\" is not "
			"recognized, or\n\tis not properly formed; "
			"format is \"OPTION:  value\";\n\tskipping malformed "
			"option...\n",s);
		return 1;
	}
	return 0;
}
