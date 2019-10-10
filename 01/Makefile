CC=g++
all: calcul 
calcul: calc.cpp
	$(CC) calc.cpp -o calc --std=c++14 -O2
clean:
	rm -rf calc
run : 
	./calc $(args)
test: 
	python3 ./test.py
