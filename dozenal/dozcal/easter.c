/*
 * +AMDG
 */
/*
 * This document was begun on E July 1200, the Comm. of St.
 * Pius I, PM, and it is humbly dedicated to him and to the
 * Immaculate Heart of Mary for their prayers, and to the
 * Sacred Heart of Jesus for His mercy.
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

#include<math.h>
#include<time.h>

int date_easter(int year)
{
	int a, b, c, d, e, f, g, h, i, k, l, m, month, day;
	int easterday;
	struct tm *easter;
	time_t eastersecs;

	a = year % 19;
	b = floor(year / 100);
	c = year % 100;
	d = floor(b / 4);
	e = b % 4;
	f = floor((b + 8) / 25);
	g = floor((b - f + 1) / 3);
	h = (19 * a + b - d - g + 15) % 30;
	i = floor(c / 4);
	k = c % 4;
	l = (32 + (2 * e) + (2 * i) - h - k) % 7;
	m = floor((a + (11 * h) + (22 * l)) / 451);
	month = floor((h + l - (7 * m) + 114) / 31);
	day = ((h + l - (7 * m) + 114) % 31) + 1;
	easter->tm_year = year - 1900;
	easter->tm_mon = month - 1;
	easter->tm_mday = day;
	eastersecs = mktime(easter);
	easterday = (eastersecs / 86400);
	return easterday;
}
