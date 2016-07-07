/*
 * +AMDG
 */
/*
 * This document was begun on 5 July 1200, the feast of St.
 * Anthony Mary Zaccaria, C, and it is humbly dedicated to
 * him and to the Immaculate Heart of Mary for their
 * prayers, and to the Sacred Heart of Jesus for His mercy.
 *
 * dozcal:  keeps a calendar with a specific internal format
 * in dozenal
 *
 * (C) Copyright 2016  Donald P. Goodman III
 *
 * This file is part of dozcal.
 *
 * dozcal is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozcal is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozcal.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<regex.h>
#include<errno.h>
#include"conv.h"

#define MAX_ERR_LENGTH 256

char *datepats[] = {
	"\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)"
};
/*	year-/mo-/da
	mo/-da-/year */

/* returns time_t of date; -1 if failed */
time_t proc_date(char *s)
{
	int i; int result; int errornum;
	char err[MAX_ERR_LENGTH+1];
	struct tm *date;
	regmatch_t pmatch[4]; size_t nmatch = 4;
	regex_t regone;
	char holder[5];
	time_t returnval;

	date = calloc(1,sizeof(struct tm));
	for (i = 0; i < 2; ++i) {
		if ((errornum = regcomp(&regone,datepats[i],0)) != 0) {
			regerror(errornum,&regone,err,MAX_ERR_LENGTH);
			return -1;
		}
		result = regexec(&regone,s,4,pmatch,0);
		regfree(&regone);
		if (result == 0) {
			switch (i) {
			case 0:
				sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
					s+pmatch[1].rm_so);
				date->tm_year = (int)doztodec(holder) - 1900;
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				date->tm_mon = (int)doztodec(holder) - 1;
				sprintf(holder,"%.*s",pmatch[3].rm_eo - pmatch[3].rm_so, 
					s+pmatch[3].rm_so);
				date->tm_mday = (int)doztodec(holder);
				break;
			case 1:
				sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
					s+pmatch[1].rm_so);
				date->tm_mon = (int)doztodec(holder) - 1;
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				date->tm_mday = (int)doztodec(holder);
				sprintf(holder,"%.*s",pmatch[3].rm_eo - pmatch[3].rm_so, 
					s+pmatch[3].rm_so);
				date->tm_year = (int)doztodec(holder) - 1900;
				break;
			}
			break;
		}
	}
	if (result != 0) {
		free(date);
		return -1;
	}
/*	printf("YEAR:  %d - ",date->tm_year);
	printf("MON:  %d - ",date->tm_mon);
	printf("MDAY:  %d\n",date->tm_mday);*/
	returnval = mktime(date);
	free(date);
	return returnval;
}

char *timepats[] = {
	"\\([0-9XE][0-9XE]\\):\\([0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\);\\([0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\);\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\)\\([0-9XE][0-9XE]\\)",
};

/* returns number of Tims since midnight, starting at 0 */
/* -1 if error */
int proc_time(char *s)
{
	int i; int result; int errornum;
	char err[MAX_ERR_LENGTH+1];
	regmatch_t pmatch[3]; size_t nmatch = 3;
	regex_t regone;
	char holder[5]; int holdnum;
	const int tims = 20736; /* number of Tims in hr */
	int hours = -1;

	for (i = 0; i < 4; ++i) {
		if ((errornum = regcomp(&regone,timepats[i],0)) != 0) {
			regerror(errornum,&regone,err,MAX_ERR_LENGTH);
			return -1;
		}
		result = regexec(&regone,s,4,pmatch,0);
		regfree(&regone);
		if (result == 0) {
			sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
				s+pmatch[1].rm_so);
			hours = ((int) doztodec(holder) * tims);
			switch (i) {
			case 0:
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				holdnum = atoi(holder);
				if (holdnum == 30) {
					hours += 10368;
				} else if (holdnum == 15) {
					hours += 5184;
				} else if (holdnum == 45) {
					hours += 15552;
				} else {
					hours += (int)(holdnum * 345.6);
				}
				break;
			case 1: case 3:
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				holdnum = (int) doztodec(holder);
				hours += (holdnum * 144);
				break;
			case 2:
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				hours += (int)doztodec(holder);
				break;
			}
			break;
		}
	}
	return hours;
}
