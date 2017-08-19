/* +AMDG */
/*
 * This document was begun on 15 Aug 1201, the feast of St.
 * Hyacinth of Poland, C, and it is humbly dedicated to him and
 * to the Immaculate Heart of Mary for her prayers, and to
 * the Sacred Heart of Jesus, for His mercy.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"errors.h"

int ranks[] = {1000,500,100,50, 10,  5,  1,0};
char *lets[] = {"M", "D","C","L","X","V","I"};

int change_vals(int *val,int place);

int main(int argc, char **argv)
{
	int ex = 7584;
	int mod;
	int i, j;
	char answer[256] = "";
	char c;

	opterr = 0;
	while ((c = getopt(argc,argv,"R:r:l:V")) != -1) {
		switch(c) {
		case 'V':
			printf("doman v1.0\n");
			printf("Copyright (C) 1201 (2017) by Donald P.  Goodman III\n");
			printf("License GPLv3+:  GNU GPL Version 3 or later "
				"<http://gnu.org/licenses/gpl.html>\n");
			printf("This is free software; you are free to change "
				"and redistribute it.  There is NO WARRANTY, "
				"to the extent permitted by law.\n");
			exit(SUCCESS);
			break;
		case 'R':
			ex = atoi(optarg);
			break;
		case '?':
			if ((optopt == 'r') || (optopt == 'l')) {
				fprintf(stderr,"doman:  option \"%c\" requires "
					"an argument\n",optopt);
				exit(OPT_REQ_ARG);
			}
			fprintf(stderr,"doman:  unrecognized option "
				"\"%c\"\n",optopt);
			exit(UNREC_OPT);
			break;
		}
	}

	printf("%d = ",ex);
	for (i = 0; ranks[i] != 0; ++i) {
		mod = change_vals(&ex,ranks[i]);
		for (j = 0; j < mod; ++j)
			strcat(answer,lets[i]);
	}
	printf("%s\n",answer);
	return 0;
}

int change_vals(int *val, int place)
{
	int mod;

	mod = *val / place;
	*val %= place;
	return mod;
}
