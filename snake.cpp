#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

string grid[10][10];
int score = 0;
int food_row;
int food_col;
int snake_row;
int snake_col;
int direction;

void display()
{
    cout << "Score: " << score << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void clear()
{
    cout << "\033[1;1H\033[2J"; // clear the screen and return to line zero
}

void spawn_food()
{
    food_row = rand() % 10;
    food_col = rand() % 10;
    grid[food_row][food_col] = "🍔";
}

void spawn_snake()
{
    direction = rand()%4;

    // random initial location != food location
    snake_row = food_row;
    snake_col = food_col;

    while (snake_row == food_row && snake_col == food_col)
    {
        snake_row = rand() % 10;
        snake_col = rand() % 10;
    }

    grid[snake_row][snake_col] = "🐍";
}

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds

    bool dead = false;
    // Use current time as seed for random generator
    srand(time(0));

    // populate the grid with empty space
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j] = " ";
        }
    }

    clear();
    spawn_food();
    spawn_snake();

    while (!dead)
    {
        display();
        sleep_for(milliseconds(500));

        // TODO: use modulo instead of if/else for all cases
        grid[snake_row][snake_col] = " ";
        switch (direction)
        {
        case 0:
            // Left
            if (snake_col != 0)
                //grid[snake_row][snake_col - 1] = "🐍";
                snake_col -= 1;
            else
                //grid[snake_row][9] = "🐍";
                snake_col = 9;
            break;
        case 1:
            /// Up
            if (snake_row != 0)
                //grid[snake_row - 1][snake_col] = "🐍";
                snake_row -= 1;
            else
                //grid[9][snake_col] = "🐍";
                snake_row = 9;
            break;
        case 2:
            // Right
                //grid[snake_row][(snake_col + 1)%10] = "🐍";
                snake_col = (snake_col + 1) % 10;
            break;
        case 3:
            // Down
                //grid[(snake_row + 1)%10][snake_col] = "🐍";
                snake_row = (snake_row + 1) % 10;
            break;
        }

        grid[snake_row][snake_col] = "🐍";

        clear();
    }

    // create borders
    // |=========|
    // |         |
    // |=========|
    // arrow key movement
    // score counter
    // high score counter
    // game over condition
    // difficulty selection

    display();
}