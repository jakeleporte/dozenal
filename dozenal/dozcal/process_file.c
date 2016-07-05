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

#define NUM_EVENTS (sizeof(*event_list) / sizeof(*event_list[0]))

int process_file(char *s,struct event **event_list)
{
	FILE *fp; char *line = NULL; size_t len = 0; ssize_t read;

	if ((fp = fopen(s,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with the following error:\n\t%d: "
			"%s\n",s,errno,strerror(errno));
		exit(BAD_FILE);
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		chomp(line);
		proc_line(line,event_list);
	}
//	free(line);
	return 0;
}

int proc_line(char *s,struct event **event_list)
{
	static int numevents = 1;

	if (strstr(s,"[EVENT]")) {
		++numevents;
		*event_list = realloc(*event_list,(numevents * sizeof(struct event)));
	}
//	*event_list = realloc(*event_list,(6 * sizeof(struct event)));
//	strcpy(event_list[1]->title,"you");
	return 0;
}
