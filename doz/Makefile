# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for the decimal to dozenal converter.

doz : main.o dozconv.h dozconv.o doz.o
	gcc -lm -o doz main.o dozconv.o doz.o

main.o : dozconv.h main.c dozconv.o doz.o
	gcc -c main.c

dozconv.o : dozconv.c dozconv.h
	gcc -c dozconv.c

doz.o : dozconv.o dozconv.h doz.c
	gcc -c doz.c
