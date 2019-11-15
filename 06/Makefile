CC=g++
all: format
format: main.o
	$(CC) main.o -o format --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o format
test: 
	./format
