# Some useful primitives.
CC := g++
WARN := -Wall
SDL  := -lSDL2
TARGET := main
CFLAGS := $(CFLAGS) $(WARN) 

# Grab all the C++ files in the project.
SOURCES := $(wildcard *.cc)
OBJS :=  $(SOURCES:.cc=.o)

everything : 
	$(CC)$(CFLAGS) main.cc -o main 

debug : 
	$(CC)$(CFLAGS) main.cc -g -o main $(SDL)

.PHONY: clean
clean :
	rm -f $(TARGET)
