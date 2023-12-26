CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=

deplica: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)