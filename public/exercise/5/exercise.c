#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    karel_init();
    // Karel starts with 5 beepers in his bag
    karel_get_bag_beepers() = 5;
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
    static int beepersPlaced = 0;
    
    if (!missionComplete) {
        // TODO: Implement beeper placement logic
        // 1. Check if beepers are available in bag
        // 2. Place beeper if available
        // 3. Check if front is clear
        // 4. Move forward if possible
        // 5. Handle completion (wall reached or bag empty)
        
        printf("Karel position: (%d, %d) - Beepers in bag: %d - Placed: %d\n", 
               karel_get_x(), karel_get_y(), karel_get_bag_beepers(), beepersPlaced);
    }
}
