CC ?= g++

default:
	$(CC) -std=c++20 -static -O3 main.cpp -o main
	./main