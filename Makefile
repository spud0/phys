# Some useful primitives.
CC := g++
WARN := -Wall
SDL  := -lSDL2
CFLAGS := $(CFLAGS) $(WARN) 

everything : 
	$(CC)$(CFLAGS) main.cc -o main 

debug : 
	$(CC)$(CFLAGS) main.cc -g -o main $(SDL)

clean :
	echo "idk yet"
