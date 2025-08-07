#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(2, 1);
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
    int localCounter = 0;
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function

}