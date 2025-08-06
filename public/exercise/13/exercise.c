#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

// TODO: Implement these functions
void move_one_side()
{
    // Move Karel forward 3 steps (one side of the square)
    // HINT: Use a loop or call karel_move() three times
}

void turn_corner()
{
    // Turn Karel left to prepare for the next side
    // HINT: Use karel_turn_left() once
}

void draw_square()
{
    // Use move_one_side() and turn_corner() to draw a complete square
    // HINT: A square has 4 sides, so you need to repeat the pattern 4 times
}

void setup()
{
    karel_init();
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

void studentCode()
{
}
