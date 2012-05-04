CC=g++
CFLAGS= -Wall -ggdb -I include/ `pkg-config --cflags --libs opencv`
OBJ=
MAINS= tp2.o tp2a.o

.PHONY	: all clean install

all	:clean tp tp2

tp :  $(OBJ) tp2.o
	$(CC) $(CFLAGS) $(OBJ) tp2.o -o tp

tp2 :  $(OBJ) tp2a.o
	$(CC) $(CFLAGS) $(OBJ) tp2a.o -o tp2

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ) $(MAINS) tp
