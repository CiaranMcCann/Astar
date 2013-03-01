CC=gcc
CFLAGS=-I. -lm
APP=main

build: main.o
	$(CC) -o $(APP) main.o $(CFLAGS)

clean:
	rm *.o
	rm $(APP)