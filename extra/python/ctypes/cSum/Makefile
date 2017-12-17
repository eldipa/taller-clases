all: test libsum.so

test: sum.c test.c
	$(CC) -Wall -pedantic -o $@ sum.c test.c

libsum.so: sum.c
	$(CC) -fPIC -shared -o $@ $?


