GENERATES = prog*[1-3] prog-a prog-so prog *.so *.a *.o *~ o.*
CC = gcc
CFLAGS = -Wall -Werror -fPIC
WORKING_DIR = $(PWD)

all: prog prog-a prog-so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

prog:	const.o fun.o prog.o

static_lib: const.o fun.o
	ar -rcs liboutput_static.a $^

dyn_lib: const.o fun.o
	$(CC) -shared $^ -oliboutput.so

prog-a: prog.o static_lib
	$(CC) -L$(WORKING_DIR) -o $@ $< -loutput_static

prog-so: prog.o dyn_lib
	$(CC) -L$(WORKING_DIR) -o $@ $< -loutput

test: test_void test_1arg test_3args
	@ echo "Testing started..."
	cmp prog1 prog-a1
	cmp prog-a1 prog-so1
	cmp prog2 prog-a2
	cmp prog-a2 prog-so2
	cmp prog3 prog-a3
	cmp prog-a3 prog-so3
	@ echo "Testing finished"

test_void: prog prog-a prog-so
	./prog > prog1 2>&1
	./prog-a > prog-a1 2>&1
	LD_LIBRARY_PATH=$(WORKING_DIR) ./prog-so > prog-so1 2>&1

test_1arg: prog prog-a prog-so
	./prog arg1 > prog2 2>&1
	./prog-a arg1 > prog-a2 2>&1
	LD_LIBRARY_PATH=$(WORKING_DIR) ./prog-so arg1 > prog-so2 2>&1

test_3args: prog prog-a prog-so
	./prog arg1 arg2 arg3 > prog3 2>&1
	./prog-a arg1 arg2 arg3 > prog-a3 2>&1
	LD_LIBRARY_PATH=$(WORKING_DIR) ./prog-so arg1 arg2 arg3 > prog-so3 2>&1

clean:
	rm -rf $(GENERATES)
