#include <stdio.h>
#include <stdlib.h>

#define str2dec(NPTR) (strtol((NPTR), NULL, 10))

void help()
{
	printf("Usage:\n");
	printf("(1) ./range END\n");
	printf("(2) ./range START END\n");
	printf("(3) ./range START END STEP\n");
}

void range(long start, long end, long step)
{
	if (end <= start || step <= 0) {
		help();
		return;
	}
	for (long i = start; i < end; i += step) {
		printf("%ld\n", i);
	}
}

int main(int argc, char **argv)
{
	switch (argc) {
	case 1:
		help();
		break;
	case 2:
		range(0, str2dec(argv[1]), 1);
		break;
	case 3:
		range(str2dec(argv[1]), str2dec(argv[2]), 1);
		break;
	case 4:
		range(str2dec(argv[1]), str2dec(argv[2]), str2dec(argv[3]));
		break;
	default:
		printf("Well, the task doesn't state what to do here... :)\n");
		break;
	}
	return 0;
}
