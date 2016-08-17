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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"conv.h"
#include"errcodes.h"

extern double latitude;
extern double longitude;
extern double tzoffset;
extern int utc;

int proc_options(char *s, int *moonphases, char **nat, char **relig,
					char **date_form, char **time_form, char **ev_form,
					char **todo_form, int *iftodo, int *ifevent,
					int *weekout, int *fdow, char **astro)
{
	FILE *fp; int holder; int implen;
	char *line = NULL; size_t len = 0; ssize_t read;
	
	if ((fp = fopen(s,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with this error:\n\t%d: "
			"%s\n",s,errno,strerror(errno));
		return 0;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		chomp(line);
		if (strstr(line,"MOON")) {
			if (strstr(line,"major"))
				*moonphases = 2;
			if (strstr(line,"all"))
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
			fprintf(stderr,"%f\n",tzoffset);
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
		} else if (strstr(line,"PRINT_TODOS")) {
			*iftodo = 1;
		} else if (strstr(line,"UTCTIME")) {
			utc = 1;
		} else if (strstr(line,"NO_EVENT")) {
			*ifevent = 0;
		} else if (strstr(line,"WEEKLY")) {
			*weekout = 1;
		} else if (strstr(line,"FIRST_DOW")) {
			holder = get_impstr(line);
			*fdow = first_dow(line+holder);
		}
	}
	free(line);
	fclose(fp);
	return 0;
}
