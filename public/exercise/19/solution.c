#include "karel.h"
#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(6, 3);
    karel_add_beeper(2, 5);
    karel_add_beeper(1, 1);
    karel_add_beeper(4, 1);

}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}
void goUpLeft() 
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
void goUpRight()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}


bool shouldGoUpRight()
{
    return (facing_west() && !front_is_clear());
}
bool shouldGoUpLeft()
{
    return (facing_east() && !front_is_clear());
}

void navigateRow()
{
    while (!shouldGoUpRight() && !shouldGoUpLeft())
    {
        karel_move();
    }
    
}
#define NO_COLS 8
#define NO_ROWS 10

int beepers [NO_ROWS][NO_COLS] = {0};


void collectBeepersInRow()
{
        while (!shouldGoUpRight() && !shouldGoUpLeft())
    {
        if (beepers_present())
        {
            printf("beeper found at row %d, col %d\n", karel_get_y(), karel_get_x());
            beepers[karel_get_y()][karel_get_x()] = 1;
            
        }
        karel_move();
    }
}

void navigateGrid() 
{
    for (int i = 0; i < NO_COLS; i++)
    {
        navigateRow();
        if (i < NO_COLS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}

void studentCode()
{
    collectBeepersInRow();
}