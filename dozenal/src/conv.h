/* +AMDG */
/*
 * A header file for the conversion routines in the dozenal
 * package.  The basic conversion routines and a couple of
 * utility functions needed by both programs.
 *
 * (C) Copyright 2010, 2011  Donald P. Goodman III
 *
 * This file is part of dec.
 *
 * dec is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dec is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dec.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#define MAXLINE 1000

int doz(char *s, char *t, int places, int expnot, int new);
int expnotate(char *s);
int posexp(char *s, int zenspot);
int negexp(char *s, int zenspot);
int dozprecis(char *s);
char dozenify(char num);
int dectodoz(char *doznum, double decnum);

int dec(char *p, int places, char expnot);
int decprecis(char *s);
int expkill (char *s, int expspot);
int errorclear(char *s);
double doztodec(char *s);
double wholedec(char *s);
double fracdec(char *s);
int decmify(char c);

void reverse(char *s);
int getword(char *s, int lim);
int isdozdig(char c);
