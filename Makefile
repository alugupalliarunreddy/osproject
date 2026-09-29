CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g -Iinclude
SRC = src/main.c src/input.c
TARGET = bin/vmem

.PHONY: all run clean test

all: $(TARGET)

$(TARGET): $(SRC) include/input.h include/vmem.h
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	bash tests/test_long_input.sh

clean:
	rm -f $(TARGET)
