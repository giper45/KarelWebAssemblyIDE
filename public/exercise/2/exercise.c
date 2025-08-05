#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates
// Variabili globali di Karel
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();
void setup() {
    // Initialize Karel and world
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

void studentCode()
{

}





