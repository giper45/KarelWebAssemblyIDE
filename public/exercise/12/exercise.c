#include "karel.h"
#define REFRESH_RATE 0.3

const char *DIRECTION_NAMES[] = {"East", "North", "West", "South"};
#define GRID_SIZE 5

void studentCode();

void setup()
{
    karel_init();
    karel_set_bag_beepers(25);
    // No initial beepers - Karel will place them
    karel_setup_printf("Exercise 12: Zig-Zag Fill\n");
    karel_setup_printf("Karel will fill a 5x5 area with beepers in zig-zag pattern.\n");
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
