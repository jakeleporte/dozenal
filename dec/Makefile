# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for the decimal to dozenal converter.

dec : main.o decconv.h decconv.o dec.o
	gcc -lm -o dec main.o decconv.o dec.o

main.o : decconv.h main.c decconv.o dec.o
	gcc -c main.c

decconv.o : decconv.c decconv.h
	gcc -c decconv.c

dec.o : decconv.o decconv.h dec.c
	gcc -c dec.c
