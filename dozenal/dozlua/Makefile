# +AMDG

LUADIR = `pkg-config --cflags lua52`
LUALIB = `pkg-config --libs lua52`

dozlua : main.o conv.h doz.o dec.o conv.o
	gcc -g -llua5.2 -lm -o dozlua main.o conv.o doz.o dec.o

main.o : dec.o conv.o doz.o main.c
	gcc -g -lm -c main.c

#stringconv.o : dec.o conv.o doz.o stringconv.c
#	gcc -g -lm -c stringconv.c

doz.o : conv.c conv.h doz.c
	gcc -lm -std=c99 -g -c doz.c

dec.o : conv.o conv.h dec.c
	gcc -g -c dec.c

conv.o : conv.c conv.h
	gcc -g -c conv.c

prefix = /usr/local
bindir = /usr/local/bin
mandir = /usr/local/share/man/man1

install : dozdc dozdc.1
	cp ./dozdc $(bindir)
	cp ./gdozdc $(bindir)
	cp ./dozdc.1 $(mandir)
	cp ./gdozdc.1 $(mandir)

uninstall :
	rm $(bindir)/dozdc
	rm $(bindir)/gdozdc
	rm $(mandir)/dozdc.1
	rm $(mandir)/gdozdc.1
