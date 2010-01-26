/* +AMDG */
/*
 * This document was begun on 15 January 2010, the Feast of
 * St. Paul the Hermit, and it is humbly dedicated to him
 * and to the Immaculate Heart of Mary for their prayers,
 * and to the Sacred Heart of Jesus for His mercy.
 */
/*
 * Basic routines for dozdc; accompanies library dozdc.h.
 */

int isdozdig(char c)
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4': case
	'5': case '6': case '7': case '8': case '9': case 'A':
	case 'a': case 'B': case 'b': case 'X': case 'x': case
	'E': case 'e': case 'T': case 't': case ';':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}
