CC=g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/TFloat.o src/bisection.o src/newton.o src/tools.o src/combined.o tp1.o

.PHONY	: all clean install

all	: clean tp

tp :  $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tp

src/TFloat.o : src/TFloat.cpp
	$(CC) $(CFLAGS) -c src/TFloat.cpp -o src/TFloat.o

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ) tp
