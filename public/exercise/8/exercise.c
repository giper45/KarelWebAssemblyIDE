#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    karel_init();
    // First beeper will be at position 5
    karel_add_beeper(5, 1);   // First beeper
    karel_add_beeper(8, 1);   // Additional beepers
    karel_add_beeper(10, 1);  // (Karel should stop at first one)
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
    static bool searchComplete = false;
    static int stepsTaken = 0;
    
    if (!searchComplete) {
        // TODO: Implement search logic
        // 1. Check if beeper is present at current position
        // 2. If no beeper present and front is clear, continue moving
        // 3. Stop when beeper is found or wall is reached
        // 4. Report search results
        
        // Use this pattern:
        // while (!beepers_present() && front_is_clear()) {
        //     karel_move();
        //     stepsTaken++;
        // }
        
        printf("Position: (%d, %d) | Steps taken: %d | Beeper here: %s\n", 
               karel_get_x(), karel_get_y(), stepsTaken, 
               beepers_present() ? "YES" : "NO");
    }
}
