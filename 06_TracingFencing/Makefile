GENERATES = move *.o *.so infile outfile infilePROTECT
CC        = gcc
CFLAGS    = -Wall -Werror -g -fPIC

all:	move

%.o:    %.c
	$(CC) $(CFLAGS) -c -o $@ $<

move:	move.o

dlib:   lib_remove.o
	$(CC) -shared $< -o lib_remove.so

test:   move dlib
	chmod +x $(PWD)/test.sh
	$(PWD)/test.sh

clean:
	rm -rf $(GENERATES)
