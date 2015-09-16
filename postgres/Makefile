CC = gcc
CFLAGS = -I/usr/include/postgresql/ -lpq

postgres_example: postgres_example.c
	$(CC) -o postgres_example postgres_example.c $(CFLAGS)

clean:
	rm -rf postgres_example
