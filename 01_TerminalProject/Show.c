#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3
#define WLINES (LINES - 2 * DX)
#define WCOLS (COLS - 2 * DX)

size_t count_num_lines(FILE *file)
{
	char *line = NULL;
	size_t len = 0, num_lines = 0;
	ssize_t read;

	while ((read = getline(&line, &len, file)) != -1) {
		num_lines++;
		free(line);
		line = NULL;
		len = 0;
	}
	return num_lines;
}

void read_lines(FILE *file, char **plines, size_t num_lines)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	for (size_t i = 0; i < num_lines; i++) {
		if ((read = getline(&line, &len, file)) == -1)
			break;
		plines[i] = line;
		line = NULL;
		len = 0;
	}
}

int count_max_digits_in_num(size_t num)
{
	int count = 0;
	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}

void display_lines_col(WINDOW *win, char **plines, size_t st, size_t end,
		       size_t st_col, size_t num_lines)
{
	int pad = count_max_digits_in_num(num_lines);
	for (size_t i = st; i < end; i++) {
		int offset = i - st + 2;
		if (end >= num_lines)
			offset--;
		if (i < num_lines && plines[i]) {
			if (st_col < strlen(plines[i]))
				mvwprintw(win, offset, 0, " %*lu: %.*s", pad, i,
					  WCOLS - 1,
					  plines[i] + st_col * sizeof(char));
			else
				mvwprintw(win, offset, 0, " %*lu:\n", pad, i);
		}
	}
}

int main(int argc, char **argv)
{
	WINDOW *win;
	FILE *file;
	int c = 0;
	size_t num_lines;
	char **plines;
	size_t st, end;
	size_t st_col = 0;

	if (argc != 2) {
		printf("One argument (file name) required\n");
		exit(1);
	}

	file = fopen(argv[1], "r");
	if (!file) {
		perror(argv[1]);
		exit(1);
	}

	initscr();
	noecho();
	cbreak();

	num_lines = count_num_lines(file);
	st = 0;
	end = WLINES;
	if (num_lines < end)
		num_lines = end;

	fseek(file, 0, SEEK_SET);
	plines = calloc(num_lines, sizeof(*plines));
	if (!plines) {
		perror("Couldn't allocate memory");
		endwin();
		fclose(file);
		exit(1);
	}
	read_lines(file, plines, num_lines);

	printw("File name: %s", argv[1]);
	refresh();

	win = newwin(WLINES, WCOLS, DX, DX);
	keypad(win, TRUE);
	scrollok(win, TRUE);

	while (1) {
		werase(win);
		box(win, 0, 0);
		display_lines_col(win, plines, st, end, st_col, num_lines);
		box(win, 0, 0);
		wmove(win, 0, 0);
		wrefresh(win);
		c = wgetch(win);
		if (c == 27)
			break;
		switch (c) {
		case 32:
		case KEY_DOWN:
			st++;
			end++;
			break;
		case KEY_UP:
			if (st > 0) {
				st--;
				end--;
			}
			break;
		case KEY_LEFT:
			if (st_col > 0)
				st_col--;
			break;
		case KEY_RIGHT:
			st_col++;
			break;
		case KEY_NPAGE:
			st += WLINES;
			end += WLINES;
			break;
		case KEY_PPAGE:
			if (st >= WLINES) {
				st -= WLINES;
				end -= WLINES;
			} else {
				st = 0;
				end = WLINES;
			}
			break;
		default:
			break;
		}
	}

	for (size_t i = 0; i < num_lines; i++) {
		free(plines[i]);
	}
	free(plines);
	fclose(file);
	endwin();
	return 0;
}
