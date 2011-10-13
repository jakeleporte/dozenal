/*
 * +AMDG
 */
/*
 * This document was begun on X Oct 11E7, the feast of St.
 * Francis Borgia, and it is humbly dedicated to him and to
 * the Immaculate Heart of Mary for their prayers, and to
 * the Sacred Heart of Jesus for His mercy.
 *
 */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "conv.h"

#define SIZE 256

/* global array of structs for days of week */
struct nameday {
	char *longname; 		/* long form */
	char *shortname;		/* abbreviation */
	int num;				/* number (0-6) */
} weekdays[] = {
	"Sunday", "Sun", 0,
	"Monday", "Mon", 1,
	"Tuesday", "Tue", 2,
	"Wednesday", "Wed", 3,
	"Thursday", "Thu", 4,
	"Friday", "Fri", 5,
	"Saturday", "Sat", 6,
};
struct monthdays {
	char *longname; char *shortname;
	int num;
} months[] = {
	"January", "Jan", 0,
	"February", "Feb", 1,
	"March", "Mar", 2,
	"April", "Apr", 3,
	"May", "May", 4,
	"June", "Jun", 5,
	"July", "Jul", 6,
	"August", "Aug", 7,
	"September", "Sep", 8,
	"October", "Oct", 9,
	"November", "Nov", 10,
	"December", "Dec", 11,
};

char *parse_for_month(char *s, struct tm *thetime);

/* governing function, calls others */
int process_date(char *s,struct tm *thetime)
{
	int i;
	char *monpointer;

	printdate(thetime);
	parse_for_weekday(s,thetime);
	printdate(thetime);
	monpointer = parse_for_month(s,thetime);
	if (monpointer != NULL)
		parse_for_date(s,monpointer,thetime);
	printf("HERE:  %s; %d\n",monpointer,thetime->tm_mon);
/*	printf("%d\n",dayofweek(20,00,1,1));*/
	exit(0);
}

/* tries to parse date from position of month; scans backward 
 * for date, then forward; if not found, make date 1 */
int parse_for_date(char *s, char *monthpoint, struct tm *thetime)
{
	char *pt;
	char daynum[SIZE] = "NULL";
	int i = 0;
	int date;

	pt = monthpoint;
	if (monthpoint == NULL) {
	}
	while (pt >= s) {
		if (isdigit(*pt) || (*pt == 'X') || (*pt == 'E'))
			daynum[i++] = *pt;
		--pt;
	}
	daynum[i] = '\0';
	if (daynum[0] != '\0') {
		for (i=0; daynum[i] == '0' && daynum[i] != '\0'; ++i);
		reverse(daynum+i);
		date = doztodec(daynum+i);
	} else {  /* FIXME:  do American slash order, too */
		date = 1;
	}
	/* error checking for date numbers per month */
	printf("DAYNUM:  %d\n",date);
	thetime->tm_mday = date;
	return 0;
}

/* parses date string for months, short, long, or alpha;
 * returns a pointer to beginning of string if present, NULL
 * if not; instills in struct thetime; if absent, use 0 */
char *parse_for_month(char *s, struct tm *thetime)
{
	int i, j, flag;
	char *monthpoint = NULL;
	char monthnum[SIZE];

	flag = j = 0;
	for (i=0; i <= 11; ++i) {
		if ((monthpoint = strstr(s,months[i].longname)) || 
		(monthpoint = strstr(s,months[i].shortname))) {
			thetime->tm_mon = months[i].num;
			break;
		}
	}
	if (monthpoint != NULL) {
		thetime->tm_mon = i;
		return monthpoint;
	}
	for (i=0; s[i] != '\0'; ++i) {
		if (s[i] == '-') {
			if (flag == 0)
				monthpoint = &s[i+1];
			flag = (flag == 0) ? 1 : 0;
		}
		if (flag == 1 && (isdigit(s[i]) || s[i]=='X' || s[i]=='E'))
			monthnum[j++] = s[i];
	}
	monthnum[j] == '\0';
	if (monthpoint != NULL) {
		thetime->tm_mon = (int)doztodec(monthnum) - 1;
		return monthpoint;
	}
}

/* parses string for weekdays and related modifiers; if
 * weekday on its own, assume "this coming"; if "last", then
 * the week prior */
int parse_for_weekday(char *s, struct tm *thetime)
{
	int tmp, tmp2, i;
	int dayyear, maxdays;
	char *daypoint = NULL; /* point at weekday in s */
	char *lastpoint; /* if "last" or "next" is in string */

	tmp = thetime->tm_wday;	 /* tmp:  current weekday num */
	for (i=0; i <= 6; ++i) {
		if ((daypoint = strstr(s,weekdays[i].longname)) || 
		(daypoint = strstr(s,weekdays[i].shortname))) {
			tmp2 = weekdays[i].num;  /* tmp2:  new weekday num */
			break;
		}
	}
	if (daypoint == NULL)
		return 0;
	thetime->tm_wday = tmp2; /* new weekday into struct */
	if ((lastpoint = strstr(s,"last")) && (lastpoint <
	daypoint) && (lastpoint != NULL)) {
		if (tmp2 < tmp)
			dayyear = tmp2 - tmp;
		else
			dayyear = (7 - (abs(tmp - tmp2))) * -1;
	} else {
		tmp2 = (tmp2 == 0) ? 7 : tmp2;
		if (tmp2 > tmp)
			dayyear = abs(tmp - tmp2);
		else
			dayyear = (7 - (abs(tmp - tmp2)));
		if ((lastpoint = strstr(s,"next")) && (lastpoint <
		daypoint) && (lastpoint != NULL))
			dayyear += 7;
	}
	maxdays = (leapyear(0,thetime->tm_year+1900)) ? 364 : 365;
	dayyear += thetime->tm_yday;
	thetime->tm_yday = dayyear; /* put yday into struct */
	if (dayyear > maxdays)
		dayyear -= maxdays;
	date_from_ydays(dayyear,thetime);
	return 0;
}

/* compute date from the number of days since Jan 1 */
int date_from_ydays(int dayyear, struct tm *thetime)
{
	int i, j;
	int month = 0;
	int day = 0;

	i = (leapyear(0,thetime->tm_year+1900)) ? 0 : 1;
	for (i=i; i < dayyear; ++i)
		switch (i) {
			case 31: ++month; day = i; break;
			case 60: ++month; day = i; break;
			case 91: ++month;	day = i; break;
			case 121: ++month; day = i; break;
			case 152: ++month; day = i; break;
			case 182: ++month; day = i; break;
			case 213: ++month; day = i; break;
			case 244: ++month; day = i; break;
			case 274: ++month; day = i; break;
			case 305: ++month; day = i; break;
			case 335: ++month; day = i; break;
		}
	thetime->tm_mon = month;
	if (leapyear(0,thetime->tm_year+1900))
		day = dayyear - day + 1;
	else
		day = dayyear - day + 2;
	thetime->tm_mday = day;
	return 0;
}

/* ensures that weekday given matches the dates, etc. */
int errorcheck(struct tm *thetime)
{

}

/* calculate day of week */
int dayofweek(int cent, int year, int month, int day)
{
	struct centtab {
		int twocent;
		int firstday;
	} centuries[] = {
		17, 4,
		18, 2,
		19, 0,
		20, 6,
		21, 4,
		22, 2,
		23, 0,
		24, 6,
		25, 4,
		26, 2,
	};
	int theweekday = 0;		/* the answer */
	int thefirstday = 0;		/* the first day of the year */
	int tmp;
	int i;

	if (cent == 0)
		cent = 20;
	for (i=0; centuries[i].twocent != cent; ++i);
	thefirstday = centuries[i].firstday;
	theweekday = (int)year / 4;
	switch (month) {
		case 1:
			if (leapyear(cent,year) == 1)
				theweekday = theweekday + thefirstday + year + 6;
			else
				theweekday = theweekday + thefirstday + year + 0;
			break;
		case 2:
			if (leapyear(cent,year) == 1)
				theweekday = theweekday + thefirstday + year + 3;
			else
				theweekday = theweekday + thefirstday + year + 2;
			break;
		case 3:
			theweekday = theweekday + thefirstday + year + 3; break;
		case 4:
			theweekday = theweekday + thefirstday + year + 6; break;
		case 5:
			theweekday = theweekday + thefirstday + year + 1; break;
		case 6:
			theweekday = theweekday + thefirstday + year + 4; break;
		case 7:
			theweekday = theweekday + thefirstday + year + 6; break;
		case 8:
			theweekday = theweekday + thefirstday + year + 2; break;
		case 9:
			theweekday = theweekday + thefirstday + year + 5; break;
		case 10:
			theweekday = theweekday + thefirstday + year + 0; break;
		case 11:
			theweekday = theweekday + thefirstday + year + 3; break;
		case 12:
			theweekday = theweekday + thefirstday + year + 5; break;
		default:
			fprintf(stderr,"dozdate:  invalid month\n");
			exit(1);
	}
	theweekday += day;
	theweekday %= 7;
	return theweekday;
}

/* determine if it's a leap year; return 1 if yes */
int leapyear(int cent, int year)
{
	cent *= 100;
	year += cent;
	if ((year % 4 == 0) && (year % 100 != 0))
		return 1;
	else if (year % 400 == 0)
		return 1;
	else
		return 0;
}

int printdate(struct tm *thetime)
{
	char *daystring;
	char *monthstring;
	int i;

	for (i=0; i <= 6; ++i)
		if (weekdays[i].num == thetime->tm_wday)
			daystring = weekdays[i].longname;
	for (i=0; i <= 11; ++i)
		if (months[i].num == thetime->tm_mon)
			monthstring = months[i].longname;
	printf("%s, %d %s %d\n",daystring,thetime->tm_mday,monthstring, 
		thetime->tm_year+1900);
}
