# +AMDG
# This document was begun on 15 January 2010, the feast of
# St. Paul the Hermit, and it is humbly dedicated to him and
# to the Immaculate Heart of Mary for their prayers, and to
# the Sacred Heart of Jesus for His mercy.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
XFORMS_FLAGS =-DXFORMS
CC = tcc
GCCFLAGS = -Wall -std=c99 -pedantic
objects = main.o getop.o vars.o stack.o shunt.o xdozbc.o dozbc.o
binobjects = dozdc gdozdc
ifeq ($(XFORMS_FLAGS),-DXFORMS)
	XFORM_OBJS = shunt.o dozbc.o xdozbc.o
	XFORM_LIBS = -lforms -lX11
else
	XFORM_OBJS = 
	XFORM_LIBS = 
endif

all: bin

dozdc : main.o ../dec/dec.o $(IDIR)/dozdc.h getop.o stack.o vars.o \
	$(XFORM_OBJS)
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -o dozdc main.o \
		../conv/conv.o ../doz/doz.o ../dec/dec.o getop.o stack.o \
		vars.o $(XFORM_OBJS) $(XFORM_LIBS) -lm

main.o : main.c ../dec/dec.o $(IDIR)/dozdc.h stack.o vars.o
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -c main.c

xdozbc.o : dozbc.o dozbc.h xdozbc.c shunt.c
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -c xdozbc.c

dozbc.o : dozbc.c dozbc.h
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(DIR) -g -c dozbc.c

shunt.o : shunt.c
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(DIR) -g -c shunt.c

getop.o : getop.c ../conv/conv.o ../doz/doz.o ../dec/dec.o \
		$(IDIR)/dozdc.h stack.o vars.o
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -c getop.c

../doz/doz.o: ../conv/conv.o ../doz/doz.c
	$(MAKE) -C ../doz

../dec/dec.o: ../conv/conv.o ../dec/dec.c
	$(MAKE) -C ../dec

../conv/conv.o: ../conv/conv.c $(IDIR)/conv.h
	$(MAKE) -C ../conv

vars.o : vars.c $(IDIR)/vars.h stack.o
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -c vars.c

stack.o : stack.c $(IDIR)/stack.h
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) -I$(IDIR) -g -c stack.c

gdozdc : gdozdc.pl
	cp gdozdc.pl gdozdc

bin: $(binobjects)

installbin: $(binobjects)
	for obj in $(binobjects) ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) ; do \
		rm -f $${obj} ; done

.PHONY: bin clean install installbin uninstall
