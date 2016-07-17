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
#include<math.h>
#include<limits.h>
#include<errno.h>
#include<string.h>
#include"conv.h"
#include"errcodes.h"

#define MAX_ERR_LENGTH 256

char *datepats[] = {
	"\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE]\\)[-/]\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)",
	"\\([0-9XE][0-9XE]\\)[ ]*\\([A-Za-z][A-Za-z]*\\)[ ]*\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)",
	"\\([A-Za-z][A-Za-z]*\\)[ ]*\\([0-9XE][0-9XE]\\),[ ]*\\([0-9XE][0-9XE][0-9XE][0-9XE]\\)"
};
/*	year-/mo-/da
	mo/-da-/year
	da[]mon[]year
	mon[]da,[]year
*/

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
	for (i = 0; i < 4; ++i) {
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
			case 2:
				sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
					s+pmatch[1].rm_so);
				date->tm_mday = (int)doztodec(holder);
				sprintf(holder,"%.*s",pmatch[2].rm_eo - pmatch[2].rm_so, 
					s+pmatch[2].rm_so);
				date->tm_mon = month_string(holder);
				sprintf(holder,"%.*s",pmatch[3].rm_eo - pmatch[3].rm_so, 
					s+pmatch[3].rm_so);
				date->tm_year = (int)doztodec(holder) - 1900;
				break;
			case 3:
				sprintf(holder,"%.*s",pmatch[1].rm_eo - pmatch[1].rm_so, 
					s+pmatch[1].rm_so);
				date->tm_mon = month_string(holder);
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

int num_to_date(int datenum, char *datestr, char *dateform)
{
	time_t unixdate;
	struct tm *broken;
	int i; int j; int k; char holder[6];
	char buffer[256];
	char doznum[6]; char formdoz[6];
	int diff;
	const char *padding="000000000000000000000000000";
	int padlen;

	datestr[0] = '\0';
	unixdate = datenum * 86400;
	broken = localtime(&unixdate);
	strftime(buffer,255,dateform,broken);
	for (i = 0; buffer[i] != '\0'; ++i) {
		j = 0; k = 0;
		if (isdigit(buffer[i])) {
			while ((buffer[i] != '\0') && (isdigit(buffer[i])) && (j < 6))
				holder[j++] = buffer[i++];
			holder[j] = '\0';
			dectodoz(doznum,(double)atoi(holder));
			padlen = strlen(holder) - strlen(doznum);
			sprintf(formdoz,"%*.*s%s",padlen,padlen,padding,doznum);
			strcat(datestr,formdoz);
			--i;
		} else {
			datestr[strlen(datestr)+1] = '\0';
			datestr[strlen(datestr)] = buffer[i];
		}
	}
	return 0;
}

int secs_to_Tims(int time,char *timestr,char *time_format)
{
	int i; int j; int k;
	const int tims = 20736; /* number of Tims in hr */
	char hours[3]; char timpart[5];
	char holder[5]; int len = -1;
	char buffer[256];
	const char *padding="000000000000000000000000000";
	int padlen;

	if (time < 0)
		return -1;
	dectodoz(timestr,(double)time);
	sprintf(buffer,"%*s",6,timestr);
	for (i = 0; buffer[i] != '\0'; ++i) {
		if (buffer[i] == ' ')
			buffer[i] = '0';
	}
	j = 0; k = 0;
	for (i = 0; buffer[i] != '\0'; ++i) {
		if (i < 2)
			hours[j++] = buffer[i];
		else
			timpart[k++] = buffer[i];
	}
	hours[j] = '\0'; timpart[k] = '\0'; timestr[0] = '\0';
	for (i = 0; (i < 256) && (time_format[i] != '\0'); ++i) {
		j = 0; k = 0; len = -1; holder[0] = '\0'; buffer[0] = '\0';
		if (time_format[i] == '%') {
			while (dozendig(time_format[++i]) && (time_format[i] != '\0')) {
				holder[j++] = time_format[i];
			}
			holder[j] = '\0';
			if (holder[0] != '\0') {
				len = (int)doztodec(holder);
			}
			if (time_format[i] == 'h') {
				sprintf(buffer,"%*.*s",len,len,hours);
				strcat(timestr,buffer);
			} else if (time_format[i] == 'b') {
				sprintf(buffer,"%*.*s",len,len,timpart);
				strcat(timestr,buffer);
			} else {
				fprintf(stderr,"dozcal:  unknown conversion "
					"character \"%%%c\" in time format string, "
					"\"%s\"\n",time_format[i],time_format);
				exit(BAD_TIME_FORMAT);
			}
		} else {
			timestr[strlen(timestr)+1] = '\0';
			timestr[strlen(timestr)] = time_format[i];
		}
	}
	return 0;
}

int month_string(char *s)
{
	lower_str(s);
	if (strstr(s,"jan"))
		return 0;
	else if (strstr(s,"feb"))
		return 1;
	else if (strstr(s,"mar"))
		return 2;
	else if (strstr(s,"apr"))
		return 3;
	else if (strstr(s,"may"))
		return 4;
	else if (strstr(s,"jun"))
		return 5;
	else if (strstr(s,"jul"))
		return 6;
	else if (strstr(s,"aug"))
		return 7;
	else if (strstr(s,"sep"))
		return 8;
	else if (strstr(s,"oct"))
		return 9;
	else if (strstr(s,"nov"))
		return 10;
	else if (strstr(s,"dec"))
		return 11;
	else
		return -1;
}
