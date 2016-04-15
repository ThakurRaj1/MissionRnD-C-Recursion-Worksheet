/*
Find if there is a connecting path between two given points in the maze.
The maze is a matrix of order MxN, check if there exists a path between (x1,y1) and (x2,y2).
Two points are said to connected if there is a series of 1's non-diagonally.
Example:
Maze of order 4x4:

1	0	1	0
1	1	0	0
0	1	0	1
0	1	1	1

(x1,y1):(0,0)
(x2,y2):(2,3)

In this case, there exists a connected path:
1
1	1
	1		1
	1	1	1

Since there is a connected path, your function has to return 1.
If a path doesn't exist between two co-ordinates then return 0.
If the co-ordinates are invalid or size of the matrix is invalid then return 0.

Function Prototype :path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2) ;
Maze: Pointer to first element of an array .
rows : No of rows
columns : Columns
x1,x2,y1,y2: Co-ordinates

Hint : You can use path_exists as a wrapper function for your original recursive function which might take
more parameters .
*/

#include<stdlib.h>

int path_exists_recursive(int *maze, int rows, int columns, int x1, int y1, int x2, int y2, int **visited) {
	if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns) {
		return 0;
	}
	if (*((maze + x1 * columns) + y1) == 0) {
		return 0;
	}
	if (x1 == x2 && y1 == y2) {
		return 1;
	}
	if (visited[x1][y1] == 1) {
		return 0;
	}
	visited[x1][y1] = 1;
	int right = path_exists_recursive(maze, rows, columns, x1, y1 + 1, x2, y2, visited);
	if (right) {
		return right;
	}
	int down = path_exists_recursive(maze, rows, columns, x1 + 1, y1, x2, y2, visited);
	if (down) {
		return down;
	}
	int left = path_exists_recursive(maze, rows, columns, x1, y1 - 1, x2, y2, visited);
	if (left) {
		return left;
	}
	int top = path_exists_recursive(maze, rows, columns, x1 - 1, y1, x2, y2, visited);
	if (top) {
		return top;
	}
			
	return 0;
}

void initialize(int **visited, int len, int rows, int columns, int val) {
	if (!visited) {
		return;
	}
	int i;
	for (i = 0; i < len; i++) {
		visited[i] = (int*)malloc(sizeof(int));
	}
	int j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			visited[i][j] = val;
		}
	}
}

int path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	if (rows < 1 || columns < 1 || x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns || x2 < 0 || x2 >= rows || y2 < 0 || y2 >= columns) {
		return 0;
	}
	int len = rows * columns;
	int **visited = (int**)malloc(sizeof(int*) * len);
	initialize(visited, len, rows, columns, 0);
	int ans = path_exists_recursive(maze, rows, columns, x1, y1, x2, y2, visited);
	return ans;
}
