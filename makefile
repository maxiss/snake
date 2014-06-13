all: main

main: main.o snake.o visual.o gamemap.o game.o
	g++ main.o snake.o visual.o gamemap.o game.o -lcurses -o main

main.o: main.cpp snake.h
	g++ -c main.cpp -std=gnu++11

game.o: game.cpp snake.h
	g++ -c game.cpp

gamemap.o: gamemap.cpp snake.h
	g++ -c gamemap.cpp

visual.o: visual.cpp snake.h
	g++ -c visual.cpp

snake.o: snake.cpp snake.h
	g++ -c snake.cpp

clear:
	rm -rf *.o main
