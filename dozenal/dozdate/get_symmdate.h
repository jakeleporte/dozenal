/* + AMDG */
/*
 * This document was begun on 16 Aug 1201, the feast of St.
 * Agapitus, M, and it is humbly dedicated to him and to the
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

long get_judate(struct tm *thetime);
long symnewyear(int symyear);
long symmtofixed(struct tm *thetime);
int symm_errcheck(struct tm *thetime);
int symmtoweekday(long judate, int firstday, struct tm *thetime);
int getgregdate(long judate, struct tm *thetime);
long symmtofixed(struct tm *thetime);
long get_judate(struct tm *thetime);
long symnewyear(int symyear);
int fixed_to_symyear(long judate,long *firstday);
int issymleapyear(int symyear);
int daysbfmonth(int symmonth);
int convtosym(struct tm *thetime, long judate, int symyear, int firstday);
int get_symmdate(struct tm *thetime,int *usesymm);
