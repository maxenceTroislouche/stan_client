CC=g++
OPTS=-Wall -Wextra
LIBS=-lwiringPi `wx-config --cxxflags --libs`
INCLUDES=-Iincludes/

all: executables/main.exe

clean:
	rm objects/* executables/*

objects/MainFrame.o: src/MainFrame.cpp
	$(CC) $^ -c -o $@ $(INCLUDES) $(LIBS)

objects/fingerprint.o: src/fingerprint.c
	$(CC) $^ -c -o $@ $(INCLUDES) $(LIBS)

executables/main.exe: src/App.cpp objects/MainFrame.o objects/fingerprint.o
	g++ $^ -o $@ $(INCLUDES) $(LIBS)
