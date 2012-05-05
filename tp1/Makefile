CC=g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/TFloat.o src/bisection.o src/newton.o src/tools.o src/combined.o
MAINS= tp1.o mechanical_energy.o tp_extra.o

.PHONY	: all clean install

all	: clean tp mechanical_energy tp_extra

tp :  $(OBJ) tp1.o
	$(CC) $(CFLAGS) $(OBJ) tp1.o -o tp

mechanical_energy : $(OBJ) mechanical_energy.o
	$(CC) $(CFLAGS) $(OBJ) mechanical_energy.o -o mechanical_energy

tp_extra : $(OBJ) tp_extra.o
	$(CC) $(CFLAGS) $(OBJ) tp_extra.o -o tp_extra

src/TFloat.o : src/TFloat.cpp
	$(CC) $(CFLAGS) -c src/TFloat.cpp -o src/TFloat.o

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ) $(MAINS) tp mechanical_energy tp_extra

clear: clean
