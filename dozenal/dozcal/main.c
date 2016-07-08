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
#include"event_struct.h"

#define NUM_EVENTS (sizeof(event_list) / sizeof(event_list[0]))
#define MAXLEN 256

struct event *event_list;
int recordnums = 0;

int main(int argc, char **argv)
{
	char c; int i;
	int numevents = 0;
	int startdate = -1;
	int enddate = -1;

	if ((event_list = malloc(recordnums++ * sizeof(struct event))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold the "
			"event list\n");
		exit(INSUFF_MEM);
	}
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
		enddate = INT_MAX;
	for (i = 0; i < recordnums-1; ++i) {
		if ((event_list[i].thisdate >= startdate) &&
				(event_list[i].thisdate <= enddate)) {
			printf("%s: %d:  %d --- %d\n",
				event_list[i].title,event_list[i].thisdate,
				event_list[i].starttime,event_list[i].endtime);
		}
	}
	free(event_list);
	return 0;
}
