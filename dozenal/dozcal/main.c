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
#include"errcodes.h"

int main(int argc, char **argv)
{
	char c;
	char *filename;

	if ((filename = malloc(1 * sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to "
			"initialize variables\n");
		exit(INSUFF_MEM);
	}
	opterr = 0;
	while ((c = getopt(argc,argv,"Vf:d:")) != -1) {
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
	return 0;
}
