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

int call_lua(char *s);
int astron(char *s, int startdate, int enddate);
int proc_options(char *s, int *moonphases, char **nat, char **relig,
					char **date_form, char **time_form, char **ev_form,
					char **todo_form, int *iftodo, int *ifevent,
					int *weekout, int *fdow, char **astro);
int process_file(char *s);
int proc_geog(char *s);
int clear_events();
int clear_todos();
int fill_todo(char *s, int index, char *date_format, char
	*time_format,FILE *outfile);
int fill_event(char *s, int index, char *date_format, char
	*time_format, FILE *outfile);
