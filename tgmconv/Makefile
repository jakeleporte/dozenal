# +AMDG

tgmconv : main.o doz.o dec.o tgm.o conv.h tgmconv.h
	gcc -g -lm -o tgmconv main.o tgm.o doz.o dec.o conv.o

main.o : main.c tgmconv.h dec.o doz.o conv.h conv.c
	gcc -g -c main.c

tgm.o : tgm.c tgmconv.h
	gcc -g -c tgm.c

doz.o : doz.c conv.h conv.c
	gcc -g -c doz.c

dec.o : dec.c conv.h conv.c
	gcc -g -c dec.c

conv.o : conv.c conv.h
	gcc -g -c conv.c
