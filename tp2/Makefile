CC= g++
CFLAGS= -Wall -ggdb -I include/
OBJ= src/tools.o src/matrix.o
MAINS= tp2.o generateNoise.o psnr.o
BIN= tp generateNoise psnr

.PHONY: all clean install

all: clean tp generateNoise psnr

tp: $(OBJ) tp2.o
	$(CC) $(CFLAGS) $(OBJ) tp2.o -o tp

generateNoise: $(OBJ) generateNoise.o
	$(CC) $(CFLAGS) $(OBJ) generateNoise.o -o generateNoise

psnr: $(OBJ) psnr.o
	$(CC) $(CFLAGS) $(OBJ) psnr.o -o psnr



src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(MAINS) $(BIN)

clear: clean
