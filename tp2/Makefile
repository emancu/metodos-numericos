CC= g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/tools.o src/matrix.o
MAINS= tp2.o

.PHONY: all clean install

all: clean tp

tp: $(OBJ) tp2.o
	$(CC) $(CFLAGS) $(OBJ) tp2.o -o tp

tp2.o: $(OBJ)
	$(CC) $(CFLAGS) -c -o tp2.o tp2.cpp

src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(MAINS) tp

clear: clean
