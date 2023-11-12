#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define TEXT_DOMAIN "num_guesser"

int main(int argc, char *argv[])
{
	int interval_start = 1;
	int interval_end = 100;
	char *answer = NULL;
	size_t answer_len;
	int delim;
	setlocale(LC_ALL, "");
	bindtextdomain(TEXT_DOMAIN, "po");
	textdomain(TEXT_DOMAIN);

	fprintf(stdout, _("Think about some number from 1 to 100. I'll guess it!\n"));

	while (interval_end - interval_start) {
		delim = interval_start - 1 +
			(interval_end - interval_start) / 2 +
			(interval_end - interval_start) % 2;

		fprintf(stdout, _("Is your number bigger than %d?\n"), delim);
		if (getline(&answer, &answer_len, stdin) == -1) {
			free(answer);
			return 1;
		}

		if (strstr(answer, _("yes"))) {
			interval_start = delim + 1;
		} else if (strstr(answer, _("no"))) {
			interval_end = delim;
		} else {
			fprintf(stdout, _("Answer 'yes' or 'no'\n"));
			continue;
		}
	}
	fprintf(stdout, _("Your number is %d\n"), interval_end);

	free(answer);
	return 0;
}
