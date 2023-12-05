/*! @mainpage
 *
 *  Usage: ./num_guesser [OPTION]...\n
 *  Simple guess number game.
 *
 *  -h, --help    display help message\n
 *  -r            work with numbers in roman form
 *
 *  Использование: ./num_guesser [ОПЦИЯ]...\n
 *  Простая игра на загадывание чисел.
 *
 *  -h, --help    вывести справочное сообщение\n
 *  -r            работать с римскими цифрами
 */
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING)
#define TEXT_DOMAIN "num_guesser"

/** Table representing first 100 arabic->roman mapping.
 */
static char *table_ar2rom[100][2] = {
    {"1", "I"},	      {"2", "II"},	 {"3", "III"},	    {"4", "IV"},
    {"5", "V"},	      {"6", "VI"},	 {"7", "VII"},	    {"8", "VIII"},
    {"9", "IX"},      {"10", "X"},	 {"11", "XI"},	    {"12", "XII"},
    {"13", "XIII"},   {"14", "XIV"},	 {"15", "XV"},	    {"16", "XVI"},
    {"17", "XVII"},   {"18", "XVIII"},	 {"19", "XIX"},	    {"20", "XX"},
    {"21", "XXI"},    {"22", "XXII"},	 {"23", "XXIII"},   {"24", "XXIV"},
    {"25", "XXV"},    {"26", "XXVI"},	 {"27", "XXVII"},   {"28", "XXVIII"},
    {"29", "XXIX"},   {"30", "XXX"},	 {"31", "XXXI"},    {"32", "XXXII"},
    {"33", "XXXIII"}, {"34", "XXXIV"},	 {"35", "XXXV"},    {"36", "XXXVI"},
    {"37", "XXXVII"}, {"38", "XXXVIII"}, {"39", "XXXIX"},   {"40", "XL"},
    {"41", "XLI"},    {"42", "XLII"},	 {"43", "XLIII"},   {"44", "XLIV"},
    {"45", "XLV"},    {"46", "XLVI"},	 {"47", "XLVII"},   {"48", "XLVIII"},
    {"49", "XLIX"},   {"50", "L"},	 {"51", "LI"},	    {"52", "LII"},
    {"53", "LIII"},   {"54", "LIV"},	 {"55", "LV"},	    {"56", "LVI"},
    {"57", "LVII"},   {"58", "LVIII"},	 {"59", "LIX"},	    {"60", "LX"},
    {"61", "LXI"},    {"62", "LXII"},	 {"63", "LXIII"},   {"64", "LXIV"},
    {"65", "LXV"},    {"66", "LXVI"},	 {"67", "LXVII"},   {"68", "LXVIII"},
    {"69", "LXIX"},   {"70", "LXX"},	 {"71", "LXXI"},    {"72", "LXXII"},
    {"73", "LXXIII"}, {"74", "LXXIV"},	 {"75", "LXXV"},    {"76", "LXXVI"},
    {"77", "LXXVII"}, {"78", "LXXVIII"}, {"79", "LXXIX"},   {"80", "LXXX"},
    {"81", "LXXXI"},  {"82", "LXXXII"},	 {"83", "LXXXIII"}, {"84", "LXXXIV"},
    {"85", "LXXXV"},  {"86", "LXXXVI"},	 {"87", "LXXXVII"}, {"88", "LXXXVIII"},
    {"89", "LXXXIX"}, {"90", "XC"},	 {"91", "XCI"},	    {"92", "XCII"},
    {"93", "XCIII"},  {"94", "XCIV"},	 {"95", "XCV"},	    {"96", "XCVI"},
    {"97", "XCVII"},  {"98", "XCVIII"},	 {"99", "XCIX"},    {"100", "C"}};

/** Convert roman string to equivalent arabic int.
 *
 * @param rom roman string
 * @return int arabic integer
 */
static int rom2ar(char *rom)
{
	for (int i = 0; i < 100; i++)
		if (!strcmp(table_ar2rom[i][1], rom))
			return strtoul(table_ar2rom[i][0], NULL, 10);
	return -1;
}

/** Convert arabic integer @ar to equivalent roman string.
 *
 * @param ar arabic integer
 * @return char * pointer to equivalent roman string
 */
static char *ar2rom(int ar)
{
	char ar_str[3];
	sprintf(ar_str, "%d", ar);
	for (int i = 0; i < 100; i++)
		if (!strcmp(table_ar2rom[i][0], ar_str))
			return table_ar2rom[i][1];
	return NULL;
}

/** Display help message.
 */
static void display_help()
{
	printf(_("Usage: ./num_guesser [OPTION]...\n"));
	printf(_("Simple guess number game.\n\n"));
	printf(_("  -h, --help    display help message\n"));
	printf(_("  -r            work with numbers in roman form\n"));
}

/** Convert arabic integer @ar to equivalent roman string.
 *
 * @param use_r roman number usage flag
 * @return int guessed number
 */
static int guess_process(int use_r)
{
	int interval_start = 1;
	int interval_end = 100;
	char *answer = NULL;
	size_t answer_len;
	int delim;

	while (interval_end - interval_start) {
		delim = interval_start - 1 +
			(interval_end - interval_start) / 2 +
			(interval_end - interval_start) % 2;

		if (use_r)
			fprintf(stdout, _("Is your number bigger than %s?\n"),
				ar2rom(delim));
		else
			fprintf(stdout, _("Is your number bigger than %d?\n"),
				delim);
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

	free(answer);
	return interval_end;
}

int main(int argc, char *argv[])
{
	int guessed_num;
	int use_r = 0;

	setlocale(LC_ALL, "");
	bindtextdomain(TEXT_DOMAIN, "po");
	textdomain(TEXT_DOMAIN);

	if (argc > 2) {
		display_help();
		return 1;
	}

	if (argc > 1 && !strcmp(argv[1], "-r")) {
		use_r = 1;
	} else if (argc > 1) {
		display_help();
		return 1;
	}

	if (use_r)
		fprintf(
		    stdout,
		    _("Think about some number from I to C. I'll guess it!\n"));
	else
		fprintf(stdout, _("Think about some number from 1 to 100. I'll "
				  "guess it!\n"));

	guessed_num = guess_process(use_r);

	if (use_r)
		fprintf(stdout, _("Your number is %s\n"), ar2rom(guessed_num));
	else
		fprintf(stdout, _("Your number is %d\n"), guessed_num);

	return 0;
}
