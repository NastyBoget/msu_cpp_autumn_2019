CC=g++
all: threadpool
threadpool: main.o thread_pool.o
	$(CC) main.o thread_pool.o -pthread -o threadpool --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
thread_pool.o: thread_pool.cpp
	$(CC) thread_pool.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o threadpool
test: 
	./threadpool
