GENERATES = range *.o test-[1-2]
CC        = gcc
CFLAGS    = -Wall -Werror -O0 -g

all:	range

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

range:	range.o

test:   range
	gdb -x gdb-scenario-1 --args ./range | grep "@@@*" | cut -c 4- | sed '0~4 a\---\' > test-1
	gdb -x gdb-scenario-2 --args ./range | grep "@@@*" | cut -c 4- | sed '0~4 a\---\' > test-2
	cmp test-1 reference-1
	cmp test-2 reference-2

clean:
	rm -rf $(GENERATES)
