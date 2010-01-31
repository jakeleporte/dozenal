/* +AMDG */
/*
 * This document was begun on 18 Jan MAXLEN-110, the commemoration
 * of St. Prisca, virgin and martyr; and it is humbly
 * dedicated to her and to the Immaculate Heart of Mary for
 * their prayers, and to the Sacred Heart of Jesus, for His
 * mercy.
 */
/*
 * The main routine for the dozenal measurement conversion
 * program.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tgmconv.h"
#include "conv.h"

#define MAXLEN 20

int main(int argc, char *argv[])
{
	char from[MAXLEN];
	char to[MAXLEN];
	char inp[MAXLEN];
	char outp[MAXLEN];
	char doznum[MAXLINE];
	int places = 4;
	char expnot = 0;
	double value = 0.001928;
	int i = 0;
	char c;

/* I know, bletcherous goto; but I need it to break out of
 * the loop/loop/switch when I hit an argument */
	startopt:
	while (--argc > 0 && (*++argv)[0] == '-') {
		if (isdigit(argv[0][1]) || argv[0][1] == '.')
			break; /* negative numbers are not optional args */
		while (c = *++argv[0])
			switch (c) {
			case 'k':
				if (isdigit(*++argv[0])) {
					places = dozprecis(argv[0]);
					goto startopt;
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"doz:  invalid precision quantity\n");
					exit(1);
				} else if (isdigit(*(argv+1)[0])) {
					places = dozprecis(*(argv+1));
					--argc, ++argv;
					goto startopt;
				} else {
					fprintf(stderr,"doz:  invalid precision quantity\n");
					exit(1);
				}
				break;
			case 'o':
				if (isalpha(*++argv[0]) || isdigit(*argv[0]) ||
				*argv[0] == '_') {
					strncpy(outp,*argv,MAXLEN-1);
					if (strlen(*argv) > (MAXLEN-1))
						outp[MAXLEN-1] = '\0';
					goto startopt;
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"tgmconv:  no output unit\n");
					exit(1);
				} else if (isalpha(*(argv+1)[0]) ||
				isdigit(*(argv+1)[0]) || *(argv+1)[0] == '_') {
					strncpy(outp,*argv+1,MAXLEN-1);
					if (strlen(*argv+1) > (MAXLEN-1))
						outp[MAXLEN-1] = '\0';
					--argc, ++argv;
					goto startopt;
				} else {
					fprintf(stderr,"tgmconv:  invalid output unit\n");
					exit(1);
				}
				break;
			case 'i':
				if (isalpha(*++argv[0]) || isdigit(*argv[0]) ||
				*argv[0] == '_') {
					strncpy(inp,*argv,MAXLEN-1);
					if (strlen(*argv) > (MAXLEN-1))
						inp[MAXLEN-1] = '\0';
					goto startopt;
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"tgmconv:  no input unit\n");
					exit(1);
				} else if (isalpha(*(argv+1)[0]) ||
				isdigit(*(argv+1)[0]) || *(argv+1)[0] == '_') {
					strncpy(inp,*argv+1,MAXLEN-1);
					if (strlen(*argv+1) > (MAXLEN-1))
						inp[MAXLEN-1] = '\0';
					--argc, ++argv;
					goto startopt;
				} else {
					fprintf(stderr,"tgmconv:  invalid input unit\n");
					exit(1);
				}
				break;
			case 't':
				if (isalpha(*++argv[0]) || isdigit(*argv[0]) ||
				*argv[0] == '_') {
					strncpy(to,*argv,MAXLEN-1);
					if (strlen(*argv) > (MAXLEN-1))
						to[MAXLEN-1] = '\0';
					goto startopt;
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"tgmconv:  no output system\n");
					exit(1);
				} else if (isalpha(*(argv+1)[0]) ||
				isdigit(*(argv+1)[0]) || *(argv+1)[0] == '_') {
					strncpy(to,*argv+1,MAXLEN-1);
					if (strlen(*argv+1) > (MAXLEN-1))
						to[MAXLEN-1] = '\0';
					--argc, ++argv;
					goto startopt;
				} else {
					fprintf(stderr,"tgmconv:  invalid input unit\n");
					exit(1);
				}
				break;
			case 'f':
				if (isalpha(*++argv[0]) || isdigit(*argv[0]) ||
				*argv[0] == '_') {
					strncpy(from,*argv,MAXLEN-1);
					if (strlen(*argv) > (MAXLEN-1))
						from[MAXLEN-1] = '\0';
					goto startopt;
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"tgmconv:  no output system\n");
					exit(1);
				} else if (isalpha(*(argv+1)[0]) ||
				isdigit(*(argv+1)[0]) || *(argv+1)[0] == '_') {
					strncpy(from,*argv+1,MAXLEN-1);
					if (strlen(*argv+1) > (MAXLEN-1))
						from[MAXLEN-1] = '\0';
					--argc, ++argv;
					goto startopt;
				} else {
					fprintf(stderr,"tgmconv:  invalid input unit\n");
					exit(1);
				}
				break;
			default:
				fprintf(stderr,"tgmconv:  illegal option \"%c\"\n",c);
				break;
			}
	}
	if (argc >= 1) {
		value = doztodec(*argv);
		value = getanswer(outp,inp,value);
		sprintf(doznum,"%.*f",places,value);
		doz(doznum,doznum,places,expnot);
		return 0;
	}
/*	while (getword(doznum,MAXLINE) != EOF);*/
	return 0;
}
