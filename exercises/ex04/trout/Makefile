trout.o: trout.h trout.c util.h
	gcc -c trout.c

util.o: util.h util.c
	gcc -c util.c

main.o: util.h trout.h main.c
	gcc -c main.c

trout: trout.o util.o main.o
	gcc -Wall -o trout trout.c util.c main.c