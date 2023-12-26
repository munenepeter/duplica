CFLAGS=-Wall -Wextra -std=c11 -pendatic -ggdb
LIBS=

deplica: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)