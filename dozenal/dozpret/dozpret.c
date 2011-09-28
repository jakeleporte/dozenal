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
#include "conv.h"

#define MAXLINE 1000

int main(int argc, char *argv[])
{
	int i;
	char expnot = 0;
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
				spacer = "\\,";
				break;
			case 'h': /* Hammond */
				zenpoint = "\'";
				break;
			case 's':
				if (*++argv[0] != '\0') {
					spacer = argv[0];
					for (i=0; i<strlen(argv[0]); ++i)
						++argv[0];
				} else if ((argv+1)[0] == NULL) {
					fprintf(stderr,"dozpret:  invalid spacer character\n");
					return 1;
				} else if (*argv[0] == '\0' && argv[1][0] != '-') {
					spacer = argv[1];
					for (i=0; i<strlen(argv[0])+1; ++i)
						++argv[1];
					++argv;--argc;
				} else {
					fprintf(stderr,"dozpret:  invalid spacer character\n");
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
		dozpret(*argv,spacer,zenpoint);
		return 0;
	}
	while (getword(number,MAXLINE) != EOF)
		dozpret(number,spacer,zenpoint);
	return 0;
}

int dozpret(char *number,char *spacer,char *zenpoint)
{
	int i, j, k, len, both = 0;
	char *zenspot; /* position of zenimal point */
	int count=1; /* number of spaces added so far */
	size_t sepnum; /* number of characters in separator */
	size_t zennum; /* number of characters in zenimal point */

	if (strchr(number,';') == NULL)
		both = 1;
	len = strlen(number);
	sepnum = strlen(spacer)-1;
	zennum = strlen(zenpoint)-1;
	for (i=0; number[i] != ';' && i < len; ++i);
	i = pretwhole(number, spacer, zenpoint);
	len = strlen(number);
	if (both == 1) {
		number[len+1] = '\0';
		printf("%s\n",number);
		return 0;
	}
	pretfrac(number, spacer, i+1);
	printf("%s\n",number);
}

int pretwhole(char *number, char *spacer, char *zenpoint)
{
	int i, j, k, len;
	size_t sepnum, zennum;

	len = strlen(number);
	sepnum = strlen(spacer);
	zennum = strlen(zenpoint);
	for (i=0; number[i] != ';' && i < len; ++i);
	if (i != len) {
		memmove(number+i+zennum-1,number+i,len+1);
		memcpy(number+i,zenpoint,zennum);
	}
	i=i+zennum-1;
	for (j=i,k=0; j>0; --j,++k) {
		if ((k % 4 == 0) && (k != 0)) {
			memmove(number+j+sepnum,number+j,len-j+1);
			memcpy(number+j,spacer,sepnum);
			len = strlen(number);
			i=i+sepnum;
		}
	}
	return i;
}

int pretfrac(char *number, char *spacer, int start)
{
	int j, k, len;
	size_t sepnum;
	
	len = strlen(number);
	sepnum = strlen(spacer);
	for (j=start,k=0; number[j] != '\0'; ++j,++k) {
		if ((k % 4 == 0) && (k != 0)) {
			memmove(number+j+sepnum,number+j,len-j+1);
			memcpy(number+j,spacer,sepnum);
			len = strlen(number);
			j+=sepnum;
		}
	}
	return 0;
}
