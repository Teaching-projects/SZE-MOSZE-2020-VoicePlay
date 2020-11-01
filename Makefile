OBJS := main.o player.o unit.o
CPPS := main.cpp player.cpp unit.cpp
CC := g++
CFLAGS := -std=c++17 -Wall -Werror -g



runCpps: $(OBJS)
	$(CC) $(CFLAGS) -o runGame $(OBJS)

player.o: player.cpp player.h jsonparser.h
	$(CC) $(CFLAGS) -c player.cpp

unit.o: unit.cpp unit.h jsonparser.h
	$(CC) $(CFLAGS) -c unit.cpp

main.o: main.cpp player.h unit.h jsonparser.h
	$(CC) $(CFLAGS) -c main.cpp
