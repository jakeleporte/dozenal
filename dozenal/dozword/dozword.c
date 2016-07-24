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
#include <unistd.h>

int printwords(char *number,char scheme);

#define SUCCESS 0
#define BAD_OPTION 1
#define OPT_REQ_ARG 2

int main(int argc, char *argv[])
{
	char c; char scheme = 's';
	char number[24];

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
			strcpy(number,optarg);
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
	printwords(number,scheme);
	printf("\n");

	return 0;
}

/* prints the number word */

int printnumword(char *number)
{
	if (*number == '0')
		printf("zero");
	else if (*number == '1')
		printf("one");
	else if (*number == '2')
		printf("two");
	else if (*number == '3')
		printf("three");
	else if (*number == '4')
		printf("four");
	else if (*number == '5')
		printf("five");
	else if (*number == '6')
		printf("six");
	else if (*number == '7')
		printf("seven");
	else if (*number == '8')
		printf("eight");
	else if (*number == '9')
		printf("nine");
	else if (*number == 'X')
		printf("ten");
	else if (*number == 'E')
		printf("elv");
	return 0;
}

/* prints the exponent level appropriate for current number */

int printpend(int currplace)
{
	if (currplace == 2)
		printf("zen ");
	else if (currplace == 3)
		printf("duna ");
	else if (currplace == 4)
		printf("trina ");
	else if (currplace == 5)
		printf("quedra ");
	else if (currplace == 6)
		printf("quen ");
	else if (currplace == 7)
		printf("hes ");
	else if (currplace == 8)
		printf("sev ");
	else if (currplace == 9)
		printf("ak ");
	else if (currplace == 10)
		printf("neen ");
	else if (currplace == 11)
		printf("dex ");
	else if (currplace == 12)
		printf("lef ");
	else if (currplace == 13)
		printf("zennil ");
	else if (currplace == 14)
		printf("zenzen ");
	else if (currplace == 15)
		printf("zenduna ");
	return 0;
}

int printsdn(int currplace)
{
	if (currplace == 2)
		printf("unqua ");
	else if (currplace == 3)
		printf("biqua ");
	else if (currplace == 4)
		printf("triqua ");
	else if (currplace == 5)
		printf("quadqua ");
	else if (currplace == 6)
		printf("pentqua ");
	else if (currplace == 7)
		printf("hexqua ");
	else if (currplace == 8)
		printf("septqua ");
	else if (currplace == 9)
		printf("octqua ");
	else if (currplace == 10)
		printf("ennqua ");
	else if (currplace == 11)
		printf("decqua ");
	else if (currplace == 12)
		printf("levqua ");
	else if (currplace == 13)
		printf("unnilqua ");
	else if (currplace == 14)
		printf("ununqua ");
	else if (currplace == 15)
		printf("unbiqua ");
	return 0;
}

/* print the words for the number */

int printwords(char *number,char scheme)
{
//	int maxlength, numlength;
	int i; int len;

/*	for (i=0; number[i] != ';' && number[i] != '\0'; ++i);
	maxlength = numlength = i;
	for (i=0; i <= maxlength; i++) {
		printnumword(number+i);
		if (scheme == 'p')
			printpend(numlength);
		else if (scheme == 's')
			printsdn(numlength);
		--numlength;
	}*/
	len = strlen(number);
	for (i = 0; i <= len; ++i) {
		printnumword(number+i);
		if ((i == 0) && (scheme == 'p'))
			printpend(len);
		else if ((i == 0) && (scheme == 's'))
			printsdn(len);
	}
}
