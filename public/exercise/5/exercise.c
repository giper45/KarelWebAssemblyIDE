#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    karel_init();
    // Karel starts with 5 beepers in his bag
    karel_set_bag_beepers(5);
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

    static bool missionComplete = false;
    static int beepersPlaced = 0;

    if (!missionComplete)
    {
        // TODO: Implement beeper placement logic
        // 1. Check if beepers are available in bag
        // 2. Place beeper if available
        // 3. Check if front is clear
        // 4. Move forward if possible
        // 5. Handle completion (wall reached or bag empty)

    }
}
