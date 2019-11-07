CC=g++
all: serializer
serializer: serializer.o deserializer.o main.o
	$(CC) main.o serializer.o deserializer.o -o serializer --std=c++14 -O2
main.o: main.cpp
	$(CC) main.cpp -c --std=c++14 -O2
serializer.o: serializer.cpp serializer.h
	$(CC) serializer.cpp -c --std=c++14 -O2
deserializer.o: deserializer.cpp deserializer.h
	$(CC) deserializer.cpp -c --std=c++14 -O2
clean:
	rm -rf *.o serializer
test: 
	./serializer
