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
#include "error_codes.h"

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

	parse_for_weekday(s,thetime);
	monpointer = parse_for_month(s,thetime);
	if (monpointer != NULL)
		parse_for_date(s,monpointer,thetime);
	parse_for_year(s,thetime);
	thetime->tm_yday = ydays_from_date(thetime);
	errorcheck(s,thetime);
	return 0;
}

/* calculate ydays from the date; return ydays; redundant,
 * but harmless, the relative date options were used */
int ydays_from_date(struct tm *thetime)
{
	int i;
	int ydays = 0;

	switch (thetime->tm_mon) {
	case 0:  ydays += 0; break;
	case 1:  ydays += 30; break;
	case 2:  ydays += 59; break;
	case 3:  ydays += 90; break;
	case 4:  ydays += 120; break;
	case 5:  ydays += 151; break;
	case 6:  ydays += 181; break;
	case 7:  ydays += 212; break;
	case 8:  ydays += 243; break;
	case 9:  ydays += 273; break;
	case 10:  ydays += 304; break;
	case 11:  ydays += 334; break;
	default:
		fprintf(stderr, "dozdate:  error:  %d is an invalid "
		"month",thetime->tm_mon);
		exit(BAD_MONTH);
		break;
	}
	if (leapyear(0,thetime->tm_year+1900) && thetime->tm_mon >= 1)
		++ydays;
	return ydays + thetime->tm_mday - 1;
}

/* ensures that weekday given matches the dates, etc. */
int errorcheck(char *s, struct tm *thetime)
{
	char *weekday, *oweekday;
	char *month;
	char number[SIZE];
	int i;

	/* fill some useful variables for error-checking */
	for (i=0; thetime->tm_wday != weekdays[i].num; ++i);
	weekday = weekdays[i].longname;
	oweekday = weekdays[dayofweek(thetime->tm_year+1900,
		thetime->tm_mon+1,thetime->tm_mday)].longname;
	for (i=0; thetime->tm_mon != months[i].num; ++i);
	month = months[i].longname;
	/* check for mday error */
	if ((thetime->tm_mon == 0 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 1 && thetime->tm_mday > 29) ||
	(thetime->tm_mon == 2 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 3 && thetime->tm_mday > 30) ||
	(thetime->tm_mon == 4 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 5 && thetime->tm_mday > 30) ||
	(thetime->tm_mon == 6 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 7 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 8 && thetime->tm_mday > 30) ||
	(thetime->tm_mon == 9 && thetime->tm_mday > 31) ||
	(thetime->tm_mon == 10 && thetime->tm_mday > 30) ||
	(thetime->tm_mon == 11 && thetime->tm_mday > 31)) {
		dectodoz(number,(double)thetime->tm_mday);
		fprintf(stderr,"dozdate:  error:  %s does not have "
		"%s days\n",month,number);
		exit(BAD_MDAY);
	} else if ((thetime->tm_mon == 1) && (thetime->tm_mday == 29)) {
		if (!leapyear(0,thetime->tm_year+1900)) {
			dectodoz(number,(double)thetime->tm_year+1900);
			fprintf(stderr,"dozdate:  error:  %s is not a "
			"leap year\n",number);
			exit(BAD_LEAP_YEAR);
		}
	}
	/* check for weekday error; fix if necessary */
	if (thetime->tm_wday != dayofweek(thetime->tm_year+1900,
	thetime->tm_mon+1,thetime->tm_mday)) {
		if (strstr(s,"Sun") || strstr(s,"Mon") ||
		strstr(s,"Tue") || strstr(s,"Wed") || strstr(s,"Thu")
		|| strstr(s,"Fri") || strstr(s,"Sat"))
			fprintf(stderr,"dozdate:  weekday \"%s\" does not "
			"match the date \"%d %s %d\";\nsetting to the correct "
			"weekday, \"%s\"\n",weekday,thetime->tm_mday,
			month,thetime->tm_year+1900,oweekday);
		thetime->tm_wday = dayofweek(thetime->tm_year+1900,
			thetime->tm_mon+1,thetime->tm_mday);
	}
}

/* find a four-digit number; if doesn't start with ;,
 * assume it's the year, even if leading zeroes */
int parse_for_year(char *s, struct tm *thetime)
{
	int i, j;
	char yearnum[SIZE] = "";
	int year = 0;
	size_t len;

	len = strlen(s);
	for (i=0; s[i] != '\0'; ++i) {
		j=0;
		yearnum[j++] = (i > 0) ? s[i-1] : '0';
		while ((isdigit(s[i]) || s[i]=='X' || s[i] == 'E') && i <= len) {
			yearnum[j++] = s[i++];
		}
		yearnum[j] = '\0';
		if ((j == 5) && (yearnum[0] != ';')) {
			memmove(yearnum,yearnum+1,5);
			year = (int)doztodec(yearnum);
		} else {
			yearnum[0] = '\0';
		}
	}
	if (year != 0)
		thetime->tm_year = year - 1900;
	return 0;
}

/* tries to parse date from position of alphabetical month; 
 * scans backward for date, then forward; if not found, make 
 * date 1 */
int parse_for_date(char *s, char *monthpoint, struct tm *thetime)
{
	char *pt, *pt2;
	char daynum[SIZE] = "NULL";
	int i = 0;
	int date = 0;

	pt = monthpoint;
	pt2 = &s[strlen(s)];
	while (pt >= s) { 				/* do date month year notation */
		if (isdigit(*pt) || (*pt == 'X') || (*pt == 'E'))
			daynum[i++] = *pt;
		--pt;
	}
	daynum[i] = '\0';
	if (daynum[0] != '\0') {
		for (i=0; daynum[i] == '0' && daynum[i] != '\0'; ++i);
		reverse(daynum+i);
		date = (int)doztodec(daynum+i);
	} else {                       /* do Amer comma notation */
		pt = monthpoint;
		while (pt <= pt2) {
			if (*pt == ',') {
				i = 0; --pt;
				while ((isspace(*pt) || *pt == 'X' || *pt == 'E' 
				|| isdigit(*pt)) && pt > s) {
					if (!isspace(*pt)) {
						daynum[i++] = *pt;
						daynum[i] = '\0';
					} 
					--pt;
				} 
				break;
			}
			++pt; 
		}
		reverse(daynum);
		if (daynum[0] != '\0')
			date = (int)doztodec(daynum);
		if (date == 0)
			date = 1;
	}
	/* error checking for date numbers per month */
	thetime->tm_mday = date;
	return 0;
}

/* parses date string for alphabetic months, short of long;
 * if found, loads month into thetime and returns pointer to
 * month; else, calls appropriate functions and returns NULL */
char *parse_for_month(char *s, struct tm *thetime)
{
	int i;
	char *monthpoint = NULL;

	for (i=0; i <= 11; ++i) {
		if ((monthpoint = strstr(s,months[i].longname)) || 
		(monthpoint = strstr(s,months[i].shortname))) {
			thetime->tm_mon = months[i].num;
			break;
		}
	}
	if (monthpoint != NULL) {
		return monthpoint;
	} else { /* must be a numeric month */
		parse_numeric_month(s,thetime);
		return NULL;
	}
}

/* looks for numeric dates, in hyphen or slash format; loads
 * parts into thetime if found */
int parse_numeric_month(char *s, struct tm *thetime)
{
	char monthnum[SIZE] = "";
	char daynum[SIZE] = "";
	char tmp[SIZE] = "";
	int i, j, flag;

	flag = j = 0; /* FIXME:  get date from hyphens, too */
	for (i=0; s[i] != '\0'; ++i) { /* test for hyphen notation */
		if (s[i] == '-') {
			flag = (flag == 0) ? 1 : 0;
			j = 0;
		}
		if (flag == 1 && (isdigit(s[i]) || s[i]=='X' || s[i]=='E')) {
			monthnum[j++] = s[i];
			monthnum[j] = '\0';
		}
		if (flag == 0 && (isdigit(s[i]) || s[i]=='X' || s[i]=='E')) {
			daynum[j++] = s[i];
			daynum[j] = '\0';
		}
	}
	monthnum[j] == '\0';
	if (monthnum[0] == '\0') { /* test for Amer slash notation */
		for (i=strlen(s); i >= 0; --i) {
			if (s[i] == '/') {
				flag = (flag == 0) ? 1 : 0;
				j = 0;
			}
			if (flag == 1 && (isdigit(s[i]) || s[i]=='X' || s[i]=='E')) {
				daynum[j++] = s[i];
				daynum[j] = '\0';
			}
			if (flag == 0 && (isdigit(s[i]) || s[i]=='X' || s[i]=='E')) {
				monthnum[j++] = s[i];
				monthnum[j] = '\0';
			}
		}
		reverse(monthnum); reverse(daynum);
	}
	if (monthnum[0] != '\0') {
		thetime->tm_mon = (int)doztodec(monthnum) - 1;
	}
	if (daynum[0] != '\0') {
		thetime->tm_mday = (int)doztodec(daynum);
	}
	return 0;
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

/* calculate day of week */
int dayofweek(int year, int month, int day)
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
	int tmp, cent;
	int i;

	cent = (int)year / 100;
	year = year - (cent * 100);
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
				theweekday = theweekday + thefirstday + year + 2;
			else
				theweekday = theweekday + thefirstday + year + 3;
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
			fprintf(stderr,"dozdate:  error:  invalid month\n");
			exit(BAD_MONTH);
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
