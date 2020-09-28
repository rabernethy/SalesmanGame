# Written by James Gottshall with much help from stack overflow
# Big fan of how well this build system works!

#Makefile for Salesmen game
.DEFAULT_GOAL := main

#g++ compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall -std=c++11 -D_GNU_SOURCE
# Linking flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Setup flags from wildcards
SOURCES := $(filter-out src/main.cpp, $(filter-out src/test.cpp, $(wildcard src/*.cpp))) # get all cpp files excluding main and test
INCLUDES := $(wildcard src/*.h)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)

test: obj/test.o $(OBJECTS)
	$(CC) $(CFLAGS) obj/test.o $(OBJECTS) -o $@ $(LDFLAGS)

main: obj/main.o $(OBJECTS)
	$(CC) $(CFLAGS) obj/main.o $(OBJECTS) -o main $(LDFLAGS)

# I have no idea what I'm doing, compilation I guess?
$(OBJECTS): obj/%.o : src/%.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@

# Create object folder if it does not exist
obj:
	mkdir $@

clean:
	@rm *.o
	@rm test
	@rm main
	@rm -rf object

run:  main
	./main
