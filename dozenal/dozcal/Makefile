# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for the decimal to dozenal converter.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
CC = gcc
objects = main.o utility.o proc_date.o
binobjects = dozcal

all: bin

dozcal: $(objects) ../doz/doz.o ../dec/dec.o ../conv/conv.o
	$(CC) -I$(IDIR) -std=c99 -g -lm -o dozcal ../conv/conv.o \
		../doz/doz.o ../dec/dec.o $(objects)

main.o: main.c ../conv/conv.o ../doz/doz.o 
	$(CC) -I$(IDIR) -g -lm -c main.c 

proc_date.o:  proc_date.c utility.c ../conv/conv.o ../doz/doz.o ../dec/dec.o
	$(CC) -I$(IDIR) -g -lm -c proc_date.c utility.c

#process_file.o: process_file.c utility.c ../conv/conv.o ../doz/doz.o ../dec/dec.o
#	$(CC) -I$(IDIR) -g -lm -c process_file.c utility.c

utility.o: utility.c
	$(CC) -I$(IDIR) -g -lm -c utility.c

../doz/doz.o: ../conv/conv.o ../doz/doz.c
	$(MAKE) -C ../doz

../dec/dec.o: ../conv/conv.o ../dec/dec.c
	$(MAKE) -C ../dec

../conv/conv.o: ../conv/conv.c $(IDIR)/conv.h
	$(MAKE) -C ../conv

bin: $(binobjects)

installbin: $(binobjects)
	for obj in $(binobjects) ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) conv.o ; do \
		rm -f $${obj} ; done

.PHONY: bin clean installbin install uninstall
