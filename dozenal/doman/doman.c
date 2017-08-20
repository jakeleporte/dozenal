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

#define MAXLEN 256

int *ranks;
char **lets;

int change_vals(int *val,int place);
int check_args();
int count_commas(char *s);

int main(int argc, char **argv)
{
	int ex = 7584;
	int mod;
	int i, j;
	char answer[MAXLEN] = "";
	char c;
	int numranks;
	int numlets;
	char *token;
	/* initialize the default ranks and lets */
	ranks = (int *)malloc(8 * sizeof(int));
	ranks[0] = 1000; ranks[1] = 500; ranks[2] = 100;
	ranks[3] = 50; ranks[4] = 10; ranks[5] = 5;
	ranks[6] = 1; ranks[7] = 0;
	lets = malloc(8 * sizeof(char *));
	for (i = 0; i < 8; ++i)
		*(lets+i) = malloc(3 * sizeof(char));
	strcpy(lets[0],"Mm"); strcpy(lets[1],"Dd"); strcpy(lets[2],"Cc");
	strcpy(lets[3],"Ll"); strcpy(lets[4],"Xx"); strcpy(lets[5],"Vv");
	strcpy(lets[6],"Ii"); strcpy(lets[7],"\0");
		
	opterr = 0;
	while ((c = getopt(argc,argv,"R:r:s:V")) != -1) {
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
		case 'r':
			numranks = count_commas(optarg) + 2;
			ranks = (int *)realloc(ranks,numranks * sizeof(int));
			i = 0;
			token = strtok(optarg,",");
			while (token != NULL) {
				ranks[i++] = atoi(token);
				token = strtok(NULL,",");
			}
			ranks[i] = 0;
			break;
		case 's':
			numranks = count_commas(optarg) + 2;
			for (i = 0; strcmp(lets[i],"\0"); ++i)
				free(lets[i]);
			free(lets[i]);
			lets = realloc(lets,numranks * sizeof(char *));
			i = 0;
			token = strtok(optarg,",");
			while (token != NULL) {
				*(lets+i) = malloc((strlen(token) + 1) * sizeof(char));
				strcpy(*(lets+i),token);
				token = strtok(NULL,",");
				i++;
			}
			*(lets+i) = malloc(2 * sizeof(char));
			strcpy(*(lets+i),"\0");
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
	check_args();
	printf("%d = ",ex);
	for (i = 0; ranks[i] != 0; ++i) {
		mod = change_vals(&ex,ranks[i]);
		for (j = 0; j < mod; ++j)
			strcat(answer,lets[i]);
	}
	printf("|%s|\n",answer);
	free(ranks);
	for (i = 0; strcmp(lets[i],"\0"); ++i)
		free(lets[i]);
	free(lets[i]);
	free(lets);
	return 0;
}

int change_vals(int *val, int place)
{
	int mod;

	mod = *val / place;
	*val %= place;
	return mod;
}

int check_args()
{
	int i, j;
	for (i = 0; ranks[i] != 0; ++i);
	for (j = 0; strlen(lets[j]) != 0; ++j);
	if (i != j) {
		fprintf(stderr,"doman:  error:  you have %d "
			"ranks and %d symbols; you should have "
			"an equal number of both\n",i,j);
		exit(MISMATCHED_RANKS_SYMS);
	}
	return 0;
}

int count_commas(char *s)
{
	int i;
	int j = 0;

	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == ',')
			++j;
	}
	return j;
}
