scene.o: scene.cpp scene.h
	g++ -g -Wall -c scene.cpp -o scene.o
engine.o: engine.cpp engine.h
	g++ -g -Wall -c engine.cpp -o engine.o -lSDL2 -lSDL2_image
main: main.cpp scene.o
	g++ -g -Wall main.cpp scene.o engine.o -o main -lSDL2 -lSDL2_image
