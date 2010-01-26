/* +AMDG */
/*
 * This document was begun on 13 January 2010, the
 * commemoration of the Baptism of Our Lord, and it is
 * humbly dedicated to the Immaculate Heart of Mary for her
 * prayers, and to the Sacred Heart of Jesus, for His mercy.
 */
/*
 * The main function for the dozenal to decimal converter.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include "decconv.h"

int main(int argc, char *argv[])
{
	int c;
	char doznum[MAXLINE];
	char *p;
	int places = 4;
	char expnot = 0;

	while (--argc > 0 && (*++argv)[0] == '-') {
		if (isdigit(argv[0][1]) || argv[0][1] == ';' ||
		argv[0][1] == 'X' || argv[0][1] == 'x' ||
		argv[0][1] == 'A' || argv[0][1] == 'a' ||
		argv[0][1] == 'E' || argv[0][1] == 'B' ||
		argv[0][1] == 'b')
			break; /* negative numbers are not optional args */
		while (c = *++argv[0])
			switch (c) {
			case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9': case '0':
			case ';': case 'A': case 'a': case 'X': case 'x':
			case 'E': case 'B': case 'b':
				break;
			case 'k':
				if (isdigit(*++argv[0])) {
					places = precision(argv[0]);
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"dec:  invalid precision quantity\n");
					exit(1);
				} else if (isdigit(*(argv+1)[0])) {
					places = precision(*(argv+1));
					--argc, ++argv;
				} else {
					fprintf(stderr,"dec:  invalid precision quantity\n");
					exit(1);
				}
				break;
			case 'e':
				expnot = 1;
				break;
			default:
				fprintf(stderr,"dec:  illegal option \"%c\"\n",c);
				break;
			}
	}
	if (argc >= 1) {
		if ((p = malloc(MAXLINE)) == NULL)
			fprintf(stderr,"dec:  insufficient memory; dying");
		strcpy(p,*argv);
		dec(p,places,expnot);
		free(p);
		return 0;
	}
	while (getword(doznum,MAXLINE) != EOF)
		dec(doznum,places,expnot);
	return 0;
}

