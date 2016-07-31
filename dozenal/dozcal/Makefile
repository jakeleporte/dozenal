# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for dozcal.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
LUALIB = -llua5.2
CC = gcc
LOCALLIBS = event_struct.h errcodes.h
objects = main.o utility.o proc_date.o process_file.o moon.o opt_file.o \
	easter.o nat_holidays.o jewish_date.o islamic.o call_lua.o
binobjects = dozcal

all: bin

dozcal: $(objects) ../doz/doz.o ../dec/dec.o ../conv/conv.o event_struct.h $(LOCALLIBS)
	$(CC) -I$(IDIR) -std=c99 -g -lm -lhdate -o dozcal ../conv/conv.o \
		../doz/doz.o ../dec/dec.o $(objects) $(LUALIB)

main.o: main.c ../conv/conv.o ../doz/doz.o ../dec/dec.o ../conv/conv.o $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c main.c ../dec/dec.c ../conv/conv.c \
		$(LUALIB)

call_lua.o: call_lua.c $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -c call_lua.c -lm $(LUALIB)

moon.o: moon.c ../doz/doz.o $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c moon.c ../doz/doz.c

jewish_date.o: jewish_date.c $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -lhdate -c jewish_date.c

islamic.o: islamic.c $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c islamic.c

nat_holidays.o: nat_holidays.c $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c nat_holidays.c

easter.o: easter.c $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c easter.c

process_file.o: process_file.c utility.c ../conv/conv.o ../doz/doz.o ../dec/dec.o $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c process_file.c utility.c ../dec/dec.c ../conv/conv.c

proc_date.o:  proc_date.c utility.c ../conv/conv.o ../doz/doz.o ../dec/dec.o $(LOCALLIBS)
	$(CC) -I$(IDIR) -g -lm -c proc_date.c utility.c ../dec/dec.c ../conv/conv.c ../doz/doz.c

opt_file.o: opt_file.c utility.c $(LOCALLIBS)
	$(CC) -I$(DIR) -g -lm -c opt_file.c utility.c

utility.o: utility.c $(LOCALLIBS)
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
