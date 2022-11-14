char table[AREA];

// Fill table with the background
void InitializeTable()
{
    for (int i = 0; i < AREA; i++)
    {
        table[i] = BACKGROUND;
    }
}

// Draw the first frame of the table
void InitializeDraw()
{
    move(0, 0);
    for (int i = 0; i < AREA; i++)
    {
        printw("%c", BACKGROUND);
        if ((i + 1) % SIZE == 0)
        {
            printw("\n");
        }
    }
}

// Change some character at the specified position
int DrawAt(int x, int y, char s)
{
    if (x >= SIZE || y >= SIZE)
    {
        return -1;
    }

    table[y * SIZE + x] = s;
    return 0;
}

// Draw new frame
void UpdateFrame(int score)
{
    move(0, 0);
    for (int i = 0; i < AREA; i++)
    {
        printw("%c", table[i]);
        if ((i + 1) % SIZE == 0)
        {
            printw("\n");
        }
    }
    printw("Score: %d\n", score);
    refresh();
}
