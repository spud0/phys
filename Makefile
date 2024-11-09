# Some useful primitives.
CC := g++
WARN := -Wall
CFLAGS := $(CFLAGS) $(WARN) 

everything : 
	$(CC)$(CFLAGS) main.cc -o main

debug : 
	$(CC)$(CFLAGS) main.cc -g -o main
