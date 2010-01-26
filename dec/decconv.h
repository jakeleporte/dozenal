/* +AMDG */
/*
 * A header file for the conversion routines in the dozenal
 * package.  The basic conversion routines and a couple of
 * utility functions needed by both programs.
 *
 */

#define MAXLINE 1000

int doz(char *s, char *t, int places, int expnot);
int dec(char *p, int places, char expnot);
int getword(char *s, int lim);
