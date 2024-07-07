CC=gcc
CXX=g++

INCLUDE=-Iinclude/

all: 
	$(CC) $(INCLUDE) -c source/swap.c -o build/swap.o