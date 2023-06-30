all: compile link

compile:
	g++ -Isrc/include -c mainlark.cpp

link:
	g++ mainlark.o -o mainlark -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio