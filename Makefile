CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -Iinclude

TARGET = bin/vmem

SOURCES = src/main.c src/input.c src/parser.c src/page.c src/frame.c \
          src/replacement.c src/translate.c src/stats.c src/simulator.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run test asan

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	@output="$$(printf '4\n2\nFIFO\nread 0\nread 256\nread 512\nstats\nquit\n' | ./$(TARGET) 2>/dev/null)"; \
	echo "$$output" | grep -q "Page faults: 3"; \
	echo "$$output" | grep -q "Evictions: 1"; \
	echo "VMU smoke test passed."

asan:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) -g -fsanitize=address -fno-omit-frame-pointer" all

clean:
	rm -f $(OBJECTS) $(TARGET)
