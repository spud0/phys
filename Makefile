# Some useful primitives.
CC := g++
WARN := -Wall
SDL  := -lSDL2
TARGET := main
CFLAGS := $(CFLAGS) $(WARN) 

# Grab all the C++ files in the project.
SOURCES := $(wildcard *.cc)
OBJS :=  $(SOURCES:.cc=.o)

# A little misleading. This should run make [debug, build, tests and clean] ?
everything : 
	$(CC)$(CFLAGS) main.cc -o main $(SDL)

build :
	$(CC)$(CFLAGS) main.cc -o main $(SDL)
 
debug : 
	$(CC)$(CFLAGS) main.cc -g -o main $(SDL)

.PHONY: tests
tests :
	$(CC) $(CFLAGS) tests/test.cc -o test

.PHONY: clean
clean :
	rm -f $(TARGET)
	rm -f test
