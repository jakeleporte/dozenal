/*
 * +AMDG
*/
/*
 * This program was begun on 9 Oct 1203, the feast of St.
 * John Leonard, C, and it is humbly dedicated to him and to
 * the Immaculate Heart of Mary, for their prayers; and to
 * the Sacred Heart of Jesus, for His mercy.
 */

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>

int parse_date(char *s, int sorend);
int strip_value(char *s);
int clean_str(char *s);
int parse_freq(char *s);

#define START_DATE 0
#define END_DATE 1

int main(int argc, char *argv[])
{
	FILE *fp; char *line = NULL; size_t len = 0; ssize_t read;
	char *icalfile;
	char *nline;
	char c;

	opterr = 0;
	while ((c = getopt(argc,argv,"f:")) != -1) {
		if (c == 'f')
			icalfile = optarg;
	}
	if ((fp = fopen(icalfile,"r")) == NULL) {
		fprintf(stderr,"dozcal:  unable to open file "
			"\"%s\", with this error:\n\t%d: "
			"%s\n",icalfile,errno,strerror(errno));
		return 0;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		clean_str(line);
		if (strstr(line,"BEGIN:VEVENT")) {
			printf("\n\n[EVENT]\n");
		} else if (strstr(line,"DTSTART")) {
			printf("START_DATE:\t");
			parse_date(strstr(line,":")+1,START_DATE);
		} else if (strstr(line,"DTEND")) {
			printf("END_DATE:\t");
			parse_date(strstr(line,":")+1,END_DATE);
		} else if (strstr(line,"SUMMARY")) {
			printf("TITLE:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"CLASS")) {
			printf("CLASS:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"CATEGORIES")) {
			printf("CATEGORY:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"LOCATION") || strstr(line,"GEO:")) {
			printf("LOCATION:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"URL:")) {
			printf("URL:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"ATTENDEES:")) {
			printf("ATTENDEES:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"TRANSPARENT:")) {
			printf("TRANSPARENT:\t");
			strip_value(nline = strstr(line,":")+1);
			printf("%s\n",nline);
		} else if (strstr(line,"FREQ=")) {
			parse_freq(line);
		}
	}
	fclose(fp);
	return 0;
}

char *get_end_range(char *s, char c, int *num)
{
	char *e;
	int i;

	e = s;
	for (i = 0; (s[i] != '\0') && (s[i] != c); ++i)
		++e;
	*num = i;
	if (e == '\0')
		return NULL;
	return e;
}

int parse_freq(char *s)
{
	char *eq;
	char *p;
	char *st;
	int n;

	eq = strstr(s,"FREQ=") + 5;
	if (strstr(eq,"MONTHLY"))
		printf("FREQ:\tmonthly");
	if (strstr(eq,"YEARLY"))
		printf("FREQ:\tyearly");
	if (strstr(eq,"WEEKLY")) {
		printf("FREQ:\t");
		if (strstr(eq,"BYDAY=SU")) {
			printf(" Sunday ");
		} else if (strstr(eq,"BYDAY=MO")) {
			printf(" Monday ");
		} else if (strstr(eq,"BYDAY=TU")) {
			printf(" Tuesday ");
		} else if (strstr(eq,"BYDAY=WE")) {
			printf(" Wednesday ");
		} else if (strstr(eq,"BYDAY=TH")) {
			printf(" Thursday ");
		} else if (strstr(eq,"BYDAY=FR")) {
			printf(" Friday ");
		} else if (strstr(eq,"BYDAY=SA")) {
			printf(" Saturday ");
		}
		printf("\nINTERVAL:  7");
	}
	if ((st = strstr(eq,"UNTIL=")) != NULL) {
		p = get_end_range(st+strlen("UNTIL=")+1,';',&n);
		if (p == NULL)
			p = get_end_range(st,':',&n);
		printf("\tEND_DATE:\t%.*s\n",n,st+6);
	}
	printf("\n");
	printf("\n\tFREQ:  %s\n",eq);
	if ((p = strstr(eq,"INTERVAL=")) != NULL) {
		printf("INTERVAL:\t%c\n",*(p+9));
	}
	return 0;
}

int clean_str(char *s)
{
	char *src, *dst;

	for (src = dst = s; *src != '\0'; ++src) {
		*dst = *src;
		if (*dst != '\n') ++dst;
	}
	*dst = '\0';
	return 0;
}

int strip_value(char *s)
{
	char *src, *dst;
	for (src = dst = s; *src != '\0'; ++src) {
		*dst = *src;
		if ((*dst != '\\') && (*(dst+1) != '\\')) ++dst;
	}
	*dst = '\0';
//	printf("%s\n",s);
	return 0;
}

int parse_date(char *s, int sorend)
{
	int year,mon,day,hr,min;

	sscanf(s,"%4d%2d%2dT%2d%2d",&year,&mon,&day,&hr,&min);
	printf("%04d-%02d-%02d\n",year,mon,day);
	if (sorend == 0)
		printf("START_TIME:\t");
	else if (sorend == 1)
		printf("END_TIME:\t");
	printf("%02d:%02d\n",hr,min);
	return 0;
}
