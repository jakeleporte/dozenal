/*
 * +AMDG
 * This document was begun on 17 Aug 11E8, the feast of St.
 * John Eudes, and it is humbly dedicated to him to the
 * Immaculate Heart of Mary, for their prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 *
*/
/*
 * Gets Julian date and converts to Symm676.
 *
 * (C) Copyright 2012  Donald P. Goodman III
 *
 * This file is part of dozdate.
 *
 * dozdate is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozdate is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozdate.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "conv.h"
#include "error_codes.h"

int main()
{
	struct tm *thetime;
	time_t curtime;
	curtime = time(NULL);
	thetime = localtime(&curtime);

	printf("%d\n",get_judate(thetime));
	return 0;
}

/* get the julian day */
int get_judate(struct tm *thetime)
{
	int a,y,m,judate;
	a = (int)((14 - (thetime->tm_mon+1)) / 12);
	y = (1900 + thetime->tm_year) + 4800 - a;
	m = (thetime->tm_mon+1) + (12 * a) - 3;
	judate = thetime->tm_mday + (int)((153 * m + 2) / 5) +
	(365 * y) + (int)(y / 4) - (int)(y / 100) + (int)(y / 400) - 32045;
	printf("a = %d\n",a);
	printf("y = %d\n",y);
	printf("m = %d\n",m);
	printf("judate = %d\n",judate);

	return judate;
}
