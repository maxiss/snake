all: main

main: main.o snake.o visual.o
	g++ main.o snake.o visual.o -lcurses -o main

main.o: main.cpp snake.h
	g++ -c main.cpp

snake: snake.cpp visual.cpp snake.h
	g++ -c snake.cpp visual.cpp

clear:
	rm -rf *.o main
