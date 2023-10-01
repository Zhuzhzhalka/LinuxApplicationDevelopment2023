#include "outlib.h"
#include <stdio.h>
void output(char *str)
{
	printf("%d: %s\012", Count++, str);
}
