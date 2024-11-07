#complier is g++
CC=g++
#complier flags -g -Wall
CFLAGS=-g -Wall
#compliler sources are .cpp files
SOURCES=*.cpp
#inlcude pre-complied .o
#OBJECTS=*.o
#name of the executable
EXECUTABLE=world_cities.out

#make all shoud do this 
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(SOURCES) $(OBJECTS) -o $@
#use these commands and flags
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
