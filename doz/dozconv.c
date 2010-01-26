/* +AMDG */
/*
 * This file was begun on 13 January 2009, the commemoration
 * of the Baptism of Our Lord, and it is humbly dedicated to
 * the Immaculate Heart of Mary for her prayers, and to the
 * Sacred Heart of Jesus for His mercy.
 */
/*
 * Contains the code for some basic routines for conversion
 * of dozenal numbers to decimal and vice-versa.  Part of
 * the dozenal package.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *s)
{
	int i, j;
	char tmp;
	size_t length;

	length = strlen(s) - 1;
	for (i=0, j=length; i<j; ++i, --j) {
		tmp = *(s+i);
		*(s+i) = *(s+j);
		*(s+j) = tmp;
	}
}

int getword(char *s, int lim)
{
	int c, i;

	--lim;
	for (i=0; (c=getchar())!=EOF && c!='\n' && c!='\t' && c!=' '; ++i) {
		if (i < lim-1)
			*(s+i) = c;
		else if (i == lim)
			*(s+i) = '\0';
	}
	if (c == EOF)
		return EOF;
	if (i < lim)
		*(s+i) = '\0';
	return i;
}
