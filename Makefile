CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14
DEPS =
LIBS =
OBJECTS = main.o
LINTOBJS = main.cpp

all: main

run:
	./main

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS) $(LIBS)

lint:
	cpplint --recursive src/ $(LINTOBJS)

clean:
	rm $(OBJECTS) main