CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=

duplica: src/main.c
	$(CC) $(CFLAGS) -o main src/main.c $(LIBS)