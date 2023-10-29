#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

#define KEYWORD "PROTECT"

int remove(const char * pathname)
{
	if (strstr(pathname, KEYWORD)) {
		return 0;
	} else {
		int (*std_remove)(const char *pathname) = dlsym(RTLD_NEXT, "remove");
		if (!std_remove) {
			fprintf(stderr, "Failed to find standard remove\n");
			return 1;
		}
		return std_remove(pathname);
	}
}
