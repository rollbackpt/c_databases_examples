CC = gcc
CFLAGS = $$(pkg-config --cflags --libs libmongoc-1.0)

mongodb_example: mongodb_example.c
	$(CC) -o mongodb_example mongodb_example.c $(CFLAGS)

clean:
	rm -rf mongodb_example
