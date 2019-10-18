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

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include<time.h>

char *front_chomp(char *s);
struct tm *broken_date(int daynum);
int lower_str(char *s);
int upper_str(char *s);
int dozendig(char c);
int get_impstr(char *s);
int add_event(int starttime, int endtime, int thisdate,
	char *title, char *class, char *categories, char
	*location, char transp, char *attendees, char *url);
int add_todo(int duedate,int starttime,int priority,
	int compflag, int pergross, char *title, char *class,
	char *categories, char *location, char *url);
int file_exist(char *s);
int add_to_event(char *title, int datenum, char *cat);
int first_dow(char *s);
int mkdaynum(time_t datenum);
int get_weekday(int datenum);
int chomp(char *s);
int get_datenum(struct tm *date);
int not_in(int date, int exceptions[], int len);
int first_of_next(struct tm *date);
int last_wday_of_month(int datenum, int wday);
int wday_of_month(int datenum, int wday, int num);
int countchars(char *s, char c);
int __sunriset__( int year, int month, int day, double lon, double lat,
                  double altit, int upper_limb, double *rise, double *set );
int addto_str(char **s, char *t);
int init_str(char **s);
