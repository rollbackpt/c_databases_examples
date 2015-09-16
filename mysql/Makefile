CC = gcc
CFLAGS = `mysql_config --cflags --libs`

mysql_example: mysql_example.c
	$(CC) -o mysql_example mysql_example.c $(CFLAGS)

clean:
	rm -rf mysql_example
