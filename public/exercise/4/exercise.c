#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    karel_init();

    // Add beepers along the street in a scattered pattern
    karel_add_beeper(2, 1);
    karel_add_beeper(4, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(8, 1);
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

    // TODO: Implement beeper collection logic
    // 1. Check if beeper present at current position
    // 2. Pick beeper if found
    // 3. Check if front is clear
    // 4. Move forward if possible
    // 5. Stop when hitting wall

    printf("Karel position: (%d, %d) - Beepers in bag: %d\n",
           karel_get_x(), karel_get_y(), karel_get_bag_beepers());
}
