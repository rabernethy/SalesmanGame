#Makefile for Salesmen game
.DEFAULT_GOAL := main

#g++ compiler
CC = g++

CFLAGS = -g -Wall -std=c++11 -D_GNU_SOURCE
LDFLAGS = -lncurses
HEADER = account.h gui.h inventory.h item.h screen.h utils.h constants.h
OBJ = account.o gui.o inventory.o item.o screen.o utils.o
CPPFILES =account.cpp gui.cpp inventory.cpp item.cpp screen.cpp utils.cpp

test: test.o $(OBJ)
	$(CC) $(CFLAGS) test.o $(OBJ) -o test $(LDFLAGS)

test.o: test.cpp $(HEADER)
	$(CC) $(CFLAGS) -c test.cpp $(LDFLAGS)

main: main.o $(OBJ)
	$(CC) $(CFLAGS) main.o $(OBJ) -o main $(LDFLAGS)

main.o: main.cpp $(HEADER)
	$(CC) $(CFLAGS) -c main.cpp $(LDFLAGS)

$(OBJ): $(CPPFILES) $(HEADER)
		  $(CC) $(CFLAGS) -c $(CPPFILES)  $(LDFLAGS)

clean:
	rm *.o
	rm test
	rm main

run:  main
	./main
