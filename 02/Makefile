CC=g++
all: test_linear_alloc 
test_linear_alloc: main.o linear_allocator.o
	$(CC) main.o linear_allocator.o -o test_linear_alloc --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
linear_allocator.o: linear_allocator.cpp linear_allocator.h
	$(CC) linear_allocator.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o test_linear_alloc
test: 
	valgrind ./test_linear_alloc
