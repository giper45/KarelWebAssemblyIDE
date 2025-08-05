#include "karel.h"
#define REFRESH_RATE 0.5

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};
void studentCode();

void setup() {
    karel_init();
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready) 
            studentCode();
        lastMoveTime = timeSec;
    }
}



void studentCode() {
 
}
