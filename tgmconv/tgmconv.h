/* +AMDG */
/*
 * This document was begun on 18 Jan 2010, the commemoration
 * of St. Prisca, virgin and martyr; and it is humbly
 * dedicated to her and to the Immaculate Heart of Mary for
 * their prayers, and to the Sacred Heart of Jesus, for His
 * mercy.
 */
/*
 * The library routines, especially the main structures, for
 * the dozenal measurement conversion program.
 */

/* once we've got the units and the value, converts it,
 * returns the answer as double */
double getanswer(char *to, char *from, double value);
/* converts unit abbrevs to full names, returns factors */
double getunits(char *s);
/* convert TGM values, returns factors */
double gettgm(char *s);
/* determines if c is an SI prefix */
int ismetprefix(char c);
/* determines appropriate metric factor, like gettgm() */
double getmetric(char *s);
/* gets factors from each side of slash */
double getslash(char *s);
