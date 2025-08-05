#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates

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
    // Karel starts with enough beepers to represent the count
    karel_get_bag_beepers() = 20;
}

static double lastMoveTime = 0;
void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready) {
            studentCode();
        }
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
