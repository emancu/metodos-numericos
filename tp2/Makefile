CC= g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/tools.o src/matrix.o
MAINS= tp2.o generateNoise.o

.PHONY: all clean install

all: clean tp generateNoise

tp: $(OBJ) tp2.o
	$(CC) $(CFLAGS) $(OBJ) tp2.o -o tp

generateNoise: $(OBJ) generateNoise.o
	$(CC) $(CFLAGS) $(OBJ) generateNoise.o -o generateNoise

generateNoise.o: $(OBJ)
	$(CC) $(CFLAGS) -c -o generateNoise.o generateNoise.cpp

tp2.o: $(OBJ)
	$(CC) $(CFLAGS) -c -o tp2.o tp2.cpp

src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(MAINS) tp generateNoise

clear: clean
