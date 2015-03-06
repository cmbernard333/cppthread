CC = g++
CFLAGS = -c -Wall
LDFLAGS = -lpthread
SRCDIR = ./src
SOURCES = $(wildcard $(SRCDIR)/*.cpp) 
INC = -I./include
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = scheduler

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
