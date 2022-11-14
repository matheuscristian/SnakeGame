struct position *snake;
int snake_size = INITIAL_SNAKE_SIZE;

int InitializeSnake()
{
    // Alloc snake body on memory
    snake = (struct position *)malloc(sizeof(struct position) * INITIAL_SNAKE_SIZE);

    // Check whether the initial snake size is valid according to the table or not
    if (INITIAL_SNAKE_SIZE > SIZE / 2 + 1)
    {
        return -1;
    }

    // Fill snake body with its initial positions
    int j = 0;
    for (int i = INITIAL_SNAKE_SIZE - 1; i > -1; i--)
    {
        snake[i].y = SIZE / 2;
        snake[i].x = SIZE / 2 - j;
        j++;
    }

    // Set direction to right
    direction = right;

    return 0;
}

// Move snake and return the last part of it
struct position MoveSnake()
{
    struct position back = snake[0];

    for (int i = 0; i < snake_size - 1; i++)
    {
        snake[i] = snake[i + 1];
    }

    if (direction == up)
    {
        snake[snake_size - 1].y--;
    }
    else if (direction == right)
    {
        snake[snake_size - 1].x++;
    }
    else if (direction == down)
    {
        snake[snake_size - 1].y++;
    }
    else if (direction == left)
    {
        snake[snake_size - 1].x--;
    }

    return back;
}

// Check if the snake is on a wall or on itself
int VerifyDeath()
{
    if (snake[snake_size - 1].x == SIZE || snake[snake_size - 1].x == -1 || snake[snake_size - 1].y == SIZE || snake[snake_size - 1].y == -1)
    {
        return 1;
    }

    for (int i = 0; i < snake_size - 1; i++)
    {
        if (snake[snake_size - 1].x == snake[i].x && snake[snake_size - 1].y == snake[i].y)
        {
            return 1;
        }
    }

    return 0;
}

int Grow()
{
    // Create a temp snake body with extended size
    struct position *snake_tmp = (struct position *)malloc(sizeof(struct position) * (snake_size + 1));
    // Copy the entire snake body to the temp body preserving the first position
    for (int i = 0; i < snake_size; i++)
    {
        snake_tmp[i + 1] = snake[i];
    }
    // Now, snake_tmp[0] = snake_tmp[1]
    snake_tmp[0] = snake[0];
    // Increase snake size
    snake_size++;
    // Realloc snake body on memory with the new size
    snake = (struct position *)realloc(snake, sizeof(struct position) * snake_size);

    // If it wasn't possible to realloc it, return -1
    if (!snake)
    {
        return -1;
    }

    // Copy the temp snake body to the snake body
    for (int i = 0; i < snake_size; i++)
    {
        snake[i] = snake_tmp[i];
    }

    // Remove snake temp from memory
    free(snake_tmp);

    return 0;
}
