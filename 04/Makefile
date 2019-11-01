CC=g++
all: bigint
bigint: main.o bigint.o
	$(CC) main.o bigint.o -o bigint --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
bigint.o: bigint.cpp bigint.h
	$(CC) bigint.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o bigint
test: 
	valgrind ./bigint
