CFLAGS=-std=c89 -pedantic -Wall -Wextra -march=native -O3

.PHONY: all
all: bf

.PHONY: clean
clean:
	$(RM) -- bf
