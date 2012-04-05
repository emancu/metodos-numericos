CC=g++
CFLAGS= -Wall -ggdb
OBJ= TFloat.o tp1.o

.PHONY	: all clean install

all	: clean tp

tp :  $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tp

TFloat.o : TFloat.cpp
	$(CC) $(CFLAGS) -c TFloat.cpp -o TFloat.o

tp1.o : tp1.c
	$(CC) $(CFLAGS) -c tp1.c -o tp1.o


clean :
	rm -rf $(OBJ) tp
