CC=g++
all: matrix
matrix: test.o matrix.o
	$(CC) test.o matrix.o -o matrix --std=c++14 -O2
test.o: test.cpp
	$(CC) test.cpp -c --std=c++14 -O2
matrix.o: matrix.cpp matrix.h
	$(CC) matrix.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o matrix
test: 
	valgrind ./matrix
