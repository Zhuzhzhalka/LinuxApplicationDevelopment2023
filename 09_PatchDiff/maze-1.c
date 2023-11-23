#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	int default_size;
	int actual_size;
	char pass_symb;
	char wall_symb;
	char **map;
	Point *stack;
	int stack_top;
} Maze;

void panic(const char *err)
{
	perror(err);
	exit(1);
}

void pushStack(Point *stack, int *top, Point p)
{
	stack[(*top)++] = p;
}

Point popStack(Point *stack, int *top)
{
	return stack[--(*top)];
}

void initializeMaze(Maze *maze)
{
	maze->map = malloc(sizeof(maze->map) * maze->actual_size);
	if (!maze->map)
		panic("Allocation error");
	for (int i = 0; i < maze->actual_size; i++) {
		maze->map[i] = malloc(sizeof(*maze->map) * maze->actual_size);
		if (!maze->map[i])
			panic("Allocation error");
	}

	maze->stack =
	    malloc(maze->default_size * maze->default_size * sizeof(Point));
	if (!maze->stack)
		panic("Allocation error");

	for (int i = 0; i < maze->actual_size; i++)
		for (int j = 0; j < maze->actual_size; j++)
			maze->map[i][j] = maze->wall_symb;
}

void generateMaze(Maze *maze)
{
	Point start = {0, 0};
	maze->map[start.x * 2 + 1][start.y * 2 + 1] = maze->pass_symb;
	pushStack(maze->stack, &maze->stack_top, start);

	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};

	while (maze->stack_top > 0) {
		Point cur = popStack(maze->stack, &maze->stack_top);
		int dirs[4];

		for (int i = 0; i < 4; i++)
			dirs[i] = i;
		for (int i = 3; i > 0; i--) {
			int j = rand() % (i + 1);
			int temp = dirs[i];
			dirs[i] = dirs[j];
			dirs[j] = temp;
		}
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[dirs[i]];
			int ny = cur.y + dy[dirs[i]];
			if (nx >= 0 && nx < maze->default_size && ny >= 0 &&
			    ny < maze->default_size &&
			    maze->map[nx * 2 + 1][ny * 2 + 1] ==
				maze->wall_symb) {
				maze->map[cur.x * 2 + 1 + dx[dirs[i]]]
					 [cur.y * 2 + 1 + dy[dirs[i]]] =
				    maze->pass_symb;
				maze->map[nx * 2 + 1][ny * 2 + 1] =
				    maze->pass_symb;
				pushStack(maze->stack, &maze->stack_top,
					  (Point){nx, ny});
			}
		}
	}
}

void printMaze(Maze *maze)
{
	for (int i = 0; i < maze->actual_size; i++) {
		for (int j = 0; j < maze->actual_size; j++)
			printf("%c", maze->map[i][j]);
		printf("\n");
	}
}

void freeMaze(Maze *maze)
{
	for (int i = 0; i < maze->actual_size; i++)
		free(maze->map[i]);
	free(maze->map);
}

int main(int argc, char *argv[])
{
	int size = 6;
	Maze maze = {size, size * 2 + 1, '.', '#', NULL, NULL, 0};

	srand(time(NULL));
	initializeMaze(&maze);
	generateMaze(&maze);
	printMaze(&maze);
	freeMaze(&maze);
	return 0;
}
