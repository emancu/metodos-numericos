CC= g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/tools.o src/matrix.o src/building.o
MAINS= tp3.o
BIN= tp

.PHONY: all clean install

all: clean tp

tp: $(OBJ) tp3.o
	$(CC) $(CFLAGS) $(OBJ) tp3.o -o tp

src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(MAINS) $(BIN) random_buildings

random_buildings:
	$(CC) $(CFLAGS) -o random_building random_building.cpp

clear: clean
