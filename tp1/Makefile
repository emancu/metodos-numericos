CC=g++
CFLAGS= -Wall -ggdb
OBJ= tp1.o

.PHONY	: all clean install

all	: clean tp

tp :  $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tp

tp1.o : tp1.c
	$(CC) $(CFLAGS) -c tp1.c -o tp1.o

clean :
	rm -rf $(OBJ) tp
