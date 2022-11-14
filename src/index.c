#include "game.h"

// Function that check whether the fruit is in the snake or not
int IsFruitInSnake(struct position fruit)
{
    for (int i = 0; i < snake_size; i++)
    {
        if (fruit.x == snake[i].x && fruit.y == snake[i].y)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    // Init screen (space for rendering in terminal)
    initscr();
    // Set raw input mode
    raw();
    // Disable printing while reading characters
    noecho();
    // Turn on keypad reading
    keypad(stdscr, TRUE);
    // Hide cursor
    curs_set(FALSE);

    // Set no-delay mode for getting input
    nodelay(stdscr, TRUE);

    // Initialize table on memory
    InitializeTable();
    // Draw the first frame of the table
    InitializeDraw();

    // Initialize snake on memory
    InitializeSnake();

    // Make a first drawing of the snake
    for (int i = 0; i < snake_size; i++)
    {
        DrawAt(snake[i].x, snake[i].y, SNAKECH);
    }

    // This is for getting random numbers
    srand(time(NULL));

    // This variable receive the position of the fruit
    struct position fruit;

    // Set a position to the fruit which isn't inside of it
    do
    {
        fruit.x = rand() % SIZE;
        fruit.y = rand() % SIZE;
    } while (IsFruitInSnake(fruit));

    // This variable will help us to set the speed of the snake
    int t = 0;
    // This one will prevent bugs where the snake runs backward and gets into itself
    int can_change_direction = 1;
    // This is the total score variable
    int score = 0;
    // Main game loop
    while (1)
    {
        // Check whether it is possible to change your direction
        // If you've changed your direction during the current frame, you can't do it again in order to prevent bugs. However the game keeps working normally and you can still move with no problems
        if (can_change_direction)
        {
            // Take key from screen input buffer
            int key = getch();
            // Check for key and if you're able to change to that direction, if so, change direction
            if (key == KEY_UP && direction != down)
            {
                direction = up;
                can_change_direction = 0;
            }
            else if (key == KEY_RIGHT && direction != left)
            {
                direction = right;
                can_change_direction = 0;
            }
            else if (key == KEY_DOWN && direction != up)
            {
                direction = down;
                can_change_direction = 0;
            }
            else if (key == KEY_LEFT && direction != right)
            {
                direction = left;
                can_change_direction = 0;
            }
        }

        // This will modify the frame rate of the game
        if (t >= 100 - (snake_size * 3))
        {
            // Get last position of the snake, so later we can replace it for the map background on the table
            struct position back = MoveSnake();

            // If snake's dead end the game
            if (VerifyDeath())
            {
                break;
            }
            // If snake's on fruit, generate other fruit, grow snake's size and Increase score
            else if (IsFruitInSnake(fruit))
            {
                do
                {
                    fruit.x = rand() % SIZE;
                    fruit.y = rand() % SIZE;
                } while (IsFruitInSnake(fruit));
                Grow();
                score++;
            }

            // Draw background character at the back of the snake on the table
            DrawAt(back.x, back.y, BACKGROUND);

            // Draw new snake head
            DrawAt(snake[snake_size - 1].x, snake[snake_size - 1].y, SNAKECH);
            // Draw new last part of the snake
            DrawAt(snake[0].x, snake[0].y, SNAKECH);

            // Draw fruit
            DrawAt(fruit.x, fruit.y, FRUITCH);

            // Update frame
            UpdateFrame(score);

            t = 0;
            can_change_direction = 1;
        }

        t++;
        usleep(10000);
    }

    // Print game over message
    printw("\nGame Over!\n");
    printw("Press any key to quit the game...\n");

    // Update screen
    refresh();

    // Sleep 500 miliseconds
    usleep(500000);

    // Set getch no-delay mode to false
    nodelay(stdscr, FALSE);

    // Clean input buffer
    flushinp();

    // Read any character
    getch();

    // Show cursor
    curs_set(TRUE);

    // End up with the terminal screen
    endwin();

    return 0;
}
