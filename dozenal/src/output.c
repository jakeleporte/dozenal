/*
 * +AMDG
 */
/*
 * This document was begun on 1 Aug 1200, the Comm. of the
 * Holy Machabees, MM, and it is humbly dedicated to them
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
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

int send_out(char *s)
{
	if (file_exist(s)) {
		freopen("%s","w",stdout);
	} else {
		fprintf(stderr,"dozcal:  cannot find chosen output pipe "
			"\"%s\" in either the current directory or in "
			"\"$HOME/dozcal/\"; output will still be to "
			"stdout...\n",s);
	}
	return 0;
}
