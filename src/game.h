#define SIZE 10
#define AREA (SIZE * SIZE)

#define BACKGROUND '_'
#define SNAKECH '*'
#define FRUITCH '#'

#define INITIAL_SNAKE_SIZE 3

struct position
{
    int x;
    int y;
};

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

enum directions
{
    up,
    right,
    down,
    left
};
enum directions direction = right;

#include "snake.c"
#include "table.c"
