#!/usr/bin/make
# Graphics Library Makefile
# Kyle Sucro kes172

LIB = library
MAIN = driver
GCC = gcc

install:
	$(GCC) -o $(LIB).o -c $(LIB).c
	$(GCC) -o $(MAIN).o -c $(MAIN).c
	$(GCC) -o $(MAIN) $(MAIN).o $(LIB).o

clean:
	rm -f $(LIB).o
	rm -f $(MAIN).o
	rm -f $(MAIN)
