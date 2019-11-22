CC=g++
all: vector
vector: main.o
	$(CC) main.o -o vector --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o vector
test: 
	valgrind ./vector
