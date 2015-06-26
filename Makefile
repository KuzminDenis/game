scene.o: scene.cpp scene.h
	g++ -g -Wall -c scene.cpp -o scene.o
engine.o: engine.cpp engine.h
	g++ -g -Wall -c engine.cpp -o engine.o -lSDL2 -lSDL2_image
main: main.cpp scene.o engine.o
	g++ -g -Wall main.cpp scene.o engine.o -o main -lSDL2 -lSDL2_image

server_engine: server_engine.cpp server_engine.h
	g++ -g -Wall -c server_engine.cpp -o server_engine.o

server: server.cpp server_engine.o scene.o
	g++ -g -Wall server.cpp server_engine.o scene.o -o server
