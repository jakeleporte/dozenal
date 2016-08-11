/*
 * +AMDG
 */
/*
 * This document was begun on 5 July 1200, the feast of St.
 * Anthony Mary Zaccaria, C, and it is humbly dedicated to
 * him and to the Immaculate Heart of Mary for their
 * prayers, and to the Sacred Heart of Jesus for His mercy.
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

#define MAXLEN 256
#define SHORTLEN 16
#define MAXLINES 16

#define EXIT_SUCCESS 0
#define OPT_REQ_ARG 1
#define UNREC_OPT 2
#define INSUFF_MEM 3
#define BAD_FILE 4
#define BAD_TIME_FORMAT 5
#define BAD_EV_FORMAT 6
#define BAD_MOON_PHASE 7
#define BAD_CONF_FILE 8
#define BAD_TODO_FORMAT 9
#define BAD_FREQ 10
#define LUA_ERROR 11
#define BAD_FDOW 12
#define BAD_OUT_FILE 13
