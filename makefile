# Makefile for cartor_console, strings, and test_cartor_console

CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = cartor_console.o strings.o test_cartor_console.o
TARGET = test_cartor_console

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

cartor_console.o: cartor_console.c cartor_console.h
	$(CC) $(CFLAGS) -c cartor_console.c

strings.o: strings.c strings.h
	$(CC) $(CFLAGS) -c strings.c

test_cartor_console.o: test_cartor_console.c cartor_console.h strings.h
	$(CC) $(CFLAGS) -c test_cartor_console.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
