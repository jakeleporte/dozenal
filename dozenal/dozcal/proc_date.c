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
#include"conv.h"

#define MAX_ERR_LENGTH 256

char *datepats[] = {
	"\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)"
};
/*	year-/mo-/da
	mo/-da-/year */

time_t proc_date(char *s)
{
	int i; int result; int errornum;
	char err[MAX_ERR_LENGTH+1];
	struct tm *date;
	regmatch_t pmatch[4]; size_t nmatch = 4;
	regex_t regone;
	char holder[5];

	for (i = 0; i < 2; ++i) {
		if ((errornum = regcomp(&regone,datepats[i],0)) != 0) {
			regerror(errornum,&regone,err,MAX_ERR_LENGTH);
			return -1;
		}
		result = regexec(&regone,s,4,pmatch,0);
		if (result == 0) {
			printf("Hurray!  |%s|\n",s);
			sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
				s+pmatch[1].rm_so);
			printf("|doz%s| = |dec%.0f|\n",holder, doztodec(holder));
			break;
		} else {
			printf("D'oh!  |%s|\n",s);
		}
	}
	regfree(&regone);
}
