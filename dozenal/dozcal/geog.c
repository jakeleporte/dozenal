/*
 * +AMDG
 */
/*
 * This document was begun on 10 Aug 1200, the feast of St.
 * Clare, V, and it is humbly dedicated to her and to the
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

#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include"utility.h"
#include"julday.h"
#include"errcodes.h"
#include"conv.h"

extern double latitude;
extern double longitude;
extern double tzoffset;

double to_degs(char *s, int latlong);
double dodegree(char *s);
double dounciaPis(char *s);

int proc_geog(char *s)
{
	char buffer[SHORTLEN];
	int i = 0;

	if (!strstr(s,"/")) {
		fprintf(stderr,"dozcal:  your geography string must "
			"be formatted with latitude and longitude separated "
			"by \"/\"; your string \"%s\" does not do so\n",s);
		exit(BAD_GEOG_STR);
	}
	for (i = 0; (s[i] != '/') && (i < SHORTLEN); ++i)
		buffer[i] = s[i];
	buffer[i] = '\0';
	latitude = to_degs(buffer,0);
	longitude = to_degs(s+i+1,1);
	return 0;
}

/* latlong is 0 for latitude, 1 for longitude */
double to_degs(char *s, int latlong)
{
	double degs = 0.0;

	if (strstr(s,"o")) {
		degs = dodegree(s);
	} else {
		degs = dounciaPis(s);
	}
	errcheck(s,latlong,degs);
	return degs;
}

double dounciaPis(char *s)
{
	double degs;

	degs = doztodec(s) / 12;
	degs = (degs * 180) / M_PI;
	return degs;
}

double dodegree(char *s)
{
	char bufone[SHORTLEN];
	char buftwo[SHORTLEN];
	char bufthree[SHORTLEN];
	double degs;
	int i; int j = 0;
	double mins, secs;

	if (strlen(s) >= SHORTLEN)
		s[SHORTLEN] = '\0';
	if (strstr(s,"'")) {
		for (i = 0; s[i] != 'o'; ++i)
			bufone[j++] = s[i];
		bufone[j] = '\0';
		j = 0;
		for (i = i + 1; (s[i] != '\'') && (s[i] != '\\'); ++i)
			buftwo[j++] = s[i];
		buftwo[j] = '\0';
		if (!isdozdig(buftwo[0]))
			memmove(buftwo,buftwo+1,strlen(buftwo));
		j = 0;
		for (i = i + 1; (s[i] != '"') && (s[i] != '\\'); ++i)
			bufthree[j++] = s[i];
		bufthree[j] = '\0';
		if (!isdozdig(bufthree[0])) {
			memmove(bufthree,bufthree+1,strlen(bufthree));
		}
		secs = doztodec(bufthree) / 3600;
		mins = doztodec(buftwo) / 60;
		degs = doztodec(bufone) + mins + secs;
	} else if (strstr(s,";")) {
		s[strlen(s)-1] = '\0';
		degs = doztodec(s);
	}
	return degs;
}

/* latlong is 0 for latitude, 1 for longitude */
int errcheck(char *s, int latlong, double degs)
{
	if ((latlong == 0) && ((degs > 90) || (degs < -90))) {
		fprintf(stderr,"dozcal:  invalid latitude argument "
			"\"%s\"",s);
		exit(BAD_LATITUDE);
	} if ((latlong == 1) && ((degs > 180) || (degs < -180))) {
		fprintf(stderr,"dozcal:  invalid latitude argument "
			"\"%s\"",s);
		exit(BAD_LONGITUDE);
	}
	return 0;
}
