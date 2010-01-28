# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for the decimal to dozenal converter.

doz : main.o conv.h conv.o doz.o
	gcc -lm -o doz main.o conv.o doz.o

main.o : conv.h main.c conv.o doz.o
	gcc -c main.c

conv.o : conv.c conv.h
	gcc -c conv.c

doz.o : conv.o conv.h doz.c
	gcc -c doz.c
