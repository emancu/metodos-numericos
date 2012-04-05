CC=g++
CFLAGS= -Wall -ggdb
OBJ= TFloat.o tp1.o

.PHONY	: all clean install

all	: clean tp

tp :  $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tp

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJ) tp
