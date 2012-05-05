CC=g++
CFLAGS= -Wall -ggdb -I include/
OBJ=
MAINS= tp2.o

.PHONY	: all clean install

all	:clean tp

tp :  $(OBJ) tp2.o
	$(CC) $(CFLAGS) $(OBJ) tp2.o -o tp


src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ) $(MAINS) tp
