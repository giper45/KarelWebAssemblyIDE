#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    karel_init();
    // Place beepers at random positions along the street for counting
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(6, 1);
    karel_add_beeper(8, 1);
    karel_add_beeper(9, 1);
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


void studentCode() {
    
    static bool missionComplete = false;
    static int beeperCount = 0;
    
    if (!missionComplete) {
        // TODO: Implement counting logic
        // 1. Check if beeper present at current position
        // 2. Increment counter if beeper found
        // 3. Move forward if possible
        // 4. Display final count when wall reached
        
        printf("Position: (%d, %d) | Beepers counted: %d\n", 
               karel_get_x(), karel_get_y(), beeperCount);
    }
}
