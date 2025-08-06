#include "karel.h"
#define REFRESH_RATE 0.5

const char *DIRECTION_NAMES[] = {"East", "North", "West", "South"};
#define WORLD_WIDTH 10
#define WORLD_HEIGHT 8

void studentCode();

void setup()
{
    karel_init();
    karel_add_beeper(2, 1); // Add beepers at specific positions
    karel_add_beeper(4, 1);
    karel_add_beeper(6, 1);
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
