all: main

main: main.o snake.o
	g++ main.o snake.o -o main

main.o: main.cpp snake.h
	g++ -c main.cpp

snake.o: snake.cpp snake.h
	g++ -c snake.cpp

clear:
	rm -rf *.o main
