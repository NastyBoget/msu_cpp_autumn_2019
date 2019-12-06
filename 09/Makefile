CC=g++
all: sort_file
sort_file: sort_file.o
	$(CC) sort_file.o -pthread -o sort_file --std=c++14 -O2
sort_file.o: sort_file.cpp
	$(CC) sort_file.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o sort_file out.txt
run: 
	./sort_file
