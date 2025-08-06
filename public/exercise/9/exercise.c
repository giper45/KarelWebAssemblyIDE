#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    karel_init();
    // Initial beeper at position 3 (first beeper to pick up)
    karel_add_beeper(3, 1);
    karel_add_beeper(4, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(6, 1);
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

enum Phase
{
    SEARCHING_BEEPER,
    SEARCHING_EMPTY_CELL,
    COMPLETE
};

void studentCode()
{
    static enum Phase currentPhase = SEARCHING_BEEPER;

    switch (currentPhase)
    {
    case SEARCHING_BEEPER:
        // Implement searching for beeper logic
        printf("Phase 1: Searching for beeper...\n");
        break;
    case SEARCHING_EMPTY_CELL:
        printf("Phase 2: Searching for empty cell...\n");
        // Implement searching for empty cell logic
        break;
    case COMPLETE:
        printf("Phase 3: Operation complete!\n");
        // Implement completion logic
        break;
    }
}
