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

#include<string.h>

int chomp(char *s)
{
	int i; int j = 0;

	for (i = strlen(s) - 1; i != 0; --i) {
		if (isspace(s[i])) {
			s[i] = '\0';
			++j;
		} else {
			break;
		}
	}
	return j;
}

char *front_chomp(char *s)
{
	int i; int j = 0;
	char *t;

	t = s;
	for (i = 0; isspace(s[i]) && s[i] != '\0'; ++i) {
			++t;
	}
	return t;
}

/* checks if variable is in array; if not, return 0, else 1 */
int not_in(int date, int exceptions[], int len)
{
	int i; int j;

	for (i = 0; i <= len; ++i) {
		if (date == exceptions[i])
			return 1;
	}
	return 0;
}

int get_impstr(char *s)
{
	char *t;

	t = strchr(s,':') + 1;
	t = front_chomp(t);
	return t-s;
}
