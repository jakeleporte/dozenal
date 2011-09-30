/*
 * +AMDG  This document was begun on 22 September 11E7, the
 * commemoration of Sts. Cyprian and Justina, VM, and it is
 * humbly dedicated to them and to the Immaculate Heart of
 * Mary for their prayers, and to the Sacred Heart of Jesus
 * for His mercy.
 *
 */
/*
 * Pretty-prints dozenal numbers output by the other dozenal
 * suite programs.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "conv.h"

#define MAXLINE 1000
#define MAXLEN 50

int main(int argc, char *argv[])
{
	int i;
	char expnot = 0, needfreesp = 0, needfreept = 0;
	char c;
	char *spacer = " ";
	char *zenpoint = "\'";
	char number[MAXLINE];

	while (--argc > 0 && (*++argv)[0] == '-') {
		if (isdigit(argv[0][1]) || argv[0][1] == '.')
			break; /* negative numbers are not optional args */
		while (c = *++argv[0])
			switch (c) {
			case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9': case '0':
			case ';': case 'X': case 'E':
				break;
			case 'e':
				expnot = 1;
				break;
			case 'l':
				if ((spacer = malloc(sizeof(char)*4)) == NULL) {
					fprintf(stderr,"dozpret:  insufficient memory\n");
					return 1;
				}
				*spacer = '\\'; *(spacer+1) = ','; *(spacer+2) = '\0';
				needfreesp = 1;
				break;
			case 'h': /* Hammond */
				if ((zenpoint = malloc(sizeof(char)*2)) == NULL) {
					fprintf(stderr,"dozpret:  insufficient memory\n");
					return 1;
				}
				*zenpoint = '\''; *(zenpoint+1) = '\0';
				needfreept = 1;
				break;
/*			case 'p':
				if (*++argv[0] != '\0') {
					zenpoint = argv[0];
					argv[0] = argv[1];
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"dozpret:  invalid zenpoint character\n");
					return 1;
				} else if (*(argv+1)[0] != '-') {
					zenpoint = *(argv+1);
					--argc; ++argv;
					argv[0] = argv[1];
				} else {
					fprintf(stderr,"dozpret:  invalid zenpoint characters(s)\n");
					return 1;
				}
				break;*/
			case 's':
				if (*++argv[0] != '\0') {
					spacer = argv[0];
				} else if (*(argv+1) == NULL) {
					fprintf(stderr,"dozpret:  invalid spacer character\n");
					return 1;
				} else if (*(argv+1)[0] != '-') {
					spacer = *(argv+1);
					--argc; ++argv;
				} else {
					fprintf(stderr,"dozpret:  invalid spacer characters(s)\n");
					return 1;
				}
				break;
			case 'v':
				printf("dozpret v3.1\n");
				printf("Copyright (C) 2011  Donald P. Goodman III\n");
				printf("License GPLv3+:  GNU GPL version 3 or "
				"later <http://gnu.org/licenses/gpl.html>\n");
				printf("This is free software:  you are free "
				"to chnage and redistribute it.  There is NO "
				"WARRANTY, to the extent permitted by law.\n");
				return 0;
				break;
			default:
				fprintf(stderr,"dozpret:  illegal option \"%c\"\n",c);
				break;
			}
	}
	if (argc >= 1) {
		if (strlen(*argv) >=MAXLINE)
			*argv[MAXLINE] = '\0';
		dozpret(*argv,spacer,zenpoint);
	} else {
		while (getword(number,MAXLINE) != EOF)
			dozpret(number,spacer,zenpoint);
	}
	if (needfreesp == 1)
		free(spacer);
	if (needfreept == 1)
		free(zenpoint);
	return 0;
}

int dozpret(char *number,char *spacer,char *zenpoint)
{
	int i, j, k, len, both = 0;
	char fracpart[MAXLINE]; /* fractional part of number */

	if (strchr(number,';') == NULL)
		both = 1;
	len = strlen(number);
	for (i=0; number[i] != ';' && i < len; ++i);
	if (both == 0) {
		strcpy(fracpart,number+i+1);
		number[i] = '\0';
	}
	prettify(number,spacer);
	printf("%s",number);
	if (both == 1) {
		printf("\n");
		return 0;
	}
	printf("%s",zenpoint);
	reverse(fracpart);
	reverse(spacer);
	prettify(fracpart,spacer);
	reverse(fracpart);
	reverse(spacer);
	printf("%s",fracpart);
	printf("\n");
	return 0;
}

int prettify(char *number, char *spacer)
{
	int i, j, k, len;
	size_t sepnum;

	len = i = strlen(number);
	sepnum = strlen(spacer);
	for (j=i,k=0; j>0; --j,++k) {
		if ((k % 4 == 0) && (k != 0)) {
			memmove(number+j+sepnum,number+j,len-j+1);
			memcpy(number+j,spacer,sepnum);
			len = strlen(number);
			i=i+sepnum;
		}
	}
	return 0;
}
