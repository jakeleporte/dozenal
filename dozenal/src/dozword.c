/*
 * +AMDG  This program was begun on 14 November 2008, the
 * feast of St. Josaphat, and it is humbly dedicated to him
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
 *
 * dozword:  inputs a dozenal number and outputs a verbal
 * representation thereof, according to TGM's
 * specifications.
 *
 * (C) Copyright 2010, 2011  Donald P. Goodman III
 *
 * This file is part of dozword.
 *
 * dozword is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozword is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozword.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include "conv.h"

int printwords(char *number,char scheme);
int validate_num(char *number);

#define NUMLEN 36 
#define SUCCESS 0
#define BAD_OPTION 1
#define OPT_REQ_ARG 2
#define BAD_CHAR 3

int main(int argc, char *argv[])
{
	char c; char scheme = 's';
	char number[NUMLEN];

	number[0] = '\0';
	opterr = 0;
	while ((c = getopt(argc,argv,"Vpsn:")) != -1) {
		switch (c) {
		case 'V':
			printf("dozword v4.0\n");
			printf("Copyright (C) 2010, 2011  Donald P. Goodman III\n");
			printf("License GPLv3+:  GNU GPL version 3 or "
				"later <http://gnu.org/licenses/gpl.html>\n");
			printf("This is free software:  you are free "
				"to change and redistribute it.  There is NO "
				"WARRANTY, to the extent permitted by law.\n");
			exit(SUCCESS);
			break;
		case 'n':
			strncpy(number,optarg,NUMLEN-1);
			break;
		case 's':
			scheme = 's';
			break;
		case 'p':
			scheme = 'p';
			break;
		case '?':
			if (optopt == 'n') {
				fprintf(stderr,"dozcal:  option \"%c\" requires "
					"an argument\n",optopt);
				exit(OPT_REQ_ARG);
			}
			fprintf(stderr,"dozword:  unrecognized option "
				"\"%c\"\n",optopt);
			exit(BAD_OPTION);
			break;
		}
	}
	if (strlen(number) > 0) {
		printwords(number,scheme);
		printf("\n");
		exit(SUCCESS);
	}
	while (getword(number,NUMLEN) != EOF) {
		printwords(number,scheme);
		printf("\n");
	}
	return SUCCESS;
}

/* prints the number word */

int printnumword(char *number)
{
	if (*number == '0')
		printf("zero ");
	else if (*number == '1')
		printf("one ");
	else if (*number == '2')
		printf("two ");
	else if (*number == '3')
		printf("three ");
	else if (*number == '4')
		printf("four ");
	else if (*number == '5')
		printf("five ");
	else if (*number == '6')
		printf("six ");
	else if (*number == '7')
		printf("seven ");
	else if (*number == '8')
		printf("eight ");
	else if (*number == '9')
		printf("nine ");
	else if (*number == 'X')
		printf("ten ");
	else if (*number == 'E')
		printf("elv ");
	else if (*number == ';')
		printf("dit ");
	return 0;
}

int printpend(int currplace)
{
	char numdigs[7];
	int i;

	if (currplace > 2985983)
		currplace = 2985982;
	dectodoz(numdigs,((double)currplace-1));
	for (i = 0; numdigs[i] != '\0'; ++i) {
		switch (numdigs[i]) {
		case '0': printf("nil"); break;
		case '1': printf("zen"); break;
		case '2': printf("dun"); break;
		case '3': printf("trin"); break;
		case '4': printf("quedr"); break;
		case '5': printf("quen"); break;
		case '6': printf("hes"); break;
		case '7': printf("sev"); break;
		case '8': printf("ak"); break;
		case '9': printf("neen"); break;
		case 'X': printf("dex"); break;
		case 'E': printf("lef"); break;
		}
	}
	printf("a ");
	return 0;
}

int printsdn(int currplace)
{
	char numdigs[7];
	int i;

	dectodoz(numdigs,((double)currplace-1));
	for (i = 0; numdigs[i] != '\0'; ++i) {
		switch (numdigs[i]) {
		case '0': printf("nil"); break;
		case '1': printf("un"); break;
		case '2': printf("bi"); break;
		case '3': printf("tri"); break;
		case '4': printf("quad"); break;
		case '5': printf("pent"); break;
		case '6': printf("hex"); break;
		case '7': printf("sept"); break;
		case '8': printf("oct"); break;
		case '9': printf("enn"); break;
		case 'X': printf("dec"); break;
		case 'E': printf("lev"); break;
		}
	}
	printf("qua ");
	return 0;
}

/* print the words for the number */

int printwords(char *number,char scheme)
{
	int i; int len;

	validate_num(number);
	for (i = 0; number[i] != '\0' && (isdigit(number[i]) ||
	(number[i] == 'X') || (number[i] == 'E')); ++i);
	len = i;
	for (i = 0; number[i] != '\0'; ++i) {
		printnumword(number+i);
		if (len > 0) {
			if ((i == 0) && (scheme == 'p'))
				printpend(len);
			else if ((i == 0) && (scheme == 's'))
				printsdn(len);
		}
	}
	return 0;
}

int validate_num(char *number)
{
	int i;

	for (i = 0; number[i] != '\0'; ++i) {
		if (isdigit(number[i]) || (number[i] == 'X') ||
			(number[i] == 'E') || (number[i] == 'T') ||
			(number[i] == 'B') || (number[i] == ';') ||
			(number[i] == 'A')) {
			if ((number[i] == 'T') || (number[i] == 'A'))
				number[i] = 'X';
			if ((number[i] == 'B'))
				number[i] = 'E';
		} else {
			fprintf(stderr,"dozword:  character \"%c\" is "
					"not a valid dozenal character\n",number[i]);
			exit(BAD_CHAR);
		}
	}
	return 0;
}
