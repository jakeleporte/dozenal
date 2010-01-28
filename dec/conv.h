/* +AMDG */
/*
 * A header file for the conversion routines in the dozenal
 * package.  The basic conversion routines and a couple of
 * utility functions needed by both programs.
 *
 */

#define MAXLINE 1000

int doz(char *s, char *t, int places, int expnot);
double doztodec(char *s);
int dec(char *p, int places, char expnot);
void reverse(char *s);
int getword(char *s, int lim);
int isdozdig(char c);
