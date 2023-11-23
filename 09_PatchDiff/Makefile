GENERATES = maze-[1-4] *.o *~ o.* maze-[2-4].c
CC = gcc
CFLAGS = -Wall -Werror -fPIC

all: patch maze-1 maze-2 maze-3 maze-4

run: all
	@ echo "@@@@@@@@@@@@@@@@@@@@@@"
	./maze-1
	@ echo "@@@@@@@@@@@@@@@@@@@@@@"
	./maze-2 6
	@ echo "@@@@@@@@@@@@@@@@@@@@@@"
	./maze-3 '.#' 6
	@ echo "@@@@@@@@@@@@@@@@@@@@@@"
	./maze-4 42 '.#' 6
	@ echo "@@@@@@@@@@@@@@@@@@@@@@"

patch:
	patch -o maze-2.c -u -i patches/0001-Implement-PatchDiff-patch1-handle-maze-size.patch
	patch -o maze-3.c -u -i patches/0002-Implement-PatchDiff-patch2-handle-maze-symbols-and-m.patch
	patch -o maze-4.c -u -i patches/0003-Implement-PatchDiff-patch3-handle-seed-and-maze-symb.patch

maze-2: maze-2.c
	$(CC) $(CFLAGS) -o $@ $<

maze-3: maze-3.c
	$(CC) $(CFLAGS) -o $@ $<

maze-4: maze-4.c
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(GENERATES)
