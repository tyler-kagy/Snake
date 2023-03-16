#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

string grid[10][10];
int score = 0;
int food_x = rand() % 10;
int food_y = rand() % 10;
int snake_x;
int snake_y;
int init_dir = rand() % 4;

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

void update()
{
    cout << "\033[1;1H\033[2J"; // clear the screen and return to line zero
}

void spawn_food()
{
    grid[food_x][food_y] = "🍔";
}

void spawn_snake()
{
    // random initial location != food location
    snake_x = food_x;
    snake_y = food_y;

    while (snake_x == food_x && snake_y == food_y)
    {
        snake_x = rand() % 10;
        snake_y = rand() % 10;
    }

    grid[snake_x][snake_y] = "🐍";
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

    update();
    spawn_food();
    spawn_snake();

    while (!dead)
    {
        display();
        sleep_for(seconds(1));

        // TODO: Move endlessly in initial direction at 1 space per second
        // allow for rollover at edges (seems to disappear on top edge)
        grid[snake_x][snake_y] = " ";
        switch (init_dir)
        {
        case 0:
            // Left
            if (snake_y != 0)
                grid[snake_x][snake_y - 1] = "🐍";
            else
                grid[snake_x][9] = "🐍";
            break;
        case 1:
            /// Up
            if (snake_x != 0)
                grid[snake_x - 1][snake_y] = "🐍";
            else
                grid[10][snake_y] = "🐍";
            break;
        case 2:
            // Right
            if (snake_y != 9)
                grid[snake_x][snake_y + 1] = "🐍";
            else
                grid[snake_x][0] = "🐍";
            break;
        case 3:
            // Down
            if (snake_x != 9)
                grid[snake_x + 1][snake_y] = "🐍";
            else
                grid[0][snake_y] = "🐍";
            break;
        }

        update();
    }

    update();

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